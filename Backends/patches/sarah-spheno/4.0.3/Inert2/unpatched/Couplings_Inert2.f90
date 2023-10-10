! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:47 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Couplings_Inert2
 
Use Control 
Use Settings 
Use Model_Data_Inert2 
Use Mathematics, Only: CompareMatrices, Adjungate 
 
Contains 
 
 Subroutine AllCouplingsReallyAll(lam5,v,lam3,lam4,ZP,lam1,lam2,g1,g2,TW,              & 
& g3,Yd,ZDL,ZDR,Yu,ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,           & 
& cplA0HpcHp,cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,              & 
& cplA0A0A0A0,cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,              & 
& cplA0G0G0H0,cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,             & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,             & 
& cplH0H0hhhh,cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp,          & 
& cplA0H0VZ,cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,       & 
& cplH0cHpVWp,cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,      & 
& cplHpcVWpVP,cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplA0A0cVWpVWp,cplA0A0VZVZ,            & 
& cplA0HpcVWpVP,cplA0HpcVWpVZ,cplA0cHpVPVWp,cplA0cHpVWpVZ,cplG0G0cVWpVWp,cplG0G0VZVZ,    & 
& cplG0HpcVWpVP,cplG0HpcVWpVZ,cplG0cHpVPVWp,cplG0cHpVWpVZ,cplH0H0cVWpVWp,cplH0H0VZVZ,    & 
& cplH0HpcVWpVP,cplH0HpcVWpVZ,cplH0cHpVPVWp,cplH0cHpVWpVZ,cplhhhhcVWpVWp,cplhhhhVZVZ,    & 
& cplhhHpcVWpVP,cplhhHpcVWpVZ,cplhhcHpVPVWp,cplhhcHpVWpVZ,cplHpcHpVPVP,cplHpcHpVPVZ,     & 
& cplHpcHpcVWpVWp,cplHpcHpVZVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L,          & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFuFdVWpL,             & 
& cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,cplcFvFeVWpL,             & 
& cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,              & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,cplcFvFvVZL,           & 
& cplcFvFvVZR,cplcFeFvcVWpL,cplcFeFvcVWpR,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,        & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp,cplcgWCgAcHp,cplcgWpgWphh,cplcgZgWpcHp,            & 
& cplcgWCgWChh,cplcgZgWCHp,cplcgZgZhh,cplcgWpgZHp,cplcgWCgZcHp)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g1,g2,TW,g3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),         & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0A0A0A0,cplA0A0G0G0,           & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplA0G0G0H0,cplA0G0H0hh,         & 
& cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),cplG0G0G0G0,cplG0G0H0H0,               & 
& cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),cplH0H0H0H0,               & 
& cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,cplhhhhHpcHp(2,2),         & 
& cplHpHpcHpcHp(2,2,2,2),cplA0H0VZ,cplA0HpcVWp(2),cplA0cHpVWp(2),cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),cplhhHpcVWp(2),            & 
& cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP(2),  & 
& cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplA0A0cVWpVWp,cplA0A0VZVZ,               & 
& cplA0HpcVWpVP(2),cplA0HpcVWpVZ(2),cplA0cHpVPVWp(2),cplA0cHpVWpVZ(2),cplG0G0cVWpVWp,    & 
& cplG0G0VZVZ,cplG0HpcVWpVP(2),cplG0HpcVWpVZ(2),cplG0cHpVPVWp(2),cplG0cHpVWpVZ(2),       & 
& cplH0H0cVWpVWp,cplH0H0VZVZ,cplH0HpcVWpVP(2),cplH0HpcVWpVZ(2),cplH0cHpVPVWp(2),         & 
& cplH0cHpVWpVZ(2),cplhhhhcVWpVWp,cplhhhhVZVZ,cplhhHpcVWpVP(2),cplhhHpcVWpVZ(2),         & 
& cplhhcHpVPVWp(2),cplhhcHpVWpVZ(2),cplHpcHpVPVP(2,2),cplHpcHpVPVZ(2,2),cplHpcHpcVWpVWp(2,2),& 
& cplHpcHpVZVZ(2,2),cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),& 
& cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),               & 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3), & 
& cplcFuFdVWpR(3,3),cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3), & 
& cplcFvFeVWpL(3,3),cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),& 
& cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),  & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),               & 
& cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3),cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,          & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,       & 
& cplcVWpVPVWpVZ3,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcgGgGVG,cplcgWpgAVWp,               & 
& cplcgWCgAcVWp,cplcgWpgWpVP,cplcgWpgWpVZ,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgWCVP,      & 
& cplcgAgWCVWp,cplcgZgWCVWp,cplcgWCgWCVZ,cplcgWpgZVWp,cplcgWCgZcVWp,cplcgWpgWpG0,        & 
& cplcgWCgWCG0,cplcgZgAhh,cplcgWpgAHp(2),cplcgWCgAcHp(2),cplcgWpgWphh,cplcgZgWpcHp(2),   & 
& cplcgWCgWChh,cplcgZgWCHp(2),cplcgZgZhh,cplcgWpgZHp(2),cplcgWCgZcHp(2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplingsReallyAll'
 
cplA0A0G0 = 0._dp 
Call CouplingA0A0G0T(lam5,v,cplA0A0G0)



cplA0A0hh = 0._dp 
Call CouplingA0A0hhT(lam5,lam3,v,cplA0A0hh)



cplA0G0H0 = 0._dp 
Call CouplingA0G0H0T(lam5,v,cplA0G0H0)



cplA0H0hh = 0._dp 
Call CouplingA0H0hhT(lam5,v,cplA0H0hh)



cplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcHp(gt2,gt3))

 End Do 
End Do 


cplG0G0hh = 0._dp 
Call CouplingG0G0hhT(lam1,v,cplG0G0hh)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H0T(lam5,v,cplG0H0H0)



cplH0H0hh = 0._dp 
Call CouplingH0H0hhT(lam5,lam3,v,cplH0H0hh)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplhhhhhh = 0._dp 
Call CouplinghhhhhhT(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHpT(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplA0A0A0A0 = 0._dp 
Call CouplingA0A0A0A0T(lam2,cplA0A0A0A0)



cplA0A0G0G0 = 0._dp 
Call CouplingA0A0G0G0T(lam5,lam3,cplA0A0G0G0)



cplA0A0G0hh = 0._dp 
Call CouplingA0A0G0hhT(lam5,cplA0A0G0hh)



cplA0A0H0H0 = 0._dp 
Call CouplingA0A0H0H0T(lam2,cplA0A0H0H0)



cplA0A0hhhh = 0._dp 
Call CouplingA0A0hhhhT(lam5,lam3,cplA0A0hhhh)



cplA0A0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0HpcHpT(gt3,gt4,lam4,lam3,lam2,ZP,cplA0A0HpcHp(gt3,gt4))

 End Do 
End Do 


cplA0G0G0H0 = 0._dp 
Call CouplingA0G0G0H0T(lam5,cplA0G0G0H0)



cplA0G0H0hh = 0._dp 
Call CouplingA0G0H0hhT(lam5,cplA0G0H0hh)



cplA0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0G0HpcHpT(gt3,gt4,lam5,lam4,ZP,cplA0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplA0H0hhhh = 0._dp 
Call CouplingA0H0hhhhT(lam5,cplA0H0hhhh)



cplA0hhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0hhHpcHpT(gt3,gt4,lam5,lam4,ZP,cplA0hhHpcHp(gt3,gt4))

 End Do 
End Do 


cplG0G0G0G0 = 0._dp 
Call CouplingG0G0G0G0T(lam1,cplG0G0G0G0)



cplG0G0H0H0 = 0._dp 
Call CouplingG0G0H0H0T(lam5,lam3,cplG0G0H0H0)



cplG0G0hhhh = 0._dp 
Call CouplingG0G0hhhhT(lam1,cplG0G0hhhh)



cplG0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0HpcHpT(gt3,gt4,lam1,lam4,lam3,ZP,cplG0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplG0H0H0hh = 0._dp 
Call CouplingG0H0H0hhT(lam5,cplG0H0H0hh)



cplG0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0H0HpcHpT(gt3,gt4,lam5,lam4,ZP,cplG0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0H0H0H0 = 0._dp 
Call CouplingH0H0H0H0T(lam2,cplH0H0H0H0)



cplH0H0hhhh = 0._dp 
Call CouplingH0H0hhhhT(lam5,lam3,cplH0H0hhhh)



cplH0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHpT(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0hhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0hhHpcHpT(gt3,gt4,lam5,lam4,ZP,cplH0hhHpcHp(gt3,gt4))

 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Call CouplinghhhhhhhhT(lam1,cplhhhhhhhh)



cplhhhhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHpT(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp(gt3,gt4))

 End Do 
End Do 


cplHpHpcHpcHp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpHpcHpcHpT(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,cplHpHpcHpcHp(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplA0H0VZ = 0._dp 
Call CouplingA0H0VZT(g1,g2,TW,cplA0H0VZ)



cplA0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpT(gt2,g2,ZP,cplA0HpcVWp(gt2))

End Do 


cplA0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVWpT(gt2,g2,ZP,cplA0cHpVWp(gt2))

End Do 


cplG0hhVZ = 0._dp 
Call CouplingG0hhVZT(g1,g2,TW,cplG0hhVZ)



cplG0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpT(gt2,g2,ZP,cplG0HpcVWp(gt2))

End Do 


cplG0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVWpT(gt2,g2,ZP,cplG0cHpVWp(gt2))

End Do 


cplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpT(gt2,g2,ZP,cplH0HpcVWp(gt2))

End Do 


cplH0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVWpT(gt2,g2,ZP,cplH0cHpVWp(gt2))

End Do 


cplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpT(gt2,g2,ZP,cplhhHpcVWp(gt2))

End Do 


cplhhcHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVWpT(gt2,g2,ZP,cplhhcHpVWp(gt2))

End Do 


cplHpcHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVP(gt1,gt2))

 End Do 
End Do 


cplHpcHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWpVWp = 0._dp 
Call CouplinghhcVWpVWpT(g2,v,cplhhcVWpVWp)



cplhhVZVZ = 0._dp 
Call CouplinghhVZVZT(g1,g2,v,TW,cplhhVZVZ)



cplHpcVWpVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVPT(gt1,g1,g2,v,ZP,TW,cplHpcVWpVP(gt1))

End Do 


cplHpcVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVZT(gt1,g1,g2,v,ZP,TW,cplHpcVWpVZ(gt1))

End Do 


cplcHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVPVWpT(gt1,g1,g2,v,ZP,TW,cplcHpVPVWp(gt1))

End Do 


cplcHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVWpVZT(gt1,g1,g2,v,ZP,TW,cplcHpVWpVZ(gt1))

End Do 


cplA0A0cVWpVWp = 0._dp 
Call CouplingA0A0cVWpVWpT(g2,cplA0A0cVWpVWp)



cplA0A0VZVZ = 0._dp 
Call CouplingA0A0VZVZT(g1,g2,TW,cplA0A0VZVZ)



cplA0HpcVWpVP = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpVPT(gt2,g1,g2,ZP,TW,cplA0HpcVWpVP(gt2))

End Do 


cplA0HpcVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpVZT(gt2,g1,g2,ZP,TW,cplA0HpcVWpVZ(gt2))

End Do 


cplA0cHpVPVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVPVWpT(gt2,g1,g2,ZP,TW,cplA0cHpVPVWp(gt2))

End Do 


cplA0cHpVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVWpVZT(gt2,g1,g2,ZP,TW,cplA0cHpVWpVZ(gt2))

End Do 


cplG0G0cVWpVWp = 0._dp 
Call CouplingG0G0cVWpVWpT(g2,cplG0G0cVWpVWp)



cplG0G0VZVZ = 0._dp 
Call CouplingG0G0VZVZT(g1,g2,TW,cplG0G0VZVZ)



cplG0HpcVWpVP = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpVPT(gt2,g1,g2,ZP,TW,cplG0HpcVWpVP(gt2))

End Do 


cplG0HpcVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpVZT(gt2,g1,g2,ZP,TW,cplG0HpcVWpVZ(gt2))

End Do 


cplG0cHpVPVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVPVWpT(gt2,g1,g2,ZP,TW,cplG0cHpVPVWp(gt2))

End Do 


cplG0cHpVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVWpVZT(gt2,g1,g2,ZP,TW,cplG0cHpVWpVZ(gt2))

End Do 


cplH0H0cVWpVWp = 0._dp 
Call CouplingH0H0cVWpVWpT(g2,cplH0H0cVWpVWp)



cplH0H0VZVZ = 0._dp 
Call CouplingH0H0VZVZT(g1,g2,TW,cplH0H0VZVZ)



cplH0HpcVWpVP = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpVPT(gt2,g1,g2,ZP,TW,cplH0HpcVWpVP(gt2))

End Do 


cplH0HpcVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpVZT(gt2,g1,g2,ZP,TW,cplH0HpcVWpVZ(gt2))

End Do 


cplH0cHpVPVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVPVWpT(gt2,g1,g2,ZP,TW,cplH0cHpVPVWp(gt2))

End Do 


cplH0cHpVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVWpVZT(gt2,g1,g2,ZP,TW,cplH0cHpVWpVZ(gt2))

End Do 


cplhhhhcVWpVWp = 0._dp 
Call CouplinghhhhcVWpVWpT(g2,cplhhhhcVWpVWp)



cplhhhhVZVZ = 0._dp 
Call CouplinghhhhVZVZT(g1,g2,TW,cplhhhhVZVZ)



cplhhHpcVWpVP = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpVPT(gt2,g1,g2,ZP,TW,cplhhHpcVWpVP(gt2))

End Do 


cplhhHpcVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpVZT(gt2,g1,g2,ZP,TW,cplhhHpcVWpVZ(gt2))

End Do 


cplhhcHpVPVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVPVWpT(gt2,g1,g2,ZP,TW,cplhhcHpVPVWp(gt2))

End Do 


cplhhcHpVWpVZ = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVWpVZT(gt2,g1,g2,ZP,TW,cplhhcHpVWpVZ(gt2))

End Do 


cplHpcHpVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVPT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVP(gt1,gt2))

 End Do 
End Do 


cplHpcHpVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVZT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVZ(gt1,gt2))

 End Do 
End Do 


cplHpcHpcVWpVWp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpcVWpVWpT(gt1,gt2,g2,ZP,cplHpcHpcVWpVWp(gt1,gt2))

 End Do 
End Do 


cplHpcHpVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZVZT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZVZ(gt1,gt2))

 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWpVPVWp = 0._dp 
Call CouplingcVWpVPVWpT(g2,TW,cplcVWpVPVWp)



cplcVWpVWpVZ = 0._dp 
Call CouplingcVWpVWpVZT(g2,TW,cplcVWpVWpVZ)



cplcFdFdG0L = 0._dp 
cplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdG0T(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdG0L(gt1,gt2),cplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhhT(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFuFdHpL = 0._dp 
cplcFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdHpL(gt1,gt2,gt3)   & 
& ,cplcFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeG0L = 0._dp 
cplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeG0T(gt1,gt2,Ye,ZEL,ZER,cplcFeFeG0L(gt1,gt2),cplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehhT(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFvFeHpL = 0._dp 
cplcFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFeHpT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFeHpL(gt1,gt2,gt3),cplcFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuG0L = 0._dp 
cplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuG0T(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuG0L(gt1,gt2),cplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhhT(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcFdFucHpL = 0._dp 
cplcFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFucHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFucHpL(gt1,gt2,gt3) & 
& ,cplcFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvcHpL = 0._dp 
cplcFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvcHpT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvcHpL(gt1,gt2,gt3),               & 
& cplcFeFvcHpR(gt1,gt2,gt3))

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


cplcFuFdVWpL = 0._dp 
cplcFuFdVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdVWpT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdVWpL(gt1,gt2),cplcFuFdVWpR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPT(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFvFeVWpL = 0._dp 
cplcFvFeVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFeVWpT(gt1,gt2,g2,ZEL,cplcFvFeVWpL(gt1,gt2),cplcFvFeVWpR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

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


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFucVWpL = 0._dp 
cplcFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFucVWpT(gt1,gt2,g2,ZDL,ZUL,cplcFdFucVWpL(gt1,gt2),cplcFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvcVWpL = 0._dp 
cplcFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvcVWpT(gt1,gt2,g2,ZEL,cplcFeFvcVWpL(gt1,gt2),cplcFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


cplVGVGVGVG1 = 0._dp 
cplVGVGVGVG2 = 0._dp 
cplVGVGVGVG3 = 0._dp 
Call CouplingVGVGVGVGT(g3,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3)



cplcVWpVPVPVWp1 = 0._dp 
cplcVWpVPVPVWp2 = 0._dp 
cplcVWpVPVPVWp3 = 0._dp 
Call CouplingcVWpVPVPVWpT(g2,TW,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3)



cplcVWpVPVWpVZ1 = 0._dp 
cplcVWpVPVWpVZ2 = 0._dp 
cplcVWpVPVWpVZ3 = 0._dp 
Call CouplingcVWpVPVWpVZT(g2,TW,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)



cplcVWpcVWpVWpVWp1 = 0._dp 
cplcVWpcVWpVWpVWp2 = 0._dp 
cplcVWpcVWpVWpVWp3 = 0._dp 
Call CouplingcVWpcVWpVWpVWpT(g2,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)



cplcVWpVWpVZVZ1 = 0._dp 
cplcVWpVWpVZVZ2 = 0._dp 
cplcVWpVWpVZVZ3 = 0._dp 
Call CouplingcVWpVWpVZVZT(g2,TW,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3)



cplcgGgGVG = 0._dp 
Call CouplingcgGgGVGT(g3,cplcgGgGVG)



cplcgWpgAVWp = 0._dp 
Call CouplingcgWpgAVWpT(g2,TW,cplcgWpgAVWp)



cplcgWCgAcVWp = 0._dp 
Call CouplingcgWCgAcVWpT(g2,TW,cplcgWCgAcVWp)



cplcgWpgWpVP = 0._dp 
Call CouplingcgWpgWpVPT(g2,TW,cplcgWpgWpVP)



cplcgWpgWpVZ = 0._dp 
Call CouplingcgWpgWpVZT(g2,TW,cplcgWpgWpVZ)



cplcgAgWpcVWp = 0._dp 
Call CouplingcgAgWpcVWpT(g2,TW,cplcgAgWpcVWp)



cplcgZgWpcVWp = 0._dp 
Call CouplingcgZgWpcVWpT(g2,TW,cplcgZgWpcVWp)



cplcgWCgWCVP = 0._dp 
Call CouplingcgWCgWCVPT(g2,TW,cplcgWCgWCVP)



cplcgAgWCVWp = 0._dp 
Call CouplingcgAgWCVWpT(g2,TW,cplcgAgWCVWp)



cplcgZgWCVWp = 0._dp 
Call CouplingcgZgWCVWpT(g2,TW,cplcgZgWCVWp)



cplcgWCgWCVZ = 0._dp 
Call CouplingcgWCgWCVZT(g2,TW,cplcgWCgWCVZ)



cplcgWpgZVWp = 0._dp 
Call CouplingcgWpgZVWpT(g2,TW,cplcgWpgZVWp)



cplcgWCgZcVWp = 0._dp 
Call CouplingcgWCgZcVWpT(g2,TW,cplcgWCgZcVWp)



cplcgWpgWpG0 = 0._dp 
Call CouplingcgWpgWpG0T(g2,v,cplcgWpgWpG0)



cplcgWCgWCG0 = 0._dp 
Call CouplingcgWCgWCG0T(g2,v,cplcgWCgWCG0)



cplcgZgAhh = 0._dp 
Call CouplingcgZgAhhT(g1,g2,v,TW,cplcgZgAhh)



cplcgWpgAHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpgAHpT(gt3,g1,g2,v,ZP,TW,cplcgWpgAHp(gt3))

End Do 


cplcgWCgAcHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWCgAcHpT(gt3,g1,g2,v,ZP,TW,cplcgWCgAcHp(gt3))

End Do 


cplcgWpgWphh = 0._dp 
Call CouplingcgWpgWphhT(g2,v,cplcgWpgWphh)



cplcgZgWpcHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpcHpT(gt3,g1,g2,v,ZP,TW,cplcgZgWpcHp(gt3))

End Do 


cplcgWCgWChh = 0._dp 
Call CouplingcgWCgWChhT(g2,v,cplcgWCgWChh)



cplcgZgWCHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWCHpT(gt3,g1,g2,v,ZP,TW,cplcgZgWCHp(gt3))

End Do 


cplcgZgZhh = 0._dp 
Call CouplingcgZgZhhT(g1,g2,v,TW,cplcgZgZhh)



cplcgWpgZHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpgZHpT(gt3,g1,g2,v,ZP,TW,cplcgWpgZHp(gt3))

End Do 


cplcgWCgZcHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWCgZcHpT(gt3,g1,g2,v,ZP,TW,cplcgWCgZcHp(gt3))

End Do 


Iname = Iname - 1 
End Subroutine AllCouplingsReallyAll

Subroutine AllCouplings(lam5,v,lam3,lam4,ZP,lam1,g1,g2,TW,g3,Yd,ZDL,ZDR,              & 
& Yu,ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,              & 
& cplG0G0hh,cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplA0H0VZ,               & 
& cplA0HpcVWp,cplA0cHpVWp,cplG0hhVZ,cplG0HpcVWp,cplG0cHpVWp,cplH0HpcVWp,cplH0cHpVWp,     & 
& cplhhHpcVWp,cplhhcHpVWp,cplHpcHpVP,cplHpcHpVZ,cplhhcVWpVWp,cplhhVZVZ,cplHpcVWpVP,      & 
& cplHpcVWpVZ,cplcHpVPVWp,cplcHpVWpVZ,cplVGVGVG,cplcVWpVPVWp,cplcVWpVWpVZ,               & 
& cplcFdFdG0L,cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,               & 
& cplcFeFeG0L,cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,               & 
& cplcFuFuG0L,cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,             & 
& cplcFeFvcHpL,cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,             & 
& cplcFuFdVWpL,cplcFuFdVWpR,cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVPL,cplcFeFeVPR,             & 
& cplcFvFeVWpL,cplcFvFeVWpR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVGL,cplcFuFuVGR,             & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFdFucVWpL,cplcFdFucVWpR,           & 
& cplcFvFvVZL,cplcFvFvVZR,cplcFeFvcVWpL,cplcFeFvcVWpR)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g1,g2,TW,g3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),              & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplA0H0VZ,cplA0HpcVWp(2),          & 
& cplA0cHpVWp(2),cplG0hhVZ,cplG0HpcVWp(2),cplG0cHpVWp(2),cplH0HpcVWp(2),cplH0cHpVWp(2),  & 
& cplhhHpcVWp(2),cplhhcHpVWp(2),cplHpcHpVP(2,2),cplHpcHpVZ(2,2),cplhhcVWpVWp,            & 
& cplhhVZVZ,cplHpcVWpVP(2),cplHpcVWpVZ(2),cplcHpVPVWp(2),cplcHpVWpVZ(2),cplVGVGVG,       & 
& cplcVWpVPVWp,cplcVWpVWpVZ,cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),          & 
& cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),cplcFeFeG0L(3,3),               & 
& cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),cplcFvFeHpR(3,3,2),& 
& cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucHpL(3,3,2),& 
& cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),cplcFdFdVGL(3,3),          & 
& cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),cplcFuFdVWpL(3,3),cplcFuFdVWpR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFvFeVWpL(3,3), & 
& cplcFvFeVWpR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3), & 
& cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFdFucVWpL(3,3),& 
& cplcFdFucVWpR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcFeFvcVWpL(3,3),               & 
& cplcFeFvcVWpR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'AllCouplings'
 
cplA0A0G0 = 0._dp 
Call CouplingA0A0G0T(lam5,v,cplA0A0G0)



cplA0A0hh = 0._dp 
Call CouplingA0A0hhT(lam5,lam3,v,cplA0A0hh)



cplA0G0H0 = 0._dp 
Call CouplingA0G0H0T(lam5,v,cplA0G0H0)



cplA0H0hh = 0._dp 
Call CouplingA0H0hhT(lam5,v,cplA0H0hh)



cplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcHp(gt2,gt3))

 End Do 
End Do 


cplG0G0hh = 0._dp 
Call CouplingG0G0hhT(lam1,v,cplG0G0hh)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H0T(lam5,v,cplG0H0H0)



cplH0H0hh = 0._dp 
Call CouplingH0H0hhT(lam5,lam3,v,cplH0H0hh)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplhhhhhh = 0._dp 
Call CouplinghhhhhhT(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHpT(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplA0H0VZ = 0._dp 
Call CouplingA0H0VZT(g1,g2,TW,cplA0H0VZ)



cplA0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpT(gt2,g2,ZP,cplA0HpcVWp(gt2))

End Do 


cplA0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVWpT(gt2,g2,ZP,cplA0cHpVWp(gt2))

End Do 


cplG0hhVZ = 0._dp 
Call CouplingG0hhVZT(g1,g2,TW,cplG0hhVZ)



cplG0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpT(gt2,g2,ZP,cplG0HpcVWp(gt2))

End Do 


cplG0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVWpT(gt2,g2,ZP,cplG0cHpVWp(gt2))

End Do 


cplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpT(gt2,g2,ZP,cplH0HpcVWp(gt2))

End Do 


cplH0cHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVWpT(gt2,g2,ZP,cplH0cHpVWp(gt2))

End Do 


cplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpT(gt2,g2,ZP,cplhhHpcVWp(gt2))

End Do 


cplhhcHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVWpT(gt2,g2,ZP,cplhhcHpVWp(gt2))

End Do 


cplHpcHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVP(gt1,gt2))

 End Do 
End Do 


cplHpcHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZT(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZ(gt1,gt2))

 End Do 
End Do 


cplhhcVWpVWp = 0._dp 
Call CouplinghhcVWpVWpT(g2,v,cplhhcVWpVWp)



cplhhVZVZ = 0._dp 
Call CouplinghhVZVZT(g1,g2,v,TW,cplhhVZVZ)



cplHpcVWpVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVPT(gt1,g1,g2,v,ZP,TW,cplHpcVWpVP(gt1))

End Do 


cplHpcVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVZT(gt1,g1,g2,v,ZP,TW,cplHpcVWpVZ(gt1))

End Do 


cplcHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVPVWpT(gt1,g1,g2,v,ZP,TW,cplcHpVPVWp(gt1))

End Do 


cplcHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVWpVZT(gt1,g1,g2,v,ZP,TW,cplcHpVWpVZ(gt1))

End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVGT(g3,cplVGVGVG)



cplcVWpVPVWp = 0._dp 
Call CouplingcVWpVPVWpT(g2,TW,cplcVWpVPVWp)



cplcVWpVWpVZ = 0._dp 
Call CouplingcVWpVWpVZT(g2,TW,cplcVWpVWpVZ)



cplcFdFdG0L = 0._dp 
cplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdG0T(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdG0L(gt1,gt2),cplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhhT(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFuFdHpL = 0._dp 
cplcFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdHpL(gt1,gt2,gt3)   & 
& ,cplcFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeG0L = 0._dp 
cplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeG0T(gt1,gt2,Ye,ZEL,ZER,cplcFeFeG0L(gt1,gt2),cplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehhT(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFvFeHpL = 0._dp 
cplcFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFeHpT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFeHpL(gt1,gt2,gt3),cplcFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuG0L = 0._dp 
cplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuG0T(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuG0L(gt1,gt2),cplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhhT(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcFdFucHpL = 0._dp 
cplcFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFucHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFucHpL(gt1,gt2,gt3) & 
& ,cplcFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvcHpL = 0._dp 
cplcFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvcHpT(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvcHpL(gt1,gt2,gt3),               & 
& cplcFeFvcHpR(gt1,gt2,gt3))

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


cplcFuFdVWpL = 0._dp 
cplcFuFdVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFdVWpT(gt1,gt2,g2,ZDL,ZUL,cplcFuFdVWpL(gt1,gt2),cplcFuFdVWpR(gt1,gt2))

 End Do 
End Do 


cplcFdFdVZL = 0._dp 
cplcFdFdVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdVZT(gt1,gt2,g1,g2,TW,cplcFdFdVZL(gt1,gt2),cplcFdFdVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVPL = 0._dp 
cplcFeFeVPR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVPT(gt1,gt2,g1,g2,TW,cplcFeFeVPL(gt1,gt2),cplcFeFeVPR(gt1,gt2))

 End Do 
End Do 


cplcFvFeVWpL = 0._dp 
cplcFvFeVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFeVWpT(gt1,gt2,g2,ZEL,cplcFvFeVWpL(gt1,gt2),cplcFvFeVWpR(gt1,gt2))

 End Do 
End Do 


cplcFeFeVZL = 0._dp 
cplcFeFeVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeVZT(gt1,gt2,g1,g2,TW,cplcFeFeVZL(gt1,gt2),cplcFeFeVZR(gt1,gt2))

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


cplcFuFuVZL = 0._dp 
cplcFuFuVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuVZT(gt1,gt2,g1,g2,TW,cplcFuFuVZL(gt1,gt2),cplcFuFuVZR(gt1,gt2))

 End Do 
End Do 


cplcFdFucVWpL = 0._dp 
cplcFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFucVWpT(gt1,gt2,g2,ZDL,ZUL,cplcFdFucVWpL(gt1,gt2),cplcFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcFvFvVZL = 0._dp 
cplcFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFvFvVZT(gt1,gt2,g1,g2,TW,cplcFvFvVZL(gt1,gt2),cplcFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplcFeFvcVWpL = 0._dp 
cplcFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvcVWpT(gt1,gt2,g2,ZEL,cplcFeFvcVWpL(gt1,gt2),cplcFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine AllCouplings

Subroutine CouplingA0A0G0T(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0' 
 
res = 0._dp 
res = res-(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0T  
 
 
Subroutine CouplingA0A0hhT(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhT  
 
 
Subroutine CouplingA0G0H0T(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H0T  
 
 
Subroutine CouplingA0H0hhT(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hh' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hhT  
 
 
Subroutine CouplingA0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcHp' 
 
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
res = res+(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcHpT  
 
 
Subroutine CouplingG0G0hhT(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hh' 
 
res = 0._dp 
res = res-(lam1*v)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhT  
 
 
Subroutine CouplingG0H0H0T(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H0T  
 
 
Subroutine CouplingH0H0hhT(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res-(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhT  
 
 
Subroutine CouplingH0HpcHpT(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcHp' 
 
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
res = res-(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcHpT  
 
 
Subroutine CouplinghhhhhhT(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
res = 0._dp 
res = res-3*lam1*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhT  
 
 
Subroutine CouplinghhHpcHpT(gt2,gt3,lam1,lam4,lam3,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcHp' 
 
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
res = res-(lam3*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam1*v*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcHpT  
 
 
Subroutine CouplingA0A0A0A0T(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0A0A0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0A0A0T  
 
 
Subroutine CouplingA0A0G0G0T(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0G0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0G0T  
 
 
Subroutine CouplingA0A0G0hhT(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0hh' 
 
res = 0._dp 
res = res-1._dp*(lam5)/2._dp
res = res+Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0hhT  
 
 
Subroutine CouplingA0A0H0H0T(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0H0H0T  
 
 
Subroutine CouplingA0A0hhhhT(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhhhT  
 
 
Subroutine CouplingA0A0HpcHpT(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0HpcHpT  
 
 
Subroutine CouplingA0G0G0H0T(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0G0H0' 
 
res = 0._dp 
res = res-1._dp*(lam5)/2._dp
res = res+Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0G0H0T  
 
 
Subroutine CouplingA0G0H0hhT(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0hh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H0hhT  
 
 
Subroutine CouplingA0G0HpcHpT(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0HpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0HpcHpT  
 
 
Subroutine CouplingA0H0hhhhT(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hhhh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res-Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hhhhT  
 
 
Subroutine CouplingA0hhHpcHpT(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0hhHpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0hhHpcHpT  
 
 
Subroutine CouplingG0G0G0G0T(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0G0G0' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0G0G0T  
 
 
Subroutine CouplingG0G0H0H0T(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0H0H0T  
 
 
Subroutine CouplingG0G0hhhhT(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhhhT  
 
 
Subroutine CouplingG0G0HpcHpT(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0HpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0HpcHpT  
 
 
Subroutine CouplingG0H0H0hhT(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0hh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res-Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H0hhT  
 
 
Subroutine CouplingG0H0HpcHpT(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0HpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0HpcHpT  
 
 
Subroutine CouplingH0H0H0H0T(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0H0H0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0H0H0T  
 
 
Subroutine CouplingH0H0hhhhT(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhhhT  
 
 
Subroutine CouplingH0H0HpcHpT(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0HpcHpT  
 
 
Subroutine CouplingH0hhHpcHpT(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0hhHpcHp' 
 
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
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0hhHpcHpT  
 
 
Subroutine CouplinghhhhhhhhT(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhT  
 
 
Subroutine CouplinghhhhHpcHpT(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpcHpT  
 
 
Subroutine CouplingHpHpcHpcHpT(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpHpcHpcHp' 
 
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
res = res-2*lam2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res = res-2*Conjg(lam5)*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-2*lam5*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res = res-2*lam1*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpHpcHpcHpT  
 
 
Subroutine CouplingA0H0VZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0VZ' 
 
res = 0._dp 
res = res+(g2*Cos(TW))/2._dp
res = res+(g1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0VZT  
 
 
Subroutine CouplingA0HpcVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpT  
 
 
Subroutine CouplingA0cHpVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0cHpVWpT  
 
 
Subroutine CouplingG0hhVZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0hhVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))/2._dp
res = res-(g1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0hhVZT  
 
 
Subroutine CouplingG0HpcVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpT  
 
 
Subroutine CouplingG0cHpVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0cHpVWpT  
 
 
Subroutine CouplingH0HpcVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpT  
 
 
Subroutine CouplingH0cHpVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0cHpVWpT  
 
 
Subroutine CouplinghhHpcVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpT  
 
 
Subroutine CouplinghhcHpVWpT(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpVWpT  
 
 
Subroutine CouplingHpcHpVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVP' 
 
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
res = res+(g1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcHpVPT  
 
 
Subroutine CouplingHpcHpVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVZ' 
 
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
res = res+(g2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcHpVZT  
 
 
Subroutine CouplinghhcVWpVWpT(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWpVWp' 
 
res = 0._dp 
res = res+(g2**2*v)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcVWpVWpT  
 
 
Subroutine CouplinghhVZVZT(g1,g2,v,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
res = 0._dp 
res = res+(g2**2*v*Cos(TW)**2)/2._dp
res = res+g1*g2*v*Cos(TW)*Sin(TW)
res = res+(g1**2*v*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhVZVZT  
 
 
Subroutine CouplingHpcVWpVPT(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcVWpVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcVWpVPT  
 
 
Subroutine CouplingHpcVWpVZT(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcVWpVZT  
 
 
Subroutine CouplingcHpVPVWpT(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpVPVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpVPVWpT  
 
 
Subroutine CouplingcHpVWpVZT(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpVWpVZT  
 
 
Subroutine CouplingA0A0cVWpVWpT(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0cVWpVWpT  
 
 
Subroutine CouplingA0A0VZVZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0VZVZT  
 
 
Subroutine CouplingA0HpcVWpVPT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpVPT  
 
 
Subroutine CouplingA0HpcVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpVZT  
 
 
Subroutine CouplingA0cHpVPVWpT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0cHpVPVWpT  
 
 
Subroutine CouplingA0cHpVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0cHpVWpVZT  
 
 
Subroutine CouplingG0G0cVWpVWpT(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0cVWpVWpT  
 
 
Subroutine CouplingG0G0VZVZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0VZVZT  
 
 
Subroutine CouplingG0HpcVWpVPT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpVPT  
 
 
Subroutine CouplingG0HpcVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpVZT  
 
 
Subroutine CouplingG0cHpVPVWpT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0cHpVPVWpT  
 
 
Subroutine CouplingG0cHpVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0cHpVWpVZT  
 
 
Subroutine CouplingH0H0cVWpVWpT(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0cVWpVWpT  
 
 
Subroutine CouplingH0H0VZVZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0VZVZT  
 
 
Subroutine CouplingH0HpcVWpVPT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpVPT  
 
 
Subroutine CouplingH0HpcVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpVZT  
 
 
Subroutine CouplingH0cHpVPVWpT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0cHpVPVWpT  
 
 
Subroutine CouplingH0cHpVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0cHpVWpVZT  
 
 
Subroutine CouplinghhhhcVWpVWpT(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWpVWpT  
 
 
Subroutine CouplinghhhhVZVZT(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZT  
 
 
Subroutine CouplinghhHpcVWpVPT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpVPT  
 
 
Subroutine CouplinghhHpcVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpVZT  
 
 
Subroutine CouplinghhcHpVPVWpT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpVPVWpT  
 
 
Subroutine CouplinghhcHpVWpVZT(gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpVWpVZT  
 
 
Subroutine CouplingHpcHpVPVPT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVP' 
 
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
 
End Subroutine CouplingHpcHpVPVPT  
 
 
Subroutine CouplingHpcHpVPVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVZ' 
 
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
 
End Subroutine CouplingHpcHpVPVZT  
 
 
Subroutine CouplingHpcHpcVWpVWpT(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpcVWpVWp' 
 
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
 
End Subroutine CouplingHpcHpcVWpVWpT  
 
 
Subroutine CouplingHpcHpVZVZT(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVZVZ' 
 
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
 
End Subroutine CouplingHpcHpVZVZT  
 
 
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
 
 
Subroutine CouplingcVWpVPVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVWp' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVPVWpT  
 
 
Subroutine CouplingcVWpVWpVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVWpVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVWpVZT  
 
 
Subroutine CouplingcFdFdG0T(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdG0T  
 
 
Subroutine CouplingcFdFdhhT(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhhT  
 
 
Subroutine CouplingcFuFdHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j2)*ZP(gt3,2)*ZUL(gt1,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdHpT  
 
 
Subroutine CouplingcFeFeG0T(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeG0T  
 
 
Subroutine CouplingcFeFehhT(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehhT  
 
 
Subroutine CouplingcFvFeHpT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFeHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resR = resR+Conjg(Ye(gt1,j1))*ZER(gt2,j1)*ZP(gt3,2)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFeHpT  
 
 
Subroutine CouplingcFuFuG0T(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuG0T  
 
 
Subroutine CouplingcFuFuhhT(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhhT  
 
 
Subroutine CouplingcFdFucHpT(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j1)*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFucHpT  
 
 
Subroutine CouplingcFeFvcHpT(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZER(gt1,j1))*Ye(gt2,j1)*ZP(gt3,2)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvcHpT  
 
 
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
 
 
Subroutine CouplingcFuFdVWpT(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFuFdVWpT  
 
 
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
 
 
Subroutine CouplingcFvFeVWpT(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFeVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFvFeVWpT  
 
 
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
 
 
Subroutine CouplingcFdFucVWpT(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFdFucVWpT  
 
 
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
 
 
Subroutine CouplingcFeFvcVWpT(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFeFvcVWpT  
 
 
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
 
 
Subroutine CouplingcVWpVPVPVWpT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVPVWp' 
 
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
 
End Subroutine CouplingcVWpVPVPVWpT  
 
 
Subroutine CouplingcVWpVPVWpVZT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVWpVZ' 
 
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
 
End Subroutine CouplingcVWpVPVWpVZT  
 
 
Subroutine CouplingcVWpcVWpVWpVWpT(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpcVWpVWpVWp' 
 
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
 
End Subroutine CouplingcVWpcVWpVWpVWpT  
 
 
Subroutine CouplingcVWpVWpVZVZT(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVWpVZVZ' 
 
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
 
End Subroutine CouplingcVWpVWpVZVZT  
 
 
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
 
 
Subroutine CouplingcgWpgAVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgAVWp' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgAVWpT  
 
 
Subroutine CouplingcgWCgAcVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgAcVWp' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgAcVWpT  
 
 
Subroutine CouplingcgWpgWpVPT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpVP' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpVPT  
 
 
Subroutine CouplingcgWpgWpVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpVZT  
 
 
Subroutine CouplingcgAgWpcVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWpcVWp' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWpcVWpT  
 
 
Subroutine CouplingcgZgWpcVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpcVWp' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpcVWpT  
 
 
Subroutine CouplingcgWCgWCVPT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCVP' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCVPT  
 
 
Subroutine CouplingcgAgWCVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWCVWp' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWCVWpT  
 
 
Subroutine CouplingcgZgWCVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWCVWp' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWCVWpT  
 
 
Subroutine CouplingcgWCgWCVZT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCVZT  
 
 
Subroutine CouplingcgWpgZVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgZVWp' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgZVWpT  
 
 
Subroutine CouplingcgWCgZcVWpT(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgZcVWp' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgZcVWpT  
 
 
Subroutine CouplingcgWpgWpG0T(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpG0' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpG0T  
 
 
Subroutine CouplingcgWCgWCG0T(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCG0' 
 
res = 0._dp 
res = res+(g2**2*v*RXiWp)/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCG0T  
 
 
Subroutine CouplingcgZgAhhT(g1,g2,v,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgAhh' 
 
res = 0._dp 
res = res+(g1*g2*v*Cos(2._dp*(TW))*RXiZ)/4._dp
res = res+(g1**2*v*RXiZ*Sin(2._dp*(TW)))/8._dp
res = res-(g2**2*v*RXiZ*Sin(2._dp*(TW)))/8._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgAhhT  
 
 
Subroutine CouplingcgWpgAHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgAHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Cos(TW)*RXiWp*ZP(gt3,2))/4._dp
res = res+(g2**2*v*RXiWp*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgAHpT  
 
 
Subroutine CouplingcgWCgAcHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgAcHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Cos(TW)*RXiWp*ZP(gt3,2))/4._dp
res = res+(g2**2*v*RXiWp*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgAcHpT  
 
 
Subroutine CouplingcgWpgWphhT(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWphh' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWphhT  
 
 
Subroutine CouplingcgZgWpcHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpcHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*v*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res-(g1*g2*v*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpcHpT  
 
 
Subroutine CouplingcgWCgWChhT(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWChh' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWChhT  
 
 
Subroutine CouplingcgZgWCHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWCHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2**2*v*Cos(TW)*RXiZ*ZP(gt3,2))/4._dp
res = res-(g1*g2*v*RXiZ*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWCHpT  
 
 
Subroutine CouplingcgZgZhhT(g1,g2,v,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgZhh' 
 
res = 0._dp 
res = res-(g2**2*v*Cos(TW)**2*RXiZ)/4._dp
res = res-(g1*g2*v*Cos(TW)*RXiZ*Sin(TW))/2._dp
res = res-(g1**2*v*RXiZ*Sin(TW)**2)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgZhhT  
 
 
Subroutine CouplingcgWpgZHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgZHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*v*Cos(TW)*RXiWp*ZP(gt3,2))/4._dp
res = res-(g1*g2*v*RXiWp*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgZHpT  
 
 
Subroutine CouplingcgWCgZcHpT(gt3,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgZcHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2**2*v*Cos(TW)*RXiWp*ZP(gt3,2))/4._dp
res = res-(g1*g2*v*RXiWp*Sin(TW)*ZP(gt3,2))/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgZcHpT  
 
 
Subroutine CouplingsForEffPot4(lam2,lam5,lam3,lam4,ZP,lam1,cplA0A0A0A0,               & 
& cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplG0G0G0G0,cplG0G0H0H0,              & 
& cplG0G0hhhh,cplG0G0HpcHp,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,cplhhhhhhhh,             & 
& cplhhhhHpcHp,cplHpHpcHpcHp)

Implicit None 
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam2,lam5,lam3,lam4,lam1

Complex(dp), Intent(out) :: cplA0A0A0A0,cplA0A0G0G0,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),cplG0G0G0G0,        & 
& cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),   & 
& cplhhhhhhhh,cplhhhhHpcHp(2,2),cplHpHpcHpcHp(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot4'
 
cplA0A0A0A0 = 0._dp 
Call CouplingA0A0A0A02L(lam2,cplA0A0A0A0)



cplA0A0G0G0 = 0._dp 
Call CouplingA0A0G0G02L(lam5,lam3,cplA0A0G0G0)



cplA0A0H0H0 = 0._dp 
Call CouplingA0A0H0H02L(lam2,cplA0A0H0H0)



cplA0A0hhhh = 0._dp 
Call CouplingA0A0hhhh2L(lam5,lam3,cplA0A0hhhh)



cplA0A0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0HpcHp2L(gt3,gt4,lam4,lam3,lam2,ZP,cplA0A0HpcHp(gt3,gt4))

 End Do 
End Do 


cplG0G0G0G0 = 0._dp 
Call CouplingG0G0G0G02L(lam1,cplG0G0G0G0)



cplG0G0H0H0 = 0._dp 
Call CouplingG0G0H0H02L(lam5,lam3,cplG0G0H0H0)



cplG0G0hhhh = 0._dp 
Call CouplingG0G0hhhh2L(lam1,cplG0G0hhhh)



cplG0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0HpcHp2L(gt3,gt4,lam1,lam4,lam3,ZP,cplG0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0H0H0H0 = 0._dp 
Call CouplingH0H0H0H02L(lam2,cplH0H0H0H0)



cplH0H0hhhh = 0._dp 
Call CouplingH0H0hhhh2L(lam5,lam3,cplH0H0hhhh)



cplH0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHp2L(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Call Couplinghhhhhhhh2L(lam1,cplhhhhhhhh)



cplhhhhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHp2L(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp(gt3,gt4))

 End Do 
End Do 


cplHpHpcHpcHp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpHpcHpcHp2L(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,cplHpHpcHpcHp(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForEffPot4

Subroutine CouplingsForEffPot3(lam5,v,lam3,lam4,ZP,lam1,g3,Yd,ZDL,ZDR,Yu,             & 
& ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,       & 
& cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplVGVGVG,cplcFdFdG0L,             & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),              & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplVGVGVG,cplcFdFdG0L(3,3),        & 
& cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),& 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForEffPot3'
 
cplA0A0G0 = 0._dp 
Call CouplingA0A0G02L(lam5,v,cplA0A0G0)



cplA0A0hh = 0._dp 
Call CouplingA0A0hh2L(lam5,lam3,v,cplA0A0hh)



cplA0G0H0 = 0._dp 
Call CouplingA0G0H02L(lam5,v,cplA0G0H0)



cplA0H0hh = 0._dp 
Call CouplingA0H0hh2L(lam5,v,cplA0H0hh)



cplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcHp2L(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcHp(gt2,gt3))

 End Do 
End Do 


cplG0G0hh = 0._dp 
Call CouplingG0G0hh2L(lam1,v,cplG0G0hh)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H02L(lam5,v,cplG0H0H0)



cplH0H0hh = 0._dp 
Call CouplingH0H0hh2L(lam5,lam3,v,cplH0H0hh)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHp2L(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplhhhhhh = 0._dp 
Call Couplinghhhhhh2L(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHp2L(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2L(g3,cplVGVGVG)



cplcFdFdG0L = 0._dp 
cplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdG02L(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdG0L(gt1,gt2),cplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhh2L(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFuFdHpL = 0._dp 
cplcFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdHp2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdHpL(gt1,gt2,gt3)  & 
& ,cplcFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeG0L = 0._dp 
cplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeG02L(gt1,gt2,Ye,ZEL,ZER,cplcFeFeG0L(gt1,gt2),cplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehh2L(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFvFeHpL = 0._dp 
cplcFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFeHp2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFeHpL(gt1,gt2,gt3),cplcFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuG0L = 0._dp 
cplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuG02L(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuG0L(gt1,gt2),cplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhh2L(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcFdFucHpL = 0._dp 
cplcFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFucHp2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFucHpL(gt1,gt2,gt3)& 
& ,cplcFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvcHpL = 0._dp 
cplcFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvcHp2L(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvcHpL(gt1,gt2,gt3)               & 
& ,cplcFeFvcHpR(gt1,gt2,gt3))

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

Subroutine CouplingA0A0A0A02L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0A0A0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0A0A02L  
 
 
Subroutine CouplingA0A0G0G02L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0G0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0G02L  
 
 
Subroutine CouplingA0A0H0H02L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0H0H02L  
 
 
Subroutine CouplingA0A0hhhh2L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhhh2L  
 
 
Subroutine CouplingA0A0HpcHp2L(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0HpcHp' 
 
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
If ((gt3.eq.gt4)) Then 
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0HpcHp2L  
 
 
Subroutine CouplingG0G0G0G02L(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0G0G0' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0G0G02L  
 
 
Subroutine CouplingG0G0H0H02L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0H0H02L  
 
 
Subroutine CouplingG0G0hhhh2L(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhhh2L  
 
 
Subroutine CouplingG0G0HpcHp2L(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0HpcHp' 
 
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
If ((gt3.eq.gt4)) Then 
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0HpcHp2L  
 
 
Subroutine CouplingH0H0H0H02L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0H0H0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0H0H02L  
 
 
Subroutine CouplingH0H0hhhh2L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhhh2L  
 
 
Subroutine CouplingH0H0HpcHp2L(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0HpcHp' 
 
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
If ((gt3.eq.gt4)) Then 
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0HpcHp2L  
 
 
Subroutine Couplinghhhhhhhh2L(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2L  
 
 
Subroutine CouplinghhhhHpcHp2L(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpcHp' 
 
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
If ((gt3.eq.gt4)) Then 
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
End If 
If ((gt3.eq.gt4)) Then 
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpcHp2L  
 
 
Subroutine CouplingHpHpcHpcHp2L(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpHpcHpcHp' 
 
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
res = res-2*lam2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*Conjg(lam5)*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*lam5*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
End If 
If ((gt1.eq.gt3).And.(gt2.eq.gt4)) Then 
res = res-2*lam1*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpHpcHpcHp2L  
 
 
Subroutine CouplingA0A0G02L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0' 
 
res = 0._dp 
res = res-(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G02L  
 
 
Subroutine CouplingA0A0hh2L(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hh2L  
 
 
Subroutine CouplingA0G0H02L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H02L  
 
 
Subroutine CouplingA0H0hh2L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hh' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hh2L  
 
 
Subroutine CouplingA0HpcHp2L(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcHp' 
 
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
res = res+(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcHp2L  
 
 
Subroutine CouplingG0G0hh2L(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hh' 
 
res = 0._dp 
res = res-(lam1*v)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hh2L  
 
 
Subroutine CouplingG0H0H02L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H02L  
 
 
Subroutine CouplingH0H0hh2L(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res-(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hh2L  
 
 
Subroutine CouplingH0HpcHp2L(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcHp' 
 
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
res = res-(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcHp2L  
 
 
Subroutine Couplinghhhhhh2L(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
res = 0._dp 
res = res-3*lam1*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2L  
 
 
Subroutine CouplinghhHpcHp2L(gt2,gt3,lam1,lam4,lam3,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcHp' 
 
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
res = res-(lam3*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam1*v*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcHp2L  
 
 
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
 
 
Subroutine CouplingcFdFdG02L(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdG02L  
 
 
Subroutine CouplingcFdFdhh2L(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2L  
 
 
Subroutine CouplingcFuFdHp2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j2)*ZP(gt3,2)*ZUL(gt1,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdHp2L  
 
 
Subroutine CouplingcFeFeG02L(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeG02L  
 
 
Subroutine CouplingcFeFehh2L(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2L  
 
 
Subroutine CouplingcFvFeHp2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFeHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resR = resR+Conjg(Ye(gt1,j1))*ZER(gt2,j1)*ZP(gt3,2)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFeHp2L  
 
 
Subroutine CouplingcFuFuG02L(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuG02L  
 
 
Subroutine CouplingcFuFuhh2L(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2L  
 
 
Subroutine CouplingcFdFucHp2L(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j1)*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFucHp2L  
 
 
Subroutine CouplingcFeFvcHp2L(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZER(gt1,j1))*Ye(gt2,j1)*ZP(gt3,2)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvcHp2L  
 
 
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
 
 
Subroutine CouplingsFor2LPole3(lam5,v,lam3,lam4,ZP,lam1,g3,Yd,ZDL,ZDR,Yu,             & 
& ZUL,ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,       & 
& cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplVGVGVG,cplcFdFdG0L,             & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g3

Complex(dp), Intent(in) :: lam5,lam3,lam4,lam1,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),              & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplVGVGVG,cplcFdFdG0L(3,3),        & 
& cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),& 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole3'
 
cplA0A0G0 = 0._dp 
Call CouplingA0A0G02LP(lam5,v,cplA0A0G0)



cplA0A0hh = 0._dp 
Call CouplingA0A0hh2LP(lam5,lam3,v,cplA0A0hh)



cplA0G0H0 = 0._dp 
Call CouplingA0G0H02LP(lam5,v,cplA0G0H0)



cplA0H0hh = 0._dp 
Call CouplingA0H0hh2LP(lam5,v,cplA0H0hh)



cplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcHp2LP(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcHp(gt2,gt3))

 End Do 
End Do 


cplG0G0hh = 0._dp 
Call CouplingG0G0hh2LP(lam1,v,cplG0G0hh)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H02LP(lam5,v,cplG0H0H0)



cplH0H0hh = 0._dp 
Call CouplingH0H0hh2LP(lam5,lam3,v,cplH0H0hh)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHp2LP(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplhhhhhh = 0._dp 
Call Couplinghhhhhh2LP(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHp2LP(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplVGVGVG = 0._dp 
Call CouplingVGVGVG2LP(g3,cplVGVGVG)



cplcFdFdG0L = 0._dp 
cplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdG02LP(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdG0L(gt1,gt2),cplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhh2LP(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFuFdHpL = 0._dp 
cplcFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFuFdHp2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFuFdHpL(gt1,gt2,gt3) & 
& ,cplcFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFeG0L = 0._dp 
cplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeG02LP(gt1,gt2,Ye,ZEL,ZER,cplcFeFeG0L(gt1,gt2),cplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehh2LP(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFvFeHpL = 0._dp 
cplcFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFvFeHp2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFvFeHpL(gt1,gt2,gt3),               & 
& cplcFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFuFuG0L = 0._dp 
cplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuG02LP(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuG0L(gt1,gt2),cplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhh2LP(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcFdFucHpL = 0._dp 
cplcFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFucHp2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,cplcFdFucHpL(gt1,gt2,gt3)& 
& ,cplcFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvcHpL = 0._dp 
cplcFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvcHp2LP(gt1,gt2,gt3,Ye,ZP,ZER,cplcFeFvcHpL(gt1,gt2,gt3)              & 
& ,cplcFeFvcHpR(gt1,gt2,gt3))

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

Subroutine CouplingA0A0G02LP(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0' 
 
res = 0._dp 
res = res-(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G02LP  
 
 
Subroutine CouplingA0A0hh2LP(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hh2LP  
 
 
Subroutine CouplingA0G0H02LP(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H02LP  
 
 
Subroutine CouplingA0H0hh2LP(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hh' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hh2LP  
 
 
Subroutine CouplingA0HpcHp2LP(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcHp' 
 
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
res = res+(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcHp2LP  
 
 
Subroutine CouplingG0G0hh2LP(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hh' 
 
res = 0._dp 
res = res-(lam1*v)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hh2LP  
 
 
Subroutine CouplingG0H0H02LP(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H02LP  
 
 
Subroutine CouplingH0H0hh2LP(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res-(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hh2LP  
 
 
Subroutine CouplingH0HpcHp2LP(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcHp' 
 
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
res = res-(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcHp2LP  
 
 
Subroutine Couplinghhhhhh2LP(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
res = 0._dp 
res = res-3*lam1*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhh2LP  
 
 
Subroutine CouplinghhHpcHp2LP(gt2,gt3,lam1,lam4,lam3,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcHp' 
 
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
res = res-(lam3*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam1*v*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcHp2LP  
 
 
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
 
 
Subroutine CouplingcFdFdG02LP(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdG02LP  
 
 
Subroutine CouplingcFdFdhh2LP(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhh2LP  
 
 
Subroutine CouplingcFuFdHp2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFdHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yd(j1,j2))*ZDR(gt2,j2)*ZP(gt3,2)*ZUL(gt1,j1)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFdHp2LP  
 
 
Subroutine CouplingcFeFeG02LP(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeG02LP  
 
 
Subroutine CouplingcFeFehh2LP(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehh2LP  
 
 
Subroutine CouplingcFvFeHp2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFvFeHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resR = resR+Conjg(Ye(gt1,j1))*ZER(gt2,j1)*ZP(gt3,2)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFvFeHp2LP  
 
 
Subroutine CouplingcFuFuG02LP(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuG02LP  
 
 
Subroutine CouplingcFuFuhh2LP(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhh2LP  
 
 
Subroutine CouplingcFdFucHp2LP(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yd(j1,j2)*ZP(gt3,2)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j1)*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFucHp2LP  
 
 
Subroutine CouplingcFeFvcHp2LP(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZER(gt1,j1))*Ye(gt2,j1)*ZP(gt3,2)
End Do 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvcHp2LP  
 
 
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
 
 
Subroutine CouplingsFor2LPole4(lam2,lam5,lam3,lam4,ZP,lam1,cplA0A0A0A0,               & 
& cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,              & 
& cplA0G0H0hh,cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,             & 
& cplG0G0hhhh,cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,             & 
& cplH0H0HpcHp,cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp)

Implicit None 
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam2,lam5,lam3,lam4,lam1

Complex(dp), Intent(out) :: cplA0A0A0A0,cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),        & 
& cplA0G0G0H0,cplA0G0H0hh,cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),               & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),   & 
& cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,               & 
& cplhhhhHpcHp(2,2),cplHpHpcHpcHp(2,2,2,2)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsFor2LPole4'
 
cplA0A0A0A0 = 0._dp 
Call CouplingA0A0A0A02LP(lam2,cplA0A0A0A0)



cplA0A0G0G0 = 0._dp 
Call CouplingA0A0G0G02LP(lam5,lam3,cplA0A0G0G0)



cplA0A0G0hh = 0._dp 
Call CouplingA0A0G0hh2LP(lam5,cplA0A0G0hh)



cplA0A0H0H0 = 0._dp 
Call CouplingA0A0H0H02LP(lam2,cplA0A0H0H0)



cplA0A0hhhh = 0._dp 
Call CouplingA0A0hhhh2LP(lam5,lam3,cplA0A0hhhh)



cplA0A0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0HpcHp2LP(gt3,gt4,lam4,lam3,lam2,ZP,cplA0A0HpcHp(gt3,gt4))

 End Do 
End Do 


cplA0G0G0H0 = 0._dp 
Call CouplingA0G0G0H02LP(lam5,cplA0G0G0H0)



cplA0G0H0hh = 0._dp 
Call CouplingA0G0H0hh2LP(lam5,cplA0G0H0hh)



cplA0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0G0HpcHp2LP(gt3,gt4,lam5,lam4,ZP,cplA0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplA0H0hhhh = 0._dp 
Call CouplingA0H0hhhh2LP(lam5,cplA0H0hhhh)



cplA0hhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0hhHpcHp2LP(gt3,gt4,lam5,lam4,ZP,cplA0hhHpcHp(gt3,gt4))

 End Do 
End Do 


cplG0G0G0G0 = 0._dp 
Call CouplingG0G0G0G02LP(lam1,cplG0G0G0G0)



cplG0G0H0H0 = 0._dp 
Call CouplingG0G0H0H02LP(lam5,lam3,cplG0G0H0H0)



cplG0G0hhhh = 0._dp 
Call CouplingG0G0hhhh2LP(lam1,cplG0G0hhhh)



cplG0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0HpcHp2LP(gt3,gt4,lam1,lam4,lam3,ZP,cplG0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplG0H0H0hh = 0._dp 
Call CouplingG0H0H0hh2LP(lam5,cplG0H0H0hh)



cplG0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0H0HpcHp2LP(gt3,gt4,lam5,lam4,ZP,cplG0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0H0H0H0 = 0._dp 
Call CouplingH0H0H0H02LP(lam2,cplH0H0H0H0)



cplH0H0hhhh = 0._dp 
Call CouplingH0H0hhhh2LP(lam5,lam3,cplH0H0hhhh)



cplH0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHp2LP(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0hhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0hhHpcHp2LP(gt3,gt4,lam5,lam4,ZP,cplH0hhHpcHp(gt3,gt4))

 End Do 
End Do 


cplhhhhhhhh = 0._dp 
Call Couplinghhhhhhhh2LP(lam1,cplhhhhhhhh)



cplhhhhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHp2LP(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp(gt3,gt4))

 End Do 
End Do 


cplHpHpcHpcHp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpHpcHpcHp2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,cplHpHpcHpcHp(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsFor2LPole4

Subroutine CouplingA0A0A0A02LP(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0A0A0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0A0A02LP  
 
 
Subroutine CouplingA0A0G0G02LP(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0G0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0G02LP  
 
 
Subroutine CouplingA0A0G0hh2LP(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0hh' 
 
res = 0._dp 
res = res-1._dp*(lam5)/2._dp
res = res+Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0hh2LP  
 
 
Subroutine CouplingA0A0H0H02LP(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0H0H02LP  
 
 
Subroutine CouplingA0A0hhhh2LP(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhhh2LP  
 
 
Subroutine CouplingA0A0HpcHp2LP(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0HpcHp2LP  
 
 
Subroutine CouplingA0G0G0H02LP(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0G0H0' 
 
res = 0._dp 
res = res-1._dp*(lam5)/2._dp
res = res+Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0G0H02LP  
 
 
Subroutine CouplingA0G0H0hh2LP(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0hh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H0hh2LP  
 
 
Subroutine CouplingA0G0HpcHp2LP(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0HpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0HpcHp2LP  
 
 
Subroutine CouplingA0H0hhhh2LP(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hhhh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res-Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hhhh2LP  
 
 
Subroutine CouplingA0hhHpcHp2LP(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0hhHpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0hhHpcHp2LP  
 
 
Subroutine CouplingG0G0G0G02LP(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0G0G0' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0G0G02LP  
 
 
Subroutine CouplingG0G0H0H02LP(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0H0H02LP  
 
 
Subroutine CouplingG0G0hhhh2LP(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhhh2LP  
 
 
Subroutine CouplingG0G0HpcHp2LP(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0HpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0HpcHp2LP  
 
 
Subroutine CouplingG0H0H0hh2LP(lam5,res)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0hh' 
 
res = 0._dp 
res = res+lam5/2._dp
res = res-Conjg(lam5)/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H0hh2LP  
 
 
Subroutine CouplingG0H0HpcHp2LP(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0HpcHp' 
 
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
res = res+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0HpcHp2LP  
 
 
Subroutine CouplingH0H0H0H02LP(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0H0H0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0H0H02LP  
 
 
Subroutine CouplingH0H0hhhh2LP(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhhh2LP  
 
 
Subroutine CouplingH0H0HpcHp2LP(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0HpcHp2LP  
 
 
Subroutine CouplingH0hhHpcHp2LP(gt3,gt4,lam5,lam4,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0hhHpcHp' 
 
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
res = res-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res = res-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res = res+(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0hhHpcHp2LP  
 
 
Subroutine Couplinghhhhhhhh2LP(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine Couplinghhhhhhhh2LP  
 
 
Subroutine CouplinghhhhHpcHp2LP(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpcHp2LP  
 
 
Subroutine CouplingHpHpcHpcHp2LP(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpHpcHpcHp' 
 
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
res = res-2*lam2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res = res-2*Conjg(lam5)*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res = res-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res = res-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res = res-2*lam5*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res = res-2*lam1*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpHpcHpcHp2LP  
 
 
Subroutine CouplingsForLoopMasses(lam5,lam4,v,ZP,g2,Yd,Yu,ZDL,ZDR,ZUL,ZUR,            & 
& Ye,ZER,g1,TW,lam1,lam3,lam2,g3,ZEL,cplA0HpcUHp,cplA0cUHpVWp,cplcFdFucUHpL,             & 
& cplcFdFucUHpR,cplcFeFvcUHpL,cplcFeFvcUHpR,cplG0cUHpVWp,cplcgZgWpcUHp,cplcgWpgZUHp,     & 
& cplcgWCgZcUHp,cplcgZgWCUHp,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,          & 
& cplHpcUHpVP,cplHpcUHpVZ,cplcUHpVPVWp,cplcUHpVWpVZ,cplA0A0UHpcUHp,cplG0G0UHpcUHp,       & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplUHpHpcUHpcHp,cplUHpcUHpVPVP,cplUHpcUHpcVWpVWp,        & 
& cplUHpcUHpVZVZ,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,       & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,   & 
& cplcUFuFdVWpR,cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,        & 
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeG0L,         & 
& cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,         & 
& cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR,cplcUFvFeHpL,   & 
& cplcUFvFeHpR,cplcUFvFeVWpL,cplcUFvFeVWpR,cplcUFvFvVZL,cplcUFvFvVZR,cplA0A0G0,          & 
& cplA0G0H0,cplcFdFdG0L,cplcFdFdG0R,cplcFeFeG0L,cplcFeFeG0R,cplcFuFuG0L,cplcFuFuG0R,     & 
& cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,cplG0HpcVWp,cplA0A0G0G0,       & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp,cplG0G0cVWpVWp,cplG0G0VZVZ,           & 
& cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp,       & 
& cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp,   & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcHp,cplA0HpcVWp,cplA0A0A0A0,               & 
& cplA0A0H0H0,cplA0A0HpcHp,cplA0A0cVWpVWp,cplA0A0VZVZ,cplH0HpcHp,cplH0HpcVWp,            & 
& cplH0H0H0H0,cplH0H0HpcHp,cplH0H0cVWpVWp,cplH0H0VZVZ,cplcFdFdVGL,cplcFdFdVGR,           & 
& cplcFuFuVGL,cplcFuFuVGR,cplcgGgGVG,cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,   & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFeFeVPL,cplcFeFeVPR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcgWpgWpVP,cplcgWCgWCVP,cplHpcHpVP,cplHpcVWpVP,cplcVWpVPVWp,cplHpcHpVPVP,            & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFvVZL,cplcFvFvVZR,               & 
& cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ,cplHpcVWpVZ,cplcVWpVWpVZ,cplHpcHpVZVZ,            & 
& cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,cplcFdFucVWpL,cplcFdFucVWpR,           & 
& cplcFeFvcVWpL,cplcFeFvcVWpR,cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,   & 
& cplHpcHpcVWpVWp,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,              & 
& cplcHpVWpVZ,cplcHpVPVWp,cplHpcHpVPVZ,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g2,g1,TW,g3

Complex(dp), Intent(in) :: lam5,lam4,Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3),Ye(3,3),ZER(3,3),       & 
& lam1,lam3,lam2,ZEL(3,3)

Complex(dp), Intent(out) :: cplA0HpcUHp(2,2),cplA0cUHpVWp(2),cplcFdFucUHpL(3,3,2),cplcFdFucUHpR(3,3,2),           & 
& cplcFeFvcUHpL(3,3,2),cplcFeFvcUHpR(3,3,2),cplG0cUHpVWp(2),cplcgZgWpcUHp(2),            & 
& cplcgWpgZUHp(2),cplcgWCgZcUHp(2),cplcgZgWCUHp(2),cplH0HpcUHp(2,2),cplH0cUHpVWp(2),     & 
& cplhhHpcUHp(2,2),cplhhcUHpVWp(2),cplHpcUHpVP(2,2),cplHpcUHpVZ(2,2),cplcUHpVPVWp(2),    & 
& cplcUHpVWpVZ(2),cplA0A0UHpcUHp(2,2),cplG0G0UHpcUHp(2,2),cplH0H0UHpcUHp(2,2),           & 
& cplhhhhUHpcUHp(2,2),cplUHpHpcUHpcHp(2,2,2,2),cplUHpcUHpVPVP(2,2),cplUHpcUHpcVWpVWp(2,2),& 
& cplUHpcUHpVZVZ(2,2),cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),             & 
& cplcUFdFdhhR(3,3),cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),               & 
& cplcUFdFdVPR(3,3),cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),            & 
& cplcUFdFucHpR(3,3,2),cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFuFdHpL(3,3,2),      & 
& cplcUFuFdHpR(3,3,2),cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuG0L(3,3),           & 
& cplcUFuFuG0R(3,3),cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),               & 
& cplcUFuFuVGR(3,3),cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),               & 
& cplcUFuFuVZR(3,3),cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),               & 
& cplcUFeFehhR(3,3),cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),               & 
& cplcUFeFeVZR(3,3),cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),       & 
& cplcUFeFvcVWpR(3,3),cplcUFvFeHpL(3,3,2),cplcUFvFeHpR(3,3,2),cplcUFvFeVWpL(3,3),        & 
& cplcUFvFeVWpR(3,3),cplcUFvFvVZL(3,3),cplcUFvFvVZR(3,3),cplA0A0G0,cplA0G0H0,            & 
& cplcFdFdG0L(3,3),cplcFdFdG0R(3,3),cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFuFuG0L(3,3),  & 
& cplcFuFuG0R(3,3),cplG0G0hh,cplcgWpgWpG0,cplcgWCgWCG0,cplG0H0H0,cplG0hhVZ,              & 
& cplG0HpcVWp(2),cplA0A0G0G0,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),      & 
& cplG0G0cVWpVWp,cplG0G0VZVZ,cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),      & 
& cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcgWpgWphh,      & 
& cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),cplhhHpcVWp(2),            & 
& cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplH0H0hhhh,cplhhhhhhhh,cplhhhhHpcHp(2,2),          & 
& cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0HpcHp(2,2),cplA0HpcVWp(2),cplA0A0A0A0,       & 
& cplA0A0H0H0,cplA0A0HpcHp(2,2),cplA0A0cVWpVWp,cplA0A0VZVZ,cplH0HpcHp(2,2),              & 
& cplH0HpcVWp(2),cplH0H0H0H0,cplH0H0HpcHp(2,2),cplH0H0cVWpVWp,cplH0H0VZVZ,               & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcgGgGVG,        & 
& cplVGVGVG,cplVGVGVGVG1,cplVGVGVGVG2,cplVGVGVGVG3,cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),    & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),cplcgWpgWpVP,      & 
& cplcgWCgWCVP,cplHpcHpVP(2,2),cplHpcVWpVP(2),cplcVWpVPVWp,cplHpcHpVPVP(2,2),            & 
& cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3,cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),     & 
& cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFvFvVZL(3,3),  & 
& cplcFvFvVZR(3,3),cplcgWpgWpVZ,cplcgWCgWCVZ,cplHpcHpVZ(2,2),cplHpcVWpVZ(2),             & 
& cplcVWpVWpVZ,cplHpcHpVZVZ(2,2),cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3,        & 
& cplcFdFucVWpL(3,3),cplcFdFucVWpR(3,3),cplcFeFvcVWpL(3,3),cplcFeFvcVWpR(3,3)

Complex(dp), Intent(out) :: cplcgWCgAcVWp,cplcgAgWpcVWp,cplcgZgWpcVWp,cplcgWCgZcVWp,cplHpcHpcVWpVWp(2,2),          & 
& cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3,cplcHpVWpVZ(2),               & 
& cplcHpVPVWp(2),cplHpcHpVPVZ(2,2),cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForLoopMasses'
 
cplA0HpcUHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcUHpL(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcUHp(gt2,gt3))

 End Do 
End Do 


cplA0cUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cUHpVWpL(gt2,g2,cplA0cUHpVWp(gt2))

End Do 


cplcFdFucUHpL = 0._dp 
cplcFdFucUHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFdFucUHpL(gt1,gt2,gt3,Yd,Yu,ZDL,ZDR,ZUL,ZUR,cplcFdFucUHpL(gt1,gt2,gt3)  & 
& ,cplcFdFucUHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeFvcUHpL = 0._dp 
cplcFeFvcUHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcFeFvcUHpL(gt1,gt2,gt3,Ye,ZER,cplcFeFvcUHpL(gt1,gt2,gt3),cplcFeFvcUHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplG0cUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cUHpVWpL(gt2,g2,cplG0cUHpVWp(gt2))

End Do 


cplcgZgWpcUHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWpcUHpL(gt3,g1,g2,v,TW,cplcgZgWpcUHp(gt3))

End Do 


cplcgWpgZUHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWpgZUHpL(gt3,g1,g2,v,TW,cplcgWpgZUHp(gt3))

End Do 


cplcgWCgZcUHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgWCgZcUHpL(gt3,g1,g2,v,TW,cplcgWCgZcUHp(gt3))

End Do 


cplcgZgWCUHp = 0._dp 
Do gt3 = 1, 2
Call CouplingcgZgWCUHpL(gt3,g1,g2,v,TW,cplcgZgWCUHp(gt3))

End Do 


cplH0HpcUHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcUHpL(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcUHp(gt2,gt3))

 End Do 
End Do 


cplH0cUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cUHpVWpL(gt2,g2,cplH0cUHpVWp(gt2))

End Do 


cplhhHpcUHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcUHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcUHp(gt2,gt3))

 End Do 
End Do 


cplhhcUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcUHpVWpL(gt2,g2,cplhhcUHpVWp(gt2))

End Do 


cplHpcUHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcUHpVPL(gt1,gt2,g1,g2,ZP,TW,cplHpcUHpVP(gt1,gt2))

 End Do 
End Do 


cplHpcUHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcUHpVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcUHpVZ(gt1,gt2))

 End Do 
End Do 


cplcUHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHpVPVWpL(gt1,g1,g2,v,TW,cplcUHpVPVWp(gt1))

End Do 


cplcUHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcUHpVWpVZL(gt1,g1,g2,v,TW,cplcUHpVWpVZ(gt1))

End Do 


cplA0A0UHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0UHpcUHpL(gt3,gt4,lam4,lam3,lam2,cplA0A0UHpcUHp(gt3,gt4))

 End Do 
End Do 


cplG0G0UHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0UHpcUHpL(gt3,gt4,lam1,lam4,lam3,cplG0G0UHpcUHp(gt3,gt4))

 End Do 
End Do 


cplH0H0UHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0UHpcUHpL(gt3,gt4,lam4,lam3,lam2,cplH0H0UHpcUHp(gt3,gt4))

 End Do 
End Do 


cplhhhhUHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhUHpcUHpL(gt3,gt4,lam1,lam4,lam3,cplhhhhUHpcUHp(gt3,gt4))

 End Do 
End Do 


cplUHpHpcUHpcHp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingUHpHpcUHpcHpL(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,cplUHpHpcUHpcHp(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplUHpcUHpVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpcUHpVPVPL(gt1,gt2,g1,g2,TW,cplUHpcUHpVPVP(gt1,gt2))

 End Do 
End Do 


cplUHpcUHpcVWpVWp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpcUHpcVWpVWpL(gt1,gt2,g2,cplUHpcUHpcVWpVWp(gt1,gt2))

 End Do 
End Do 


cplUHpcUHpVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingUHpcUHpVZVZL(gt1,gt2,g1,g2,TW,cplUHpcUHpVZVZ(gt1,gt2))

 End Do 
End Do 


cplcUFdFdG0L = 0._dp 
cplcUFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdG0L(gt1,gt2,Yd,ZDL,ZDR,cplcUFdFdG0L(gt1,gt2),cplcUFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,cplcUFdFdhhL(gt1,gt2),cplcUFdFdhhR(gt1,gt2))

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


cplcUFdFucHpL = 0._dp 
cplcUFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFucHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,cplcUFdFucHpL(gt1,gt2,gt3)       & 
& ,cplcUFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFucVWpL = 0._dp 
cplcUFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFucVWpL(gt1,gt2,g2,ZUL,cplcUFdFucVWpL(gt1,gt2),cplcUFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFuFdHpL = 0._dp 
cplcUFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,cplcUFuFdHpL(gt1,gt2,gt3)         & 
& ,cplcUFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdVWpL = 0._dp 
cplcUFuFdVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFdVWpL(gt1,gt2,g2,ZDL,cplcUFuFdVWpL(gt1,gt2),cplcUFuFdVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuG0L = 0._dp 
cplcUFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuG0L(gt1,gt2,Yu,ZUL,ZUR,cplcUFuFuG0L(gt1,gt2),cplcUFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcUFuFuhhL = 0._dp 
cplcUFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,cplcUFuFuhhL(gt1,gt2),cplcUFuFuhhR(gt1,gt2))

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


cplcUFeFeG0L = 0._dp 
cplcUFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeG0L(gt1,gt2,Ye,ZEL,ZER,cplcUFeFeG0L(gt1,gt2),cplcUFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFehhL(gt1,gt2,Ye,ZEL,ZER,cplcUFeFehhL(gt1,gt2),cplcUFeFehhR(gt1,gt2))

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


cplcUFeFvcHpL = 0._dp 
cplcUFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvcHpL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvcHpL(gt1,gt2,gt3),cplcUFeFvcHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFvcVWpL = 0._dp 
cplcUFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFvcVWpL(gt1,gt2,g2,cplcUFeFvcVWpL(gt1,gt2),cplcUFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFvFeHpL = 0._dp 
cplcUFvFeHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFvFeHpL(gt1,gt2,gt3,Ye,ZP,ZER,cplcUFvFeHpL(gt1,gt2,gt3),               & 
& cplcUFvFeHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFvFeVWpL = 0._dp 
cplcUFvFeVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFvFeVWpL(gt1,gt2,g2,ZEL,cplcUFvFeVWpL(gt1,gt2),cplcUFvFeVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFvFvVZL = 0._dp 
cplcUFvFvVZR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFvFvVZL(gt1,gt2,g1,g2,TW,cplcUFvFvVZL(gt1,gt2),cplcUFvFvVZR(gt1,gt2))

 End Do 
End Do 


cplA0A0G0 = 0._dp 
Call CouplingA0A0G0L(lam5,v,cplA0A0G0)



cplA0G0H0 = 0._dp 
Call CouplingA0G0H0L(lam5,v,cplA0G0H0)



cplcFdFdG0L = 0._dp 
cplcFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdG0L(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdG0L(gt1,gt2),cplcFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcFeFeG0L = 0._dp 
cplcFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFeG0L(gt1,gt2,Ye,ZEL,ZER,cplcFeFeG0L(gt1,gt2),cplcFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcFuFuG0L = 0._dp 
cplcFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuG0L(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuG0L(gt1,gt2),cplcFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplG0G0hh = 0._dp 
Call CouplingG0G0hhL(lam1,v,cplG0G0hh)



cplcgWpgWpG0 = 0._dp 
Call CouplingcgWpgWpG0L(g2,v,cplcgWpgWpG0)



cplcgWCgWCG0 = 0._dp 
Call CouplingcgWCgWCG0L(g2,v,cplcgWCgWCG0)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H0L(lam5,v,cplG0H0H0)



cplG0hhVZ = 0._dp 
Call CouplingG0hhVZL(g1,g2,TW,cplG0hhVZ)



cplG0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpL(gt2,g2,ZP,cplG0HpcVWp(gt2))

End Do 


cplA0A0G0G0 = 0._dp 
Call CouplingA0A0G0G0L(lam5,lam3,cplA0A0G0G0)



cplG0G0G0G0 = 0._dp 
Call CouplingG0G0G0G0L(lam1,cplG0G0G0G0)



cplG0G0H0H0 = 0._dp 
Call CouplingG0G0H0H0L(lam5,lam3,cplG0G0H0H0)



cplG0G0hhhh = 0._dp 
Call CouplingG0G0hhhhL(lam1,cplG0G0hhhh)



cplG0G0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0HpcHpL(gt3,gt4,lam1,lam4,lam3,ZP,cplG0G0HpcHp(gt3,gt4))

 End Do 
End Do 


cplG0G0cVWpVWp = 0._dp 
Call CouplingG0G0cVWpVWpL(g2,cplG0G0cVWpVWp)



cplG0G0VZVZ = 0._dp 
Call CouplingG0G0VZVZL(g1,g2,TW,cplG0G0VZVZ)



cplA0A0hh = 0._dp 
Call CouplingA0A0hhL(lam5,lam3,v,cplA0A0hh)



cplA0H0hh = 0._dp 
Call CouplingA0H0hhL(lam5,v,cplA0H0hh)



cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehhL(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcgWpgWphh = 0._dp 
Call CouplingcgWpgWphhL(g2,v,cplcgWpgWphh)



cplcgWCgWChh = 0._dp 
Call CouplingcgWCgWChhL(g2,v,cplcgWCgWChh)



cplcgZgZhh = 0._dp 
Call CouplingcgZgZhhL(g1,g2,v,TW,cplcgZgZhh)



cplH0H0hh = 0._dp 
Call CouplingH0H0hhL(lam5,lam3,v,cplH0H0hh)



cplhhhhhh = 0._dp 
Call CouplinghhhhhhL(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpL(gt2,g2,ZP,cplhhHpcVWp(gt2))

End Do 


cplhhcVWpVWp = 0._dp 
Call CouplinghhcVWpVWpL(g2,v,cplhhcVWpVWp)



cplhhVZVZ = 0._dp 
Call CouplinghhVZVZL(g1,g2,v,TW,cplhhVZVZ)



cplA0A0hhhh = 0._dp 
Call CouplingA0A0hhhhL(lam5,lam3,cplA0A0hhhh)



cplH0H0hhhh = 0._dp 
Call CouplingH0H0hhhhL(lam5,lam3,cplH0H0hhhh)



cplhhhhhhhh = 0._dp 
Call CouplinghhhhhhhhL(lam1,cplhhhhhhhh)



cplhhhhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHpL(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp(gt3,gt4))

 End Do 
End Do 


cplhhhhcVWpVWp = 0._dp 
Call CouplinghhhhcVWpVWpL(g2,cplhhhhcVWpVWp)



cplhhhhVZVZ = 0._dp 
Call CouplinghhhhVZVZL(g1,g2,TW,cplhhhhVZVZ)



cplA0H0VZ = 0._dp 
Call CouplingA0H0VZL(g1,g2,TW,cplA0H0VZ)



cplA0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingA0HpcHpL(gt2,gt3,lam5,lam4,v,ZP,cplA0HpcHp(gt2,gt3))

 End Do 
End Do 


cplA0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpL(gt2,g2,ZP,cplA0HpcVWp(gt2))

End Do 


cplA0A0A0A0 = 0._dp 
Call CouplingA0A0A0A0L(lam2,cplA0A0A0A0)



cplA0A0H0H0 = 0._dp 
Call CouplingA0A0H0H0L(lam2,cplA0A0H0H0)



cplA0A0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0HpcHpL(gt3,gt4,lam4,lam3,lam2,ZP,cplA0A0HpcHp(gt3,gt4))

 End Do 
End Do 


cplA0A0cVWpVWp = 0._dp 
Call CouplingA0A0cVWpVWpL(g2,cplA0A0cVWpVWp)



cplA0A0VZVZ = 0._dp 
Call CouplingA0A0VZVZL(g1,g2,TW,cplA0A0VZVZ)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHpL(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpL(gt2,g2,ZP,cplH0HpcVWp(gt2))

End Do 


cplH0H0H0H0 = 0._dp 
Call CouplingH0H0H0H0L(lam2,cplH0H0H0H0)



cplH0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHpL(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0H0cVWpVWp = 0._dp 
Call CouplingH0H0cVWpVWpL(g2,cplH0H0cVWpVWp)



cplH0H0VZVZ = 0._dp 
Call CouplingH0H0VZVZL(g1,g2,TW,cplH0H0VZVZ)



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


cplcgWpgWpVP = 0._dp 
Call CouplingcgWpgWpVPL(g2,TW,cplcgWpgWpVP)



cplcgWCgWCVP = 0._dp 
Call CouplingcgWCgWCVPL(g2,TW,cplcgWCgWCVP)



cplHpcHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVP(gt1,gt2))

 End Do 
End Do 


cplHpcVWpVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVPL(gt1,g1,g2,v,ZP,TW,cplHpcVWpVP(gt1))

End Do 


cplcVWpVPVWp = 0._dp 
Call CouplingcVWpVPVWpL(g2,TW,cplcVWpVPVWp)



cplHpcHpVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWpVPVPVWp1 = 0._dp 
cplcVWpVPVPVWp2 = 0._dp 
cplcVWpVPVPVWp3 = 0._dp 
Call CouplingcVWpVPVPVWpL(g2,TW,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3)



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


cplcgWpgWpVZ = 0._dp 
Call CouplingcgWpgWpVZL(g2,TW,cplcgWpgWpVZ)



cplcgWCgWCVZ = 0._dp 
Call CouplingcgWCgWCVZL(g2,TW,cplcgWCgWCVZ)



cplHpcHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZ(gt1,gt2))

 End Do 
End Do 


cplHpcVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVZL(gt1,g1,g2,v,ZP,TW,cplHpcVWpVZ(gt1))

End Do 


cplcVWpVWpVZ = 0._dp 
Call CouplingcVWpVWpVZL(g2,TW,cplcVWpVWpVZ)



cplHpcHpVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWpVWpVZVZ1 = 0._dp 
cplcVWpVWpVZVZ2 = 0._dp 
cplcVWpVWpVZVZ3 = 0._dp 
Call CouplingcVWpVWpVZVZL(g2,TW,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3)



cplcFdFucVWpL = 0._dp 
cplcFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFucVWpL(gt1,gt2,g2,ZDL,ZUL,cplcFdFucVWpL(gt1,gt2),cplcFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcFeFvcVWpL = 0._dp 
cplcFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvcVWpL(gt1,gt2,g2,ZEL,cplcFeFvcVWpL(gt1,gt2),cplcFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


cplcgWCgAcVWp = 0._dp 
Call CouplingcgWCgAcVWpL(g2,TW,cplcgWCgAcVWp)



cplcgAgWpcVWp = 0._dp 
Call CouplingcgAgWpcVWpL(g2,TW,cplcgAgWpcVWp)



cplcgZgWpcVWp = 0._dp 
Call CouplingcgZgWpcVWpL(g2,TW,cplcgZgWpcVWp)



cplcgWCgZcVWp = 0._dp 
Call CouplingcgWCgZcVWpL(g2,TW,cplcgWCgZcVWp)



cplHpcHpcVWpVWp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpcVWpVWpL(gt1,gt2,g2,ZP,cplHpcHpcVWpVWp(gt1,gt2))

 End Do 
End Do 


cplcVWpcVWpVWpVWp1 = 0._dp 
cplcVWpcVWpVWpVWp2 = 0._dp 
cplcVWpcVWpVWpVWp3 = 0._dp 
Call CouplingcVWpcVWpVWpVWpL(g2,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)



cplcHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVWpVZL(gt1,g1,g2,v,ZP,TW,cplcHpVWpVZ(gt1))

End Do 


cplcHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVPVWpL(gt1,g1,g2,v,ZP,TW,cplcHpVPVWp(gt1))

End Do 


cplHpcHpVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWpVPVWpVZ1 = 0._dp 
cplcVWpVPVWpVZ2 = 0._dp 
cplcVWpVPVWpVZ3 = 0._dp 
Call CouplingcVWpVPVWpVZL(g2,TW,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForLoopMasses

Subroutine CouplingA0HpcUHpL(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcUHp' 
 
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
res = res-(lam4*v*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(lam5*v*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(lam4*v*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(v*Conjg(lam5)*ZP(gt2,2))/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcUHpL  
 
 
Subroutine CouplingA0cUHpVWpL(gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cUHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res-1._dp*(g2)/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0cUHpVWpL  
 
 
Subroutine CouplingcFdFucUHpL(gt1,gt2,gt3,Yd,Yu,ZDL,ZDR,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucUHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Conjg(ZDR(gt1,j2))*Conjg(ZUL(gt2,j1))*Yd(j1,j2)
End Do 
End Do 
End If 
resR = 0._dp 
If ((2.eq.gt3)) Then 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+Conjg(Yu(j1,j2))*ZDL(gt1,j1)*ZUR(gt2,j2)
End Do 
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFucUHpL  
 
 
Subroutine CouplingcFeFvcUHpL(gt1,gt2,gt3,Ye,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcUHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+Conjg(ZER(gt1,j1))*Ye(gt2,j1)
End Do 
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFvcUHpL  
 
 
Subroutine CouplingG0cUHpVWpL(gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cUHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt2)) Then 
res = res-1._dp*(g2)/2._dp
End If 
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0cUHpVWpL  
 
 
Subroutine CouplingcgZgWpcUHpL(gt3,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpcUHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res-(g2**2*v*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1*g2*v*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpcUHpL  
 
 
Subroutine CouplingcgWpgZUHpL(gt3,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgZUHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res+(g2**2*v*Cos(TW)*RXiWp)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1*g2*v*RXiWp*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgZUHpL  
 
 
Subroutine CouplingcgWCgZcUHpL(gt3,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgZcUHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res+(g2**2*v*Cos(TW)*RXiWp)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1*g2*v*RXiWp*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgZcUHpL  
 
 
Subroutine CouplingcgZgWCUHpL(gt3,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt3
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWCUHp' 
 
If ((gt3.Lt.1).Or.(gt3.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt3 out of range', gt3 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt3 out of range', gt3 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt3)) Then 
res = res-(g2**2*v*Cos(TW)*RXiZ)/4._dp
End If 
If ((2.eq.gt3)) Then 
res = res-(g1*g2*v*RXiZ*Sin(TW))/4._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWCUHpL  
 
 
Subroutine CouplingH0HpcUHpL(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcUHp' 
 
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
res = res-(lam4*v*ZP(gt2,1))/2._dp
End If 
If ((2.eq.gt3)) Then 
res = res+(lam5*v*ZP(gt2,1))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*v*ZP(gt2,2))/2._dp
End If 
If ((1.eq.gt3)) Then 
res = res+(v*Conjg(lam5)*ZP(gt2,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcUHpL  
 
 
Subroutine CouplingH0cUHpVWpL(gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cUHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((1.eq.gt2)) Then 
res = res+g2/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0cUHpVWpL  
 
 
Subroutine CouplinghhHpcUHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcUHp' 
 
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
res = res-(lam3*v*ZP(gt2,1))
End If 
If ((1.eq.gt3)) Then 
res = res-(lam4*v*ZP(gt2,1))
End If 
If ((2.eq.gt3)) Then 
res = res-(lam1*v*ZP(gt2,2))
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcUHpL  
 
 
Subroutine CouplinghhcUHpVWpL(gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcUHpVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt2)) Then 
res = res-1._dp*(g2)/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcUHpVWpL  
 
 
Subroutine CouplingHpcUHpVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcUHpVP' 
 
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
res = res+(g1*Cos(TW)*ZP(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res+(g2*Sin(TW)*ZP(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g1*Cos(TW)*ZP(gt1,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g2*Sin(TW)*ZP(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcUHpVPL  
 
 
Subroutine CouplingHpcUHpVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcUHpVZ' 
 
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
res = res+(g2*Cos(TW)*ZP(gt1,1))/2._dp
End If 
If ((1.eq.gt2)) Then 
res = res-(g1*Sin(TW)*ZP(gt1,1))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res+(g2*Cos(TW)*ZP(gt1,2))/2._dp
End If 
If ((2.eq.gt2)) Then 
res = res-(g1*Sin(TW)*ZP(gt1,2))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcUHpVZL  
 
 
Subroutine CouplingcUHpVPVWpL(gt1,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHpVPVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt1)) Then 
res = res-(g1*g2*v*Cos(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHpVPVWpL  
 
 
Subroutine CouplingcUHpVWpVZL(gt1,g1,g2,v,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUHpVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
If ((2.eq.gt1)) Then 
res = res+(g1*g2*v*Sin(TW))/2._dp
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUHpVWpVZL  
 
 
Subroutine CouplingA0A0UHpcUHpL(gt3,gt4,lam4,lam3,lam2,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0UHpcUHp' 
 
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
res = res-1._dp*(lam2)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam3)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam4)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0UHpcUHpL  
 
 
Subroutine CouplingG0G0UHpcUHpL(gt3,gt4,lam1,lam4,lam3,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0UHpcUHp' 
 
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
res = res-1._dp*(lam3)
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-1._dp*(lam4)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam1)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0UHpcUHpL  
 
 
Subroutine CouplingH0H0UHpcUHpL(gt3,gt4,lam4,lam3,lam2,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0UHpcUHp' 
 
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
res = res-1._dp*(lam2)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam3)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam4)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0UHpcUHpL  
 
 
Subroutine CouplinghhhhUHpcUHpL(gt3,gt4,lam1,lam4,lam3,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhUHpcUHp' 
 
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
res = res-1._dp*(lam3)
End If 
If ((1.eq.gt3).And.(1.eq.gt4)) Then 
res = res-1._dp*(lam4)
End If 
If ((2.eq.gt3).And.(2.eq.gt4)) Then 
res = res-1._dp*(lam1)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhUHpcUHpL  
 
 
Subroutine CouplingUHpHpcUHpcHpL(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpHpcUHpcHp' 
 
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
res = res-2*lam2*ZP(gt2,1)*ZP(gt4,1)
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,1)*ZP(gt4,1))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-2*Conjg(lam5)*ZP(gt2,2)*ZP(gt4,1)
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,2)*ZP(gt4,1))
End If 
If ((1.eq.gt3).And.(2.eq.gt1)) Then 
res = res-(lam3*ZP(gt2,1)*ZP(gt4,2))
End If 
If ((1.eq.gt1).And.(2.eq.gt3)) Then 
res = res-2*lam5*ZP(gt2,1)*ZP(gt4,2)
End If 
If ((1.eq.gt1).And.(1.eq.gt3)) Then 
res = res-(lam3*ZP(gt2,2)*ZP(gt4,2))
End If 
If ((2.eq.gt1).And.(2.eq.gt3)) Then 
res = res-2*lam1*ZP(gt2,2)*ZP(gt4,2)
End If 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingUHpHpcUHpcHpL  
 
 
Subroutine CouplingUHpcUHpVPVPL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpcUHpVPVP' 
 
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
 
End Subroutine CouplingUHpcUHpVPVPL  
 
 
Subroutine CouplingUHpcUHpcVWpVWpL(gt1,gt2,g2,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpcUHpcVWpVWp' 
 
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
 
End Subroutine CouplingUHpcUHpcVWpVWpL  
 
 
Subroutine CouplingUHpcUHpVZVZL(gt1,gt2,g1,g2,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingUHpcUHpVZVZ' 
 
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
 
End Subroutine CouplingUHpcUHpVZVZL  
 
 
Subroutine CouplingcUFdFdG0L(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+(Conjg(ZDL(gt2,j1))*Yd(j1,gt1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR-((Conjg(Yd(gt1,j2))*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFdG0L  
 
 
Subroutine CouplingcUFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Yd(j1,gt1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR-((Conjg(Yd(gt1,j2))*ZDR(gt2,j2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcUFdFucHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFucHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+Conjg(ZUL(gt2,j1))*Yd(j1,gt1)*ZP(gt3,2)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR+Conjg(Yu(gt1,j2))*ZP(gt3,2)*ZUR(gt2,j2)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFdFucHpL  
 
 
Subroutine CouplingcUFdFucVWpL(gt1,gt2,g2,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFdFucVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcUFdFucVWpL  
 
 
Subroutine CouplingcUFuFdHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),Yu(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFdHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+Conjg(ZDL(gt2,j1))*Yu(j1,gt1)*ZP(gt3,2)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR+Conjg(Yd(gt1,j2))*ZDR(gt2,j2)*ZP(gt3,2)
End Do 
End If 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFdHpL  
 
 
Subroutine CouplingcUFuFdVWpL(gt1,gt2,g2,ZDL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFdVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcUFuFdVWpL  
 
 
Subroutine CouplingcUFuFuG0L(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Yu(j1,gt1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR-((Conjg(Yu(gt1,j2))*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFuFuG0L  
 
 
Subroutine CouplingcUFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Yu(j1,gt1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR+(Conjg(Yu(gt1,j2))*ZUR(gt2,j2))/sqrt(2._dp)
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
 
 
Subroutine CouplingcUFeFeG0L(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
Do j1 = 1,3
resL = resL+(Conjg(ZEL(gt2,j1))*Ye(j1,gt1))/sqrt(2._dp)
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR-((Conjg(Ye(gt1,j2))*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End If 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFeG0L  
 
 
Subroutine CouplingcUFeFehhL(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Ye(j1,gt1))/sqrt(2._dp))
End Do 
End If 
resR = 0._dp 
If ((gt1.le.3).And.(gt1.ge.1)) Then 
Do j2 = 1,3
resR = resR-((Conjg(Ye(gt1,j2))*ZER(gt2,j2))/sqrt(2._dp))
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
 
 
Subroutine CouplingcUFeFvcHpL(gt1,gt2,gt3,Ye,ZP,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFvcHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+Ye(gt2,gt1)*ZP(gt3,2)
End If 
resR = 0._dp 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFeFvcHpL  
 
 
Subroutine CouplingcUFeFvcVWpL(gt1,gt2,g2,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFeFvcVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcUFeFvcVWpL  
 
 
Subroutine CouplingcUFvFeHpL(gt1,gt2,gt3,Ye,ZP,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: Ye(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFeHp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resR = resR+Conjg(Ye(gt1,j1))*ZER(gt2,j1)*ZP(gt3,2)
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcUFvFeHpL  
 
 
Subroutine CouplingcUFvFeVWpL(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcUFvFeVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcUFvFeVWpL  
 
 
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
 
 
Subroutine CouplingA0A0G0L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0' 
 
res = 0._dp 
res = res-(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0L  
 
 
Subroutine CouplingA0G0H0L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H0L  
 
 
Subroutine CouplingcFdFdG0L(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFdG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdG0L  
 
 
Subroutine CouplingcFeFeG0L(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFeG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFeG0L  
 
 
Subroutine CouplingcFuFuG0L(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Complex(dp), Intent(in) :: Yu(3,3),ZUL(3,3),ZUR(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFuFuG0' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
resL = -(0.,1.)*resL 
 
resR = -(0.,1.)*resR 
 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuG0L  
 
 
Subroutine CouplingG0G0hhL(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hh' 
 
res = 0._dp 
res = res-(lam1*v)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhL  
 
 
Subroutine CouplingcgWpgWpG0L(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpG0' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpG0L  
 
 
Subroutine CouplingcgWCgWCG0L(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCG0' 
 
res = 0._dp 
res = res+(g2**2*v*RXiWp)/4._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCG0L  
 
 
Subroutine CouplingG0H0H0L(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H0L  
 
 
Subroutine CouplingG0hhVZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0hhVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))/2._dp
res = res-(g1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0hhVZL  
 
 
Subroutine CouplingG0HpcVWpL(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpL  
 
 
Subroutine CouplingA0A0G0G0L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0G0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0G0L  
 
 
Subroutine CouplingG0G0G0G0L(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0G0G0' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0G0G0L  
 
 
Subroutine CouplingG0G0H0H0L(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0H0H0L  
 
 
Subroutine CouplingG0G0hhhhL(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhhhL  
 
 
Subroutine CouplingG0G0HpcHpL(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0HpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0HpcHpL  
 
 
Subroutine CouplingG0G0cVWpVWpL(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0cVWpVWpL  
 
 
Subroutine CouplingG0G0VZVZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0VZVZL  
 
 
Subroutine CouplingA0A0hhL(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res+(lam5*v)/2._dp
res = res+(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhL  
 
 
Subroutine CouplingA0H0hhL(lam5,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hh' 
 
res = 0._dp 
res = res+(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hhL  
 
 
Subroutine CouplingcFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZDL(gt2,j1))*Conjg(ZDR(gt1,j2))*Yd(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Yd(j1,j2))*ZDL(gt1,j1)*ZDR(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFdFdhhL  
 
 
Subroutine CouplingcFeFehhL(gt1,gt2,Ye,ZEL,ZER,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL-((Conjg(ZEL(gt2,j1))*Conjg(ZER(gt1,j2))*Ye(j1,j2))/sqrt(2._dp))
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR-((Conjg(Ye(j1,j2))*ZEL(gt1,j1)*ZER(gt2,j2))/sqrt(2._dp))
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFeFehhL  
 
 
Subroutine CouplingcFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
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

resL = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resL = resL+(Conjg(ZUL(gt2,j1))*Conjg(ZUR(gt1,j2))*Yu(j1,j2))/sqrt(2._dp)
End Do 
End Do 
resR = 0._dp 
Do j2 = 1,3
Do j1 = 1,3
resR = resR+(Conjg(Yu(j1,j2))*ZUL(gt1,j1)*ZUR(gt2,j2))/sqrt(2._dp)
End Do 
End Do 
If ((Real(resL,dp).ne.Real(resL,dp)).or.(Real(resR,dp).ne.Real(resR,dp))) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcFuFuhhL  
 
 
Subroutine CouplingcgWpgWphhL(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWphh' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWphhL  
 
 
Subroutine CouplingcgWCgWChhL(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWChh' 
 
res = 0._dp 
res = res-(g2**2*v*RXiWp)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWChhL  
 
 
Subroutine CouplingcgZgZhhL(g1,g2,v,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgZhh' 
 
res = 0._dp 
res = res-(g2**2*v*Cos(TW)**2*RXiZ)/4._dp
res = res-(g1*g2*v*Cos(TW)*RXiZ*Sin(TW))/2._dp
res = res-(g1**2*v*RXiZ*Sin(TW)**2)/4._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgZhhL  
 
 
Subroutine CouplingH0H0hhL(lam5,lam3,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hh' 
 
res = 0._dp 
res = res-(lam3*v)
res = res-(lam5*v)/2._dp
res = res-(v*Conjg(lam5))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhL  
 
 
Subroutine CouplinghhhhhhL(lam1,v,res)

Implicit None 

Real(dp), Intent(in) :: v

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhh' 
 
res = 0._dp 
res = res-3*lam1*v
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhL  
 
 
Subroutine CouplinghhHpcHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcHp' 
 
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
res = res-(lam3*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,1))
res = res-(lam1*v*ZP(gt2,2)*ZP(gt3,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcHpL  
 
 
Subroutine CouplinghhHpcVWpL(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g2*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpL  
 
 
Subroutine CouplinghhcVWpVWpL(g2,v,res)

Implicit None 

Real(dp), Intent(in) :: g2,v

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcVWpVWp' 
 
res = 0._dp 
res = res+(g2**2*v)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhcVWpVWpL  
 
 
Subroutine CouplinghhVZVZL(g1,g2,v,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,v,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhVZVZ' 
 
res = 0._dp 
res = res+(g2**2*v*Cos(TW)**2)/2._dp
res = res+g1*g2*v*Cos(TW)*Sin(TW)
res = res+(g1**2*v*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhVZVZL  
 
 
Subroutine CouplingA0A0hhhhL(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res+lam5/2._dp
res = res+Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhhhL  
 
 
Subroutine CouplingH0H0hhhhL(lam5,lam3,res)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hhhh' 
 
res = 0._dp 
res = res-1._dp*(lam3)
res = res-1._dp*(lam5)/2._dp
res = res-Conjg(lam5)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhhhL  
 
 
Subroutine CouplinghhhhhhhhL(lam1,res)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
res = 0._dp 
res = res-3._dp*(lam1)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhL  
 
 
Subroutine CouplinghhhhHpcHpL(gt3,gt4,lam1,lam4,lam3,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpcHp' 
 
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
res = res-(lam3*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam4*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam1*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpcHpL  
 
 
Subroutine CouplinghhhhcVWpVWpL(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWpVWpL  
 
 
Subroutine CouplinghhhhVZVZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZL  
 
 
Subroutine CouplingA0H0VZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0VZ' 
 
res = 0._dp 
res = res+(g2*Cos(TW))/2._dp
res = res+(g1*Sin(TW))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0VZL  
 
 
Subroutine CouplingA0HpcHpL(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcHp' 
 
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
res = res+(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res-(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcHpL  
 
 
Subroutine CouplingA0HpcVWpL(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,1))/2._dp
res = -(0.,1.)*res 
 
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpL  
 
 
Subroutine CouplingA0A0A0A0L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0A0A0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0A0A0L  
 
 
Subroutine CouplingA0A0H0H0L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0H0H0' 
 
res = 0._dp 
res = res-1._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0H0H0L  
 
 
Subroutine CouplingA0A0HpcHpL(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0HpcHpL  
 
 
Subroutine CouplingA0A0cVWpVWpL(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0cVWpVWpL  
 
 
Subroutine CouplingA0A0VZVZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0VZVZL  
 
 
Subroutine CouplingH0HpcHpL(gt2,gt3,lam5,lam4,v,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2,gt3
Real(dp), Intent(in) :: v,ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcHp' 
 
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
res = res-(lam4*v*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res+(v*Conjg(lam5)*ZP(gt2,2)*ZP(gt3,1))/2._dp
res = res-(lam4*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
res = res+(lam5*v*ZP(gt2,1)*ZP(gt3,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcHpL  
 
 
Subroutine CouplingH0HpcVWpL(gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g2*ZP(gt2,1))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpL  
 
 
Subroutine CouplingH0H0H0H0L(lam2,res)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0H0H0' 
 
res = 0._dp 
res = res-3._dp*(lam2)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0H0H0L  
 
 
Subroutine CouplingH0H0HpcHpL(gt3,gt4,lam4,lam3,lam2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0HpcHp' 
 
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
res = res-(lam2*ZP(gt3,1)*ZP(gt4,1))
res = res-(lam3*ZP(gt3,2)*ZP(gt4,2))
res = res-(lam4*ZP(gt3,2)*ZP(gt4,2))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0HpcHpL  
 
 
Subroutine CouplingH0H0cVWpVWpL(g2,res)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0cVWpVWp' 
 
res = 0._dp 
res = res+g2**2/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0cVWpVWpL  
 
 
Subroutine CouplingH0H0VZVZL(g1,g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0VZVZ' 
 
res = 0._dp 
res = res+(g2**2*Cos(TW)**2)/2._dp
res = res+g1*g2*Cos(TW)*Sin(TW)
res = res+(g1**2*Sin(TW)**2)/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0VZVZL  
 
 
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
 
 
Subroutine CouplingcgWpgWpVPL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpVP' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpVPL  
 
 
Subroutine CouplingcgWCgWCVPL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCVP' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCVPL  
 
 
Subroutine CouplingHpcHpVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVP' 
 
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
res = res+(g1*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g1*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res+(g2*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcHpVPL  
 
 
Subroutine CouplingHpcVWpVPL(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcVWpVP' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcVWpVPL  
 
 
Subroutine CouplingcVWpVPVWpL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVWp' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVPVWpL  
 
 
Subroutine CouplingHpcHpVPVPL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVP' 
 
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
 
End Subroutine CouplingHpcHpVPVPL  
 
 
Subroutine CouplingcVWpVPVPVWpL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVPVWp' 
 
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
 
End Subroutine CouplingcVWpVPVPVWpL  
 
 
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
 
 
Subroutine CouplingcgWpgWpVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWpgWpVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWpgWpVZL  
 
 
Subroutine CouplingcgWCgWCVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgWCVZ' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgWCVZL  
 
 
Subroutine CouplingHpcHpVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVZ' 
 
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
res = res+(g2*Cos(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res-(g1*Sin(TW)*ZP(gt1,1)*ZP(gt2,1))/2._dp
res = res+(g2*Cos(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
res = res-(g1*Sin(TW)*ZP(gt1,2)*ZP(gt2,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcHpVZL  
 
 
Subroutine CouplingHpcVWpVZL(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingHpcVWpVZL  
 
 
Subroutine CouplingcVWpVWpVZL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVWpVZ' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVWpVZL  
 
 
Subroutine CouplingHpcHpVZVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVZVZ' 
 
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
 
End Subroutine CouplingHpcHpVZVZL  
 
 
Subroutine CouplingcVWpVWpVZVZL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVWpVZVZ' 
 
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
 
End Subroutine CouplingcVWpVWpVZVZL  
 
 
Subroutine CouplingcFdFucVWpL(gt1,gt2,g2,ZDL,ZUL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFdFucVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFdFucVWpL  
 
 
Subroutine CouplingcFeFvcVWpL(gt1,gt2,g2,ZEL,resL,resR)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2

Complex(dp), Intent(in) :: ZEL(3,3)

Complex(dp), Intent(out) :: resL, resR 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcFeFvcVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.3)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
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
 
End Subroutine CouplingcFeFvcVWpL  
 
 
Subroutine CouplingcgWCgAcVWpL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgAcVWp' 
 
res = 0._dp 
res = res+g2*Sin(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgAcVWpL  
 
 
Subroutine CouplingcgAgWpcVWpL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgAgWpcVWp' 
 
res = 0._dp 
res = res-(g2*Sin(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgAgWpcVWpL  
 
 
Subroutine CouplingcgZgWpcVWpL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgZgWpcVWp' 
 
res = 0._dp 
res = res-(g2*Cos(TW))
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgZgWpcVWpL  
 
 
Subroutine CouplingcgWCgZcVWpL(g2,TW,res)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcgWCgZcVWp' 
 
res = 0._dp 
res = res+g2*Cos(TW)
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcgWCgZcVWpL  
 
 
Subroutine CouplingHpcHpcVWpVWpL(gt1,gt2,g2,ZP,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpcVWpVWp' 
 
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
 
End Subroutine CouplingHpcHpcVWpVWpL  
 
 
Subroutine CouplingcVWpcVWpVWpVWpL(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpcVWpVWpVWp' 
 
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
 
End Subroutine CouplingcVWpcVWpVWpVWpL  
 
 
Subroutine CouplingcHpVWpVZL(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpVWpVZ' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res+(g1*g2*v*Sin(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpVWpVZL  
 
 
Subroutine CouplingcHpVPVWpL(gt1,g1,g2,v,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1
Real(dp), Intent(in) :: g1,g2,v,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcHpVPVWp' 
 
If ((gt1.Lt.1).Or.(gt1.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt1 out of range', gt1 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt1 out of range', gt1 
  Call TerminateProgram 
End If 

res = 0._dp 
res = res-(g1*g2*v*Cos(TW)*ZP(gt1,2))/2._dp
If (Real(res,dp).ne.Real(res,dp)) Then 
 Write(*,*) "NaN appearing in ",NameOfUnit(Iname) 
 Call TerminateProgram 
End If 


Iname = Iname - 1 
 
End Subroutine CouplingcHpVPVWpL  
 
 
Subroutine CouplingHpcHpVPVZL(gt1,gt2,g1,g2,ZP,TW,res)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVZ' 
 
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
 
End Subroutine CouplingHpcHpVPVZL  
 
 
Subroutine CouplingcVWpVPVWpVZL(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1, res2, res3 
 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVWpVZ' 
 
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
 
End Subroutine CouplingcVWpVPVWpVZL  
 
 
Subroutine CouplingsForVectorBosons(g1,g2,TW,ZP,v,ZDL,ZUL,ZEL,cplG0hhVZ,              & 
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
& cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)

Implicit None 
Real(dp), Intent(in) :: g1,g2,TW,ZP(2,2),v

Complex(dp), Intent(in) :: ZDL(3,3),ZUL(3,3),ZEL(3,3)

Complex(dp), Intent(out) :: cplG0hhVZ,cplG0HpcVWp(2),cplG0G0cVWpVWp,cplG0G0VZVZ,cplhhHpcVWp(2),cplhhcVWpVWp,      & 
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

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForVectorBosons'
 
cplG0hhVZ = 0._dp 
Call CouplingG0hhVZL(g1,g2,TW,cplG0hhVZ)



cplG0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpL(gt2,g2,ZP,cplG0HpcVWp(gt2))

End Do 


cplG0G0cVWpVWp = 0._dp 
Call CouplingG0G0cVWpVWpL(g2,cplG0G0cVWpVWp)



cplG0G0VZVZ = 0._dp 
Call CouplingG0G0VZVZL(g1,g2,TW,cplG0G0VZVZ)



cplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpL(gt2,g2,ZP,cplhhHpcVWp(gt2))

End Do 


cplhhcVWpVWp = 0._dp 
Call CouplinghhcVWpVWpL(g2,v,cplhhcVWpVWp)



cplhhVZVZ = 0._dp 
Call CouplinghhVZVZL(g1,g2,v,TW,cplhhVZVZ)



cplhhhhcVWpVWp = 0._dp 
Call CouplinghhhhcVWpVWpL(g2,cplhhhhcVWpVWp)



cplhhhhVZVZ = 0._dp 
Call CouplinghhhhVZVZL(g1,g2,TW,cplhhhhVZVZ)



cplA0H0VZ = 0._dp 
Call CouplingA0H0VZL(g1,g2,TW,cplA0H0VZ)



cplA0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpL(gt2,g2,ZP,cplA0HpcVWp(gt2))

End Do 


cplA0A0cVWpVWp = 0._dp 
Call CouplingA0A0cVWpVWpL(g2,cplA0A0cVWpVWp)



cplA0A0VZVZ = 0._dp 
Call CouplingA0A0VZVZL(g1,g2,TW,cplA0A0VZVZ)



cplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpL(gt2,g2,ZP,cplH0HpcVWp(gt2))

End Do 


cplH0H0cVWpVWp = 0._dp 
Call CouplingH0H0cVWpVWpL(g2,cplH0H0cVWpVWp)



cplH0H0VZVZ = 0._dp 
Call CouplingH0H0VZVZL(g1,g2,TW,cplH0H0VZVZ)



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


cplcgWpgWpVP = 0._dp 
Call CouplingcgWpgWpVPL(g2,TW,cplcgWpgWpVP)



cplcgWCgWCVP = 0._dp 
Call CouplingcgWCgWCVPL(g2,TW,cplcgWCgWCVP)



cplHpcHpVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVP(gt1,gt2))

 End Do 
End Do 


cplHpcVWpVP = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVPL(gt1,g1,g2,v,ZP,TW,cplHpcVWpVP(gt1))

End Do 


cplcVWpVPVWp = 0._dp 
Call CouplingcVWpVPVWpL(g2,TW,cplcVWpVPVWp)



cplHpcHpVPVP = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVPL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVP(gt1,gt2))

 End Do 
End Do 


cplcVWpVPVPVWp1 = 0._dp 
cplcVWpVPVPVWp2 = 0._dp 
cplcVWpVPVPVWp3 = 0._dp 
Call CouplingcVWpVPVPVWpL(g2,TW,cplcVWpVPVPVWp1,cplcVWpVPVPVWp2,cplcVWpVPVPVWp3)



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


cplcgWpgWpVZ = 0._dp 
Call CouplingcgWpgWpVZL(g2,TW,cplcgWpgWpVZ)



cplcgWCgWCVZ = 0._dp 
Call CouplingcgWCgWCVZL(g2,TW,cplcgWCgWCVZ)



cplHpcHpVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZ(gt1,gt2))

 End Do 
End Do 


cplHpcVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingHpcVWpVZL(gt1,g1,g2,v,ZP,TW,cplHpcVWpVZ(gt1))

End Do 


cplcVWpVWpVZ = 0._dp 
Call CouplingcVWpVWpVZL(g2,TW,cplcVWpVWpVZ)



cplHpcHpVZVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZVZ(gt1,gt2))

 End Do 
End Do 


cplcVWpVWpVZVZ1 = 0._dp 
cplcVWpVWpVZVZ2 = 0._dp 
cplcVWpVWpVZVZ3 = 0._dp 
Call CouplingcVWpVWpVZVZL(g2,TW,cplcVWpVWpVZVZ1,cplcVWpVWpVZVZ2,cplcVWpVWpVZVZ3)



cplcFdFucVWpL = 0._dp 
cplcFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFucVWpL(gt1,gt2,g2,ZDL,ZUL,cplcFdFucVWpL(gt1,gt2),cplcFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcFeFvcVWpL = 0._dp 
cplcFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvcVWpL(gt1,gt2,g2,ZEL,cplcFeFvcVWpL(gt1,gt2),cplcFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


cplcgWCgAcVWp = 0._dp 
Call CouplingcgWCgAcVWpL(g2,TW,cplcgWCgAcVWp)



cplcgAgWpcVWp = 0._dp 
Call CouplingcgAgWpcVWpL(g2,TW,cplcgAgWpcVWp)



cplcgZgWpcVWp = 0._dp 
Call CouplingcgZgWpcVWpL(g2,TW,cplcgZgWpcVWp)



cplcgWCgZcVWp = 0._dp 
Call CouplingcgWCgZcVWpL(g2,TW,cplcgWCgZcVWp)



cplHpcHpcVWpVWp = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpcVWpVWpL(gt1,gt2,g2,ZP,cplHpcHpcVWpVWp(gt1,gt2))

 End Do 
End Do 


cplcVWpcVWpVWpVWp1 = 0._dp 
cplcVWpcVWpVWpVWp2 = 0._dp 
cplcVWpcVWpVWpVWp3 = 0._dp 
Call CouplingcVWpcVWpVWpVWpL(g2,cplcVWpcVWpVWpVWp1,cplcVWpcVWpVWpVWp2,cplcVWpcVWpVWpVWp3)



cplcHpVWpVZ = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVWpVZL(gt1,g1,g2,v,ZP,TW,cplcHpVWpVZ(gt1))

End Do 


cplcHpVPVWp = 0._dp 
Do gt1 = 1, 2
Call CouplingcHpVPVWpL(gt1,g1,g2,v,ZP,TW,cplcHpVPVWp(gt1))

End Do 


cplHpcHpVPVZ = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVZL(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVZ(gt1,gt2))

 End Do 
End Do 


cplcVWpVPVWpVZ1 = 0._dp 
cplcVWpVPVWpVZ2 = 0._dp 
cplcVWpVPVWpVZ3 = 0._dp 
Call CouplingcVWpVPVWpVZL(g2,TW,cplcVWpVPVWpVZ1,cplcVWpVPVWpVZ2,cplcVWpVPVWpVZ3)



Iname = Iname - 1 
End Subroutine CouplingsForVectorBosons

Subroutine CouplingsForSMfermions(Yd,ZDL,ZDR,g3,g1,g2,TW,Yu,ZP,ZUL,ZUR,               & 
& Ye,ZEL,ZER,cplcUFdFdG0L,cplcUFdFdG0R,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFdFdVGL,           & 
& cplcUFdFdVGR,cplcUFdFdVPL,cplcUFdFdVPR,cplcUFdFdVZL,cplcUFdFdVZR,cplcUFdFucHpL,        & 
& cplcUFdFucHpR,cplcUFdFucVWpL,cplcUFdFucVWpR,cplcUFuFdHpL,cplcUFuFdHpR,cplcUFuFdVWpL,   & 
& cplcUFuFdVWpR,cplcUFuFuG0L,cplcUFuFuG0R,cplcUFuFuhhL,cplcUFuFuhhR,cplcUFuFuVGL,        & 
& cplcUFuFuVGR,cplcUFuFuVPL,cplcUFuFuVPR,cplcUFuFuVZL,cplcUFuFuVZR,cplcUFeFeG0L,         & 
& cplcUFeFeG0R,cplcUFeFehhL,cplcUFeFehhR,cplcUFeFeVPL,cplcUFeFeVPR,cplcUFeFeVZL,         & 
& cplcUFeFeVZR,cplcUFeFvcHpL,cplcUFeFvcHpR,cplcUFeFvcVWpL,cplcUFeFvcVWpR)

Implicit None 
Real(dp), Intent(in) :: g3,g1,g2,TW,ZP(2,2)

Complex(dp), Intent(in) :: Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplcUFdFdG0L(3,3),cplcUFdFdG0R(3,3),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),              & 
& cplcUFdFdVGL(3,3),cplcUFdFdVGR(3,3),cplcUFdFdVPL(3,3),cplcUFdFdVPR(3,3),               & 
& cplcUFdFdVZL(3,3),cplcUFdFdVZR(3,3),cplcUFdFucHpL(3,3,2),cplcUFdFucHpR(3,3,2),         & 
& cplcUFdFucVWpL(3,3),cplcUFdFucVWpR(3,3),cplcUFuFdHpL(3,3,2),cplcUFuFdHpR(3,3,2),       & 
& cplcUFuFdVWpL(3,3),cplcUFuFdVWpR(3,3),cplcUFuFuG0L(3,3),cplcUFuFuG0R(3,3),             & 
& cplcUFuFuhhL(3,3),cplcUFuFuhhR(3,3),cplcUFuFuVGL(3,3),cplcUFuFuVGR(3,3),               & 
& cplcUFuFuVPL(3,3),cplcUFuFuVPR(3,3),cplcUFuFuVZL(3,3),cplcUFuFuVZR(3,3),               & 
& cplcUFeFeG0L(3,3),cplcUFeFeG0R(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),               & 
& cplcUFeFeVPL(3,3),cplcUFeFeVPR(3,3),cplcUFeFeVZL(3,3),cplcUFeFeVZR(3,3),               & 
& cplcUFeFvcHpL(3,3,2),cplcUFeFvcHpR(3,3,2),cplcUFeFvcVWpL(3,3),cplcUFeFvcVWpR(3,3)

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForSMfermions'
 
cplcUFdFdG0L = 0._dp 
cplcUFdFdG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdG0L(gt1,gt2,Yd,ZDL,ZDR,cplcUFdFdG0L(gt1,gt2),cplcUFdFdG0R(gt1,gt2))

 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,cplcUFdFdhhL(gt1,gt2),cplcUFdFdhhR(gt1,gt2))

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


cplcUFdFucHpL = 0._dp 
cplcUFdFucHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFdFucHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZUL,ZUR,cplcUFdFucHpL(gt1,gt2,gt3)       & 
& ,cplcUFdFucHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFdFucVWpL = 0._dp 
cplcUFdFucVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFucVWpL(gt1,gt2,g2,ZUL,cplcUFdFucVWpL(gt1,gt2),cplcUFdFucVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFuFdHpL = 0._dp 
cplcUFuFdHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFuFdHpL(gt1,gt2,gt3,Yd,Yu,ZP,ZDL,ZDR,cplcUFuFdHpL(gt1,gt2,gt3)         & 
& ,cplcUFuFdHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFuFdVWpL = 0._dp 
cplcUFuFdVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFdVWpL(gt1,gt2,g2,ZDL,cplcUFuFdVWpL(gt1,gt2),cplcUFuFdVWpR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuG0L = 0._dp 
cplcUFuFuG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuG0L(gt1,gt2,Yu,ZUL,ZUR,cplcUFuFuG0L(gt1,gt2),cplcUFuFuG0R(gt1,gt2))

 End Do 
End Do 


cplcUFuFuhhL = 0._dp 
cplcUFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,cplcUFuFuhhL(gt1,gt2),cplcUFuFuhhR(gt1,gt2))

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


cplcUFeFeG0L = 0._dp 
cplcUFeFeG0R = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFeG0L(gt1,gt2,Ye,ZEL,ZER,cplcUFeFeG0L(gt1,gt2),cplcUFeFeG0R(gt1,gt2))

 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFehhL(gt1,gt2,Ye,ZEL,ZER,cplcUFeFehhL(gt1,gt2),cplcUFeFehhR(gt1,gt2))

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


cplcUFeFvcHpL = 0._dp 
cplcUFeFvcHpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
  Do gt3 = 1, 2
Call CouplingcUFeFvcHpL(gt1,gt2,gt3,Ye,ZP,cplcUFeFvcHpL(gt1,gt2,gt3),cplcUFeFvcHpR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcUFeFvcVWpL = 0._dp 
cplcUFeFvcVWpR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFvcVWpL(gt1,gt2,g2,cplcUFeFvcVWpL(gt1,gt2),cplcUFeFvcVWpR(gt1,gt2))

 End Do 
End Do 


Iname = Iname - 1 
End Subroutine CouplingsForSMfermions

Subroutine CouplingsForTadpoles(lam5,lam4,v,ZP,g2,lam1,lam3,lam2,Yd,ZDL,              & 
& ZDR,Yu,ZUL,ZUR,Ye,ZEL,ZER,g1,TW,cplH0HpcUHp,cplH0cUHpVWp,cplhhHpcUHp,cplhhcUHpVWp,     & 
& cplH0H0UHpcUHp,cplhhhhUHpcUHp,cplcUFdFdhhL,cplcUFdFdhhR,cplcUFuFuhhL,cplcUFuFuhhR,     & 
& cplcUFeFehhL,cplcUFeFehhR,cplA0G0H0,cplG0G0hh,cplG0H0H0,cplG0hhVZ,cplG0G0H0H0,         & 
& cplG0G0hhhh,cplA0A0hh,cplA0H0hh,cplcFdFdhhL,cplcFdFdhhR,cplcFeFehhL,cplcFeFehhR,       & 
& cplcFuFuhhL,cplcFuFuhhR,cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,      & 
& cplhhHpcHp,cplhhHpcVWp,cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplH0H0hhhh,cplhhhhhhhh,     & 
& cplhhhhHpcHp,cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0A0H0H0,cplH0HpcHp,              & 
& cplH0HpcVWp,cplH0H0H0H0,cplH0H0HpcHp,cplH0H0cVWpVWp,cplH0H0VZVZ)

Implicit None 
Real(dp), Intent(in) :: v,ZP(2,2),g2,g1,TW

Complex(dp), Intent(in) :: lam5,lam4,lam1,lam3,lam2,Yd(3,3),ZDL(3,3),ZDR(3,3),Yu(3,3),ZUL(3,3),ZUR(3,3),         & 
& Ye(3,3),ZEL(3,3),ZER(3,3)

Complex(dp), Intent(out) :: cplH0HpcUHp(2,2),cplH0cUHpVWp(2),cplhhHpcUHp(2,2),cplhhcUHpVWp(2),cplH0H0UHpcUHp(2,2),& 
& cplhhhhUHpcUHp(2,2),cplcUFdFdhhL(3,3),cplcUFdFdhhR(3,3),cplcUFuFuhhL(3,3),             & 
& cplcUFuFuhhR(3,3),cplcUFeFehhL(3,3),cplcUFeFehhR(3,3),cplA0G0H0,cplG0G0hh,             & 
& cplG0H0H0,cplG0hhVZ,cplG0G0H0H0,cplG0G0hhhh,cplA0A0hh,cplA0H0hh,cplcFdFdhhL(3,3),      & 
& cplcFdFdhhR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),  & 
& cplcgWpgWphh,cplcgWCgWChh,cplcgZgZhh,cplH0H0hh,cplhhhhhh,cplhhHpcHp(2,2),              & 
& cplhhHpcVWp(2),cplhhcVWpVWp,cplhhVZVZ,cplA0A0hhhh,cplH0H0hhhh,cplhhhhhhhh,             & 
& cplhhhhHpcHp(2,2),cplhhhhcVWpVWp,cplhhhhVZVZ,cplA0H0VZ,cplA0A0H0H0,cplH0HpcHp(2,2),    & 
& cplH0HpcVWp(2),cplH0H0H0H0,cplH0H0HpcHp(2,2),cplH0H0cVWpVWp,cplH0H0VZVZ

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsForTadpoles'
 
cplH0HpcUHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcUHpL(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcUHp(gt2,gt3))

 End Do 
End Do 


cplH0cUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cUHpVWpL(gt2,g2,cplH0cUHpVWp(gt2))

End Do 


cplhhHpcUHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcUHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcUHp(gt2,gt3))

 End Do 
End Do 


cplhhcUHpVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcUHpVWpL(gt2,g2,cplhhcUHpVWp(gt2))

End Do 


cplH0H0UHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0UHpcUHpL(gt3,gt4,lam4,lam3,lam2,cplH0H0UHpcUHp(gt3,gt4))

 End Do 
End Do 


cplhhhhUHpcUHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhUHpcUHpL(gt3,gt4,lam1,lam4,lam3,cplhhhhUHpcUHp(gt3,gt4))

 End Do 
End Do 


cplcUFdFdhhL = 0._dp 
cplcUFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,cplcUFdFdhhL(gt1,gt2),cplcUFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcUFuFuhhL = 0._dp 
cplcUFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,cplcUFuFuhhL(gt1,gt2),cplcUFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcUFeFehhL = 0._dp 
cplcUFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcUFeFehhL(gt1,gt2,Ye,ZEL,ZER,cplcUFeFehhL(gt1,gt2),cplcUFeFehhR(gt1,gt2))

 End Do 
End Do 


cplA0G0H0 = 0._dp 
Call CouplingA0G0H0L(lam5,v,cplA0G0H0)



cplG0G0hh = 0._dp 
Call CouplingG0G0hhL(lam1,v,cplG0G0hh)



cplG0H0H0 = 0._dp 
Call CouplingG0H0H0L(lam5,v,cplG0H0H0)



cplG0hhVZ = 0._dp 
Call CouplingG0hhVZL(g1,g2,TW,cplG0hhVZ)



cplG0G0H0H0 = 0._dp 
Call CouplingG0G0H0H0L(lam5,lam3,cplG0G0H0H0)



cplG0G0hhhh = 0._dp 
Call CouplingG0G0hhhhL(lam1,cplG0G0hhhh)



cplA0A0hh = 0._dp 
Call CouplingA0A0hhL(lam5,lam3,v,cplA0A0hh)



cplA0H0hh = 0._dp 
Call CouplingA0H0hhL(lam5,v,cplA0H0hh)



cplcFdFdhhL = 0._dp 
cplcFdFdhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFdFdhhL(gt1,gt2,Yd,ZDL,ZDR,cplcFdFdhhL(gt1,gt2),cplcFdFdhhR(gt1,gt2))

 End Do 
End Do 


cplcFeFehhL = 0._dp 
cplcFeFehhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFehhL(gt1,gt2,Ye,ZEL,ZER,cplcFeFehhL(gt1,gt2),cplcFeFehhR(gt1,gt2))

 End Do 
End Do 


cplcFuFuhhL = 0._dp 
cplcFuFuhhR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFuFuhhL(gt1,gt2,Yu,ZUL,ZUR,cplcFuFuhhL(gt1,gt2),cplcFuFuhhR(gt1,gt2))

 End Do 
End Do 


cplcgWpgWphh = 0._dp 
Call CouplingcgWpgWphhL(g2,v,cplcgWpgWphh)



cplcgWCgWChh = 0._dp 
Call CouplingcgWCgWChhL(g2,v,cplcgWCgWChh)



cplcgZgZhh = 0._dp 
Call CouplingcgZgZhhL(g1,g2,v,TW,cplcgZgZhh)



cplH0H0hh = 0._dp 
Call CouplingH0H0hhL(lam5,lam3,v,cplH0H0hh)



cplhhhhhh = 0._dp 
Call CouplinghhhhhhL(lam1,v,cplhhhhhh)



cplhhHpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplinghhHpcHpL(gt2,gt3,lam1,lam4,lam3,v,ZP,cplhhHpcHp(gt2,gt3))

 End Do 
End Do 


cplhhHpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpL(gt2,g2,ZP,cplhhHpcVWp(gt2))

End Do 


cplhhcVWpVWp = 0._dp 
Call CouplinghhcVWpVWpL(g2,v,cplhhcVWpVWp)



cplhhVZVZ = 0._dp 
Call CouplinghhVZVZL(g1,g2,v,TW,cplhhVZVZ)



cplA0A0hhhh = 0._dp 
Call CouplingA0A0hhhhL(lam5,lam3,cplA0A0hhhh)



cplH0H0hhhh = 0._dp 
Call CouplingH0H0hhhhL(lam5,lam3,cplH0H0hhhh)



cplhhhhhhhh = 0._dp 
Call CouplinghhhhhhhhL(lam1,cplhhhhhhhh)



cplhhhhHpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHpL(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp(gt3,gt4))

 End Do 
End Do 


cplhhhhcVWpVWp = 0._dp 
Call CouplinghhhhcVWpVWpL(g2,cplhhhhcVWpVWp)



cplhhhhVZVZ = 0._dp 
Call CouplinghhhhVZVZL(g1,g2,TW,cplhhhhVZVZ)



cplA0H0VZ = 0._dp 
Call CouplingA0H0VZL(g1,g2,TW,cplA0H0VZ)



cplA0A0H0H0 = 0._dp 
Call CouplingA0A0H0H0L(lam2,cplA0A0H0H0)



cplH0HpcHp = 0._dp 
Do gt2 = 1, 2
 Do gt3 = 1, 2
Call CouplingH0HpcHpL(gt2,gt3,lam5,lam4,v,ZP,cplH0HpcHp(gt2,gt3))

 End Do 
End Do 


cplH0HpcVWp = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpL(gt2,g2,ZP,cplH0HpcVWp(gt2))

End Do 


cplH0H0H0H0 = 0._dp 
Call CouplingH0H0H0H0L(lam2,cplH0H0H0H0)



cplH0H0HpcHp = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHpL(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp(gt3,gt4))

 End Do 
End Do 


cplH0H0cVWpVWp = 0._dp 
Call CouplingH0H0cVWpVWpL(g2,cplH0H0cVWpVWp)



cplH0H0VZVZ = 0._dp 
Call CouplingH0H0VZVZL(g1,g2,TW,cplH0H0VZVZ)



Iname = Iname - 1 
End Subroutine CouplingsForTadpoles

Subroutine CouplingsColoredQuartics(lam2,lam5,lam3,lam4,ZP,lam1,g2,g1,TW,             & 
& g3,cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1,     & 
& cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1,cplA0H0hhhh1,cplA0hhHpcHp1,cplG0G0G0G01,       & 
& cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1,cplG0H0H0hh1,cplG0H0HpcHp1,cplH0H0H0H01,       & 
& cplH0H0hhhh1,cplH0H0HpcHp1,cplH0hhHpcHp1,cplhhhhhhhh1,cplhhhhHpcHp1,cplHpHpcHpcHp1,    & 
& cplA0A0cVWpVWp1,cplA0A0VZVZ1,cplA0HpcVWpVP1,cplA0HpcVWpVZ1,cplA0cHpVPVWp1,             & 
& cplA0cHpVWpVZ1,cplG0G0cVWpVWp1,cplG0G0VZVZ1,cplG0HpcVWpVP1,cplG0HpcVWpVZ1,             & 
& cplG0cHpVPVWp1,cplG0cHpVWpVZ1,cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0HpcVWpVP1,             & 
& cplH0HpcVWpVZ1,cplH0cHpVPVWp1,cplH0cHpVWpVZ1,cplhhhhcVWpVWp1,cplhhhhVZVZ1,             & 
& cplhhHpcVWpVP1,cplhhHpcVWpVZ1,cplhhcHpVPVWp1,cplhhcHpVWpVZ1,cplHpcHpVPVP1,             & 
& cplHpcHpVPVZ1,cplHpcHpcVWpVWp1,cplHpcHpVZVZ1,cplVGVGVGVG1Q,cplVGVGVGVG2Q,              & 
& cplVGVGVGVG3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,cplcVWpVPVWpVZ1Q,     & 
& cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,             & 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q)

Implicit None 
Real(dp), Intent(in) :: ZP(2,2),g2,g1,TW,g3

Complex(dp), Intent(in) :: lam2,lam5,lam3,lam4,lam1

Complex(dp), Intent(out) :: cplA0A0A0A01,cplA0A0G0G01,cplA0A0G0hh1,cplA0A0H0H01,cplA0A0hhhh1,cplA0A0HpcHp1(2,2),  & 
& cplA0G0G0H01,cplA0G0H0hh1,cplA0G0HpcHp1(2,2),cplA0H0hhhh1,cplA0hhHpcHp1(2,2),          & 
& cplG0G0G0G01,cplG0G0H0H01,cplG0G0hhhh1,cplG0G0HpcHp1(2,2),cplG0H0H0hh1,cplG0H0HpcHp1(2,2),& 
& cplH0H0H0H01,cplH0H0hhhh1,cplH0H0HpcHp1(2,2),cplH0hhHpcHp1(2,2),cplhhhhhhhh1,          & 
& cplhhhhHpcHp1(2,2),cplHpHpcHpcHp1(2,2,2,2),cplA0A0cVWpVWp1,cplA0A0VZVZ1,               & 
& cplA0HpcVWpVP1(2),cplA0HpcVWpVZ1(2),cplA0cHpVPVWp1(2),cplA0cHpVWpVZ1(2),               & 
& cplG0G0cVWpVWp1,cplG0G0VZVZ1,cplG0HpcVWpVP1(2),cplG0HpcVWpVZ1(2),cplG0cHpVPVWp1(2),    & 
& cplG0cHpVWpVZ1(2),cplH0H0cVWpVWp1,cplH0H0VZVZ1,cplH0HpcVWpVP1(2),cplH0HpcVWpVZ1(2),    & 
& cplH0cHpVPVWp1(2),cplH0cHpVWpVZ1(2),cplhhhhcVWpVWp1,cplhhhhVZVZ1,cplhhHpcVWpVP1(2),    & 
& cplhhHpcVWpVZ1(2),cplhhcHpVPVWp1(2),cplhhcHpVWpVZ1(2),cplHpcHpVPVP1(2,2),              & 
& cplHpcHpVPVZ1(2,2),cplHpcHpcVWpVWp1(2,2),cplHpcHpVZVZ1(2,2),cplVGVGVGVG1Q,             & 
& cplVGVGVGVG2Q,cplVGVGVGVG3Q,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q,        & 
& cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,& 
& cplcVWpcVWpVWpVWp3Q,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q

Integer :: gt1, gt2, gt3, gt4, ct1, ct2, ct3, ct4

Iname = Iname + 1 
NameOfUnit(Iname) = 'CouplingsColoredQuartics'
 
cplA0A0A0A01 = 0._dp 
Call CouplingA0A0A0A0Q(lam2,cplA0A0A0A01)



cplA0A0G0G01 = 0._dp 
Call CouplingA0A0G0G0Q(lam5,lam3,cplA0A0G0G01)



cplA0A0G0hh1 = 0._dp 
Call CouplingA0A0G0hhQ(lam5,cplA0A0G0hh1)



cplA0A0H0H01 = 0._dp 
Call CouplingA0A0H0H0Q(lam2,cplA0A0H0H01)



cplA0A0hhhh1 = 0._dp 
Call CouplingA0A0hhhhQ(lam5,lam3,cplA0A0hhhh1)



cplA0A0HpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0A0HpcHpQ(gt3,gt4,lam4,lam3,lam2,ZP,cplA0A0HpcHp1(gt3,gt4))

 End Do 
End Do 


cplA0G0G0H01 = 0._dp 
Call CouplingA0G0G0H0Q(lam5,cplA0G0G0H01)



cplA0G0H0hh1 = 0._dp 
Call CouplingA0G0H0hhQ(lam5,cplA0G0H0hh1)



cplA0G0HpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0G0HpcHpQ(gt3,gt4,lam5,lam4,ZP,cplA0G0HpcHp1(gt3,gt4))

 End Do 
End Do 


cplA0H0hhhh1 = 0._dp 
Call CouplingA0H0hhhhQ(lam5,cplA0H0hhhh1)



cplA0hhHpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingA0hhHpcHpQ(gt3,gt4,lam5,lam4,ZP,cplA0hhHpcHp1(gt3,gt4))

 End Do 
End Do 


cplG0G0G0G01 = 0._dp 
Call CouplingG0G0G0G0Q(lam1,cplG0G0G0G01)



cplG0G0H0H01 = 0._dp 
Call CouplingG0G0H0H0Q(lam5,lam3,cplG0G0H0H01)



cplG0G0hhhh1 = 0._dp 
Call CouplingG0G0hhhhQ(lam1,cplG0G0hhhh1)



cplG0G0HpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0G0HpcHpQ(gt3,gt4,lam1,lam4,lam3,ZP,cplG0G0HpcHp1(gt3,gt4))

 End Do 
End Do 


cplG0H0H0hh1 = 0._dp 
Call CouplingG0H0H0hhQ(lam5,cplG0H0H0hh1)



cplG0H0HpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingG0H0HpcHpQ(gt3,gt4,lam5,lam4,ZP,cplG0H0HpcHp1(gt3,gt4))

 End Do 
End Do 


cplH0H0H0H01 = 0._dp 
Call CouplingH0H0H0H0Q(lam2,cplH0H0H0H01)



cplH0H0hhhh1 = 0._dp 
Call CouplingH0H0hhhhQ(lam5,lam3,cplH0H0hhhh1)



cplH0H0HpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0H0HpcHpQ(gt3,gt4,lam4,lam3,lam2,ZP,cplH0H0HpcHp1(gt3,gt4))

 End Do 
End Do 


cplH0hhHpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplingH0hhHpcHpQ(gt3,gt4,lam5,lam4,ZP,cplH0hhHpcHp1(gt3,gt4))

 End Do 
End Do 


cplhhhhhhhh1 = 0._dp 
Call CouplinghhhhhhhhQ(lam1,cplhhhhhhhh1)



cplhhhhHpcHp1 = 0._dp 
Do gt3 = 1, 2
 Do gt4 = 1, 2
Call CouplinghhhhHpcHpQ(gt3,gt4,lam1,lam4,lam3,ZP,cplhhhhHpcHp1(gt3,gt4))

 End Do 
End Do 


cplHpHpcHpcHp1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
  Do gt3 = 1, 2
   Do gt4 = 1, 2
Call CouplingHpHpcHpcHpQ(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,cplHpHpcHpcHp1(gt1,gt2,gt3,gt4))

   End Do 
  End Do 
 End Do 
End Do 


cplA0A0cVWpVWp1 = 0._dp 
Call CouplingA0A0cVWpVWpQ(g2,cplA0A0cVWpVWp1)



cplA0A0VZVZ1 = 0._dp 
Call CouplingA0A0VZVZQ(g1,g2,TW,cplA0A0VZVZ1)



cplA0HpcVWpVP1 = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpVPQ(gt2,g1,g2,ZP,TW,cplA0HpcVWpVP1(gt2))

End Do 


cplA0HpcVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingA0HpcVWpVZQ(gt2,g1,g2,ZP,TW,cplA0HpcVWpVZ1(gt2))

End Do 


cplA0cHpVPVWp1 = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVPVWpQ(gt2,g1,g2,ZP,TW,cplA0cHpVPVWp1(gt2))

End Do 


cplA0cHpVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingA0cHpVWpVZQ(gt2,g1,g2,ZP,TW,cplA0cHpVWpVZ1(gt2))

End Do 


cplG0G0cVWpVWp1 = 0._dp 
Call CouplingG0G0cVWpVWpQ(g2,cplG0G0cVWpVWp1)



cplG0G0VZVZ1 = 0._dp 
Call CouplingG0G0VZVZQ(g1,g2,TW,cplG0G0VZVZ1)



cplG0HpcVWpVP1 = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpVPQ(gt2,g1,g2,ZP,TW,cplG0HpcVWpVP1(gt2))

End Do 


cplG0HpcVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingG0HpcVWpVZQ(gt2,g1,g2,ZP,TW,cplG0HpcVWpVZ1(gt2))

End Do 


cplG0cHpVPVWp1 = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVPVWpQ(gt2,g1,g2,ZP,TW,cplG0cHpVPVWp1(gt2))

End Do 


cplG0cHpVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingG0cHpVWpVZQ(gt2,g1,g2,ZP,TW,cplG0cHpVWpVZ1(gt2))

End Do 


cplH0H0cVWpVWp1 = 0._dp 
Call CouplingH0H0cVWpVWpQ(g2,cplH0H0cVWpVWp1)



cplH0H0VZVZ1 = 0._dp 
Call CouplingH0H0VZVZQ(g1,g2,TW,cplH0H0VZVZ1)



cplH0HpcVWpVP1 = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpVPQ(gt2,g1,g2,ZP,TW,cplH0HpcVWpVP1(gt2))

End Do 


cplH0HpcVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingH0HpcVWpVZQ(gt2,g1,g2,ZP,TW,cplH0HpcVWpVZ1(gt2))

End Do 


cplH0cHpVPVWp1 = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVPVWpQ(gt2,g1,g2,ZP,TW,cplH0cHpVPVWp1(gt2))

End Do 


cplH0cHpVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplingH0cHpVWpVZQ(gt2,g1,g2,ZP,TW,cplH0cHpVWpVZ1(gt2))

End Do 


cplhhhhcVWpVWp1 = 0._dp 
Call CouplinghhhhcVWpVWpQ(g2,cplhhhhcVWpVWp1)



cplhhhhVZVZ1 = 0._dp 
Call CouplinghhhhVZVZQ(g1,g2,TW,cplhhhhVZVZ1)



cplhhHpcVWpVP1 = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpVPQ(gt2,g1,g2,ZP,TW,cplhhHpcVWpVP1(gt2))

End Do 


cplhhHpcVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplinghhHpcVWpVZQ(gt2,g1,g2,ZP,TW,cplhhHpcVWpVZ1(gt2))

End Do 


cplhhcHpVPVWp1 = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVPVWpQ(gt2,g1,g2,ZP,TW,cplhhcHpVPVWp1(gt2))

End Do 


cplhhcHpVWpVZ1 = 0._dp 
Do gt2 = 1, 2
Call CouplinghhcHpVWpVZQ(gt2,g1,g2,ZP,TW,cplhhcHpVWpVZ1(gt2))

End Do 


cplHpcHpVPVP1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVPQ(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVP1(gt1,gt2))

 End Do 
End Do 


cplHpcHpVPVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVPVZQ(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVPVZ1(gt1,gt2))

 End Do 
End Do 


cplHpcHpcVWpVWp1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpcVWpVWpQ(gt1,gt2,g2,ZP,cplHpcHpcVWpVWp1(gt1,gt2))

 End Do 
End Do 


cplHpcHpVZVZ1 = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingHpcHpVZVZQ(gt1,gt2,g1,g2,ZP,TW,cplHpcHpVZVZ1(gt1,gt2))

 End Do 
End Do 


cplVGVGVGVG1Q = 0._dp 
cplVGVGVGVG2Q = 0._dp 
cplVGVGVGVG3Q = 0._dp 
Call CouplingVGVGVGVGQ(g3,cplVGVGVGVG1Q,cplVGVGVGVG2Q,cplVGVGVGVG3Q)



cplcVWpVPVPVWp1Q = 0._dp 
cplcVWpVPVPVWp2Q = 0._dp 
cplcVWpVPVPVWp3Q = 0._dp 
Call CouplingcVWpVPVPVWpQ(g2,TW,cplcVWpVPVPVWp1Q,cplcVWpVPVPVWp2Q,cplcVWpVPVPVWp3Q)



cplcVWpVPVWpVZ1Q = 0._dp 
cplcVWpVPVWpVZ2Q = 0._dp 
cplcVWpVPVWpVZ3Q = 0._dp 
Call CouplingcVWpVPVWpVZQ(g2,TW,cplcVWpVPVWpVZ1Q,cplcVWpVPVWpVZ2Q,cplcVWpVPVWpVZ3Q)



cplcVWpcVWpVWpVWp1Q = 0._dp 
cplcVWpcVWpVWpVWp2Q = 0._dp 
cplcVWpcVWpVWpVWp3Q = 0._dp 
Call CouplingcVWpcVWpVWpVWpQ(g2,cplcVWpcVWpVWpVWp1Q,cplcVWpcVWpVWpVWp2Q,              & 
& cplcVWpcVWpVWpVWp3Q)



cplcVWpVWpVZVZ1Q = 0._dp 
cplcVWpVWpVZVZ2Q = 0._dp 
cplcVWpVWpVZVZ3Q = 0._dp 
Call CouplingcVWpVWpVZVZQ(g2,TW,cplcVWpVWpVZVZ1Q,cplcVWpVWpVZVZ2Q,cplcVWpVWpVZVZ3Q)



Iname = Iname - 1 
End Subroutine CouplingsColoredQuartics

Subroutine CouplingA0A0A0A0Q(lam2,res1)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0A0A0' 
 
res1 = 0._dp 
res1 = res1-3._dp*(lam2)

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0A0A0Q  
 
 
Subroutine CouplingA0A0G0G0Q(lam5,lam3,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0G0' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam3)
res1 = res1-1._dp*(lam5)/2._dp
res1 = res1-Conjg(lam5)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0G0Q  
 
 
Subroutine CouplingA0A0G0hhQ(lam5,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0G0hh' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam5)/2._dp
res1 = res1+Conjg(lam5)/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0G0hhQ  
 
 
Subroutine CouplingA0A0H0H0Q(lam2,res1)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0H0H0' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam2)

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0H0H0Q  
 
 
Subroutine CouplingA0A0hhhhQ(lam5,lam3,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0hhhh' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam3)
res1 = res1+lam5/2._dp
res1 = res1+Conjg(lam5)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0hhhhQ  
 
 
Subroutine CouplingA0A0HpcHpQ(gt3,gt4,lam4,lam3,lam2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0HpcHp' 
 
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
res1 = res1-(lam2*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0HpcHpQ  
 
 
Subroutine CouplingA0G0G0H0Q(lam5,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0G0H0' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam5)/2._dp
res1 = res1+Conjg(lam5)/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0G0H0Q  
 
 
Subroutine CouplingA0G0H0hhQ(lam5,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0H0hh' 
 
res1 = 0._dp 
res1 = res1+lam5/2._dp
res1 = res1+Conjg(lam5)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0H0hhQ  
 
 
Subroutine CouplingA0G0HpcHpQ(gt3,gt4,lam5,lam4,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0G0HpcHp' 
 
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
res1 = res1+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0G0HpcHpQ  
 
 
Subroutine CouplingA0H0hhhhQ(lam5,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0H0hhhh' 
 
res1 = 0._dp 
res1 = res1+lam5/2._dp
res1 = res1-Conjg(lam5)/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0H0hhhhQ  
 
 
Subroutine CouplingA0hhHpcHpQ(gt3,gt4,lam5,lam4,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0hhHpcHp' 
 
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
res1 = res1+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0hhHpcHpQ  
 
 
Subroutine CouplingG0G0G0G0Q(lam1,res1)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0G0G0' 
 
res1 = 0._dp 
res1 = res1-3._dp*(lam1)

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0G0G0Q  
 
 
Subroutine CouplingG0G0H0H0Q(lam5,lam3,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0H0H0' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam3)
res1 = res1+lam5/2._dp
res1 = res1+Conjg(lam5)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0H0H0Q  
 
 
Subroutine CouplingG0G0hhhhQ(lam1,res1)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0hhhh' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam1)

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0hhhhQ  
 
 
Subroutine CouplingG0G0HpcHpQ(gt3,gt4,lam1,lam4,lam3,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0HpcHp' 
 
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
res1 = res1-(lam3*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam1*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0HpcHpQ  
 
 
Subroutine CouplingG0H0H0hhQ(lam5,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0H0hh' 
 
res1 = 0._dp 
res1 = res1+lam5/2._dp
res1 = res1-Conjg(lam5)/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0H0hhQ  
 
 
Subroutine CouplingG0H0HpcHpQ(gt3,gt4,lam5,lam4,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0H0HpcHp' 
 
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
res1 = res1+(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1-(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0H0HpcHpQ  
 
 
Subroutine CouplingH0H0H0H0Q(lam2,res1)

Implicit None 

Complex(dp), Intent(in) :: lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0H0H0' 
 
res1 = 0._dp 
res1 = res1-3._dp*(lam2)

 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0H0H0Q  
 
 
Subroutine CouplingH0H0hhhhQ(lam5,lam3,res1)

Implicit None 

Complex(dp), Intent(in) :: lam5,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0hhhh' 
 
res1 = 0._dp 
res1 = res1-1._dp*(lam3)
res1 = res1-1._dp*(lam5)/2._dp
res1 = res1-Conjg(lam5)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0hhhhQ  
 
 
Subroutine CouplingH0H0HpcHpQ(gt3,gt4,lam4,lam3,lam2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam4,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0HpcHp' 
 
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
res1 = res1-(lam2*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt3,2)*ZP(gt4,2))
res1 = res1-(lam4*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0HpcHpQ  
 
 
Subroutine CouplingH0hhHpcHpQ(gt3,gt4,lam5,lam4,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam4

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0hhHpcHp' 
 
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
res1 = res1-(lam4*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1+(Conjg(lam5)*ZP(gt3,2)*ZP(gt4,1))/2._dp
res1 = res1-(lam4*ZP(gt3,1)*ZP(gt4,2))/2._dp
res1 = res1+(lam5*ZP(gt3,1)*ZP(gt4,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0hhHpcHpQ  
 
 
Subroutine CouplinghhhhhhhhQ(lam1,res1)

Implicit None 

Complex(dp), Intent(in) :: lam1

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'Couplinghhhhhhhh' 
 
res1 = 0._dp 
res1 = res1-3._dp*(lam1)

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhhhhhQ  
 
 
Subroutine CouplinghhhhHpcHpQ(gt3,gt4,lam1,lam4,lam3,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam1,lam4,lam3

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhHpcHp' 
 
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
res1 = res1-(lam3*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam4*ZP(gt3,1)*ZP(gt4,1))
res1 = res1-(lam1*ZP(gt3,2)*ZP(gt4,2))

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhHpcHpQ  
 
 
Subroutine CouplingHpHpcHpcHpQ(gt1,gt2,gt3,gt4,lam5,lam1,lam3,lam2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2,gt3,gt4
Real(dp), Intent(in) :: ZP(2,2)

Complex(dp), Intent(in) :: lam5,lam1,lam3,lam2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpHpcHpcHp' 
 
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
res1 = res1-2*lam2*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-2*Conjg(lam5)*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,1)
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,1))
res1 = res1-(lam3*ZP(gt1,2)*ZP(gt2,1)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-(lam3*ZP(gt1,1)*ZP(gt2,2)*ZP(gt3,1)*ZP(gt4,2))
res1 = res1-2*lam5*ZP(gt1,1)*ZP(gt2,1)*ZP(gt3,2)*ZP(gt4,2)
res1 = res1-2*lam1*ZP(gt1,2)*ZP(gt2,2)*ZP(gt3,2)*ZP(gt4,2)

 


Iname = Iname - 1 
 
End Subroutine CouplingHpHpcHpcHpQ  
 
 
Subroutine CouplingA0A0cVWpVWpQ(g2,res1)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0cVWpVWp' 
 
res1 = 0._dp 
res1 = res1+g2**2/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0cVWpVWpQ  
 
 
Subroutine CouplingA0A0VZVZQ(g1,g2,TW,res1)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0A0VZVZ' 
 
res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2)/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)
res1 = res1+(g1**2*Sin(TW)**2)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingA0A0VZVZQ  
 
 
Subroutine CouplingA0HpcVWpVPQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpVPQ  
 
 
Subroutine CouplingA0HpcVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0HpcVWpVZQ  
 
 
Subroutine CouplingA0cHpVPVWpQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0cHpVPVWpQ  
 
 
Subroutine CouplingA0cHpVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingA0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingA0cHpVWpVZQ  
 
 
Subroutine CouplingG0G0cVWpVWpQ(g2,res1)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0cVWpVWp' 
 
res1 = 0._dp 
res1 = res1+g2**2/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0cVWpVWpQ  
 
 
Subroutine CouplingG0G0VZVZQ(g1,g2,TW,res1)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0G0VZVZ' 
 
res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2)/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)
res1 = res1+(g1**2*Sin(TW)**2)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingG0G0VZVZQ  
 
 
Subroutine CouplingG0HpcVWpVPQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpVPQ  
 
 
Subroutine CouplingG0HpcVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0HpcVWpVZQ  
 
 
Subroutine CouplingG0cHpVPVWpQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0cHpVPVWpQ  
 
 
Subroutine CouplingG0cHpVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingG0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp
res1 = -(0.,1.)*res1 
 


Iname = Iname - 1 
 
End Subroutine CouplingG0cHpVWpVZQ  
 
 
Subroutine CouplingH0H0cVWpVWpQ(g2,res1)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0cVWpVWp' 
 
res1 = 0._dp 
res1 = res1+g2**2/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0cVWpVWpQ  
 
 
Subroutine CouplingH0H0VZVZQ(g1,g2,TW,res1)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0H0VZVZ' 
 
res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2)/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)
res1 = res1+(g1**2*Sin(TW)**2)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0H0VZVZQ  
 
 
Subroutine CouplingH0HpcVWpVPQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpVPQ  
 
 
Subroutine CouplingH0HpcVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0HpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0HpcVWpVZQ  
 
 
Subroutine CouplingH0cHpVPVWpQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Cos(TW)*ZP(gt2,1))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0cHpVPVWpQ  
 
 
Subroutine CouplingH0cHpVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingH0cHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Sin(TW)*ZP(gt2,1))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplingH0cHpVWpVZQ  
 
 
Subroutine CouplinghhhhcVWpVWpQ(g2,res1)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhcVWpVWp' 
 
res1 = 0._dp 
res1 = res1+g2**2/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhcVWpVWpQ  
 
 
Subroutine CouplinghhhhVZVZQ(g1,g2,TW,res1)

Implicit None 

Real(dp), Intent(in) :: g1,g2,TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhhhVZVZ' 
 
res1 = 0._dp 
res1 = res1+(g2**2*Cos(TW)**2)/2._dp
res1 = res1+g1*g2*Cos(TW)*Sin(TW)
res1 = res1+(g1**2*Sin(TW)**2)/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhhhVZVZQ  
 
 
Subroutine CouplinghhHpcVWpVPQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWpVP' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpVPQ  
 
 
Subroutine CouplinghhHpcVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhHpcVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhHpcVWpVZQ  
 
 
Subroutine CouplinghhcHpVPVWpQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpVPVWp' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1-(g1*g2*Cos(TW)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpVPVWpQ  
 
 
Subroutine CouplinghhcHpVWpVZQ(gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplinghhcHpVWpVZ' 
 
If ((gt2.Lt.1).Or.(gt2.Gt.2)) Then 
  Write (ErrCan,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (ErrCan,*) 'index gt2 out of range', gt2 
  Write (*,*) 'Problem in Subroutine ',NameOfUnit(Iname) 
  Write (*,*) 'index gt2 out of range', gt2 
  Call TerminateProgram 
End If 

res1 = 0._dp 
res1 = res1+(g1*g2*Sin(TW)*ZP(gt2,2))/2._dp

 


Iname = Iname - 1 
 
End Subroutine CouplinghhcHpVWpVZQ  
 
 
Subroutine CouplingHpcHpVPVPQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVP' 
 
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
 
End Subroutine CouplingHpcHpVPVPQ  
 
 
Subroutine CouplingHpcHpVPVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVPVZ' 
 
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
 
End Subroutine CouplingHpcHpVPVZQ  
 
 
Subroutine CouplingHpcHpcVWpVWpQ(gt1,gt2,g2,ZP,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g2,ZP(2,2)

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpcVWpVWp' 
 
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
 
End Subroutine CouplingHpcHpcVWpVWpQ  
 
 
Subroutine CouplingHpcHpVZVZQ(gt1,gt2,g1,g2,ZP,TW,res1)

Implicit None 

Integer, Intent(in) :: gt1,gt2
Real(dp), Intent(in) :: g1,g2,ZP(2,2),TW

Complex(dp), Intent(out) :: res1 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingHpcHpVZVZ' 
 
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
 
End Subroutine CouplingHpcHpVZVZQ  
 
 
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
 
 
Subroutine CouplingcVWpVPVPVWpQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVPVWp' 
 
res1 = 0._dp 
res1 = res1+g2**2*Sin(TW)**2

 
res2 = 0._dp 
res2 = res2+g2**2*Sin(TW)**2

 
res3 = 0._dp 
res3 = res3-2*g2**2*Sin(TW)**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVPVPVWpQ  
 
 
Subroutine CouplingcVWpVPVWpVZQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVPVWpVZ' 
 
res1 = 0._dp 
res1 = res1+g2**2*Cos(TW)*Sin(TW)

 
res2 = 0._dp 
res2 = res2-(g2**2*Sin(2._dp*(TW)))

 
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)*Sin(TW)

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVPVWpVZQ  
 
 
Subroutine CouplingcVWpcVWpVWpVWpQ(g2,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpcVWpVWpVWp' 
 
res1 = 0._dp 
res1 = res1+2*g2**2

 
res2 = 0._dp 
res2 = res2-g2**2

 
res3 = 0._dp 
res3 = res3-g2**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpcVWpVWpVWpQ  
 
 
Subroutine CouplingcVWpVWpVZVZQ(g2,TW,res1,res2,res3)

Implicit None 

Real(dp), Intent(in) :: g2,TW

Complex(dp), Intent(out) :: res1 
Complex(dp), Intent(out) :: res2 
Complex(dp), Intent(out) :: res3 
Integer :: j1,j2,j3,j4,j5,j6, j7, j8, j9, j10, j11, j12 
Iname = Iname +1 
NameOfUnit(Iname) = 'CouplingcVWpVWpVZVZ' 
 
res1 = 0._dp 
res1 = res1-2*g2**2*Cos(TW)**2

 
res2 = 0._dp 
res2 = res2+g2**2*Cos(TW)**2

 
res3 = 0._dp 
res3 = res3+g2**2*Cos(TW)**2

 


Iname = Iname - 1 
 
End Subroutine CouplingcVWpVWpVZVZQ  
 
 
End Module Couplings_Inert2 
