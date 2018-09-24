Module EffectivePotential_NMSSM 
 
Use Control 
Use Settings 
Use Couplings_NMSSM 
Use LoopFunctions 
Use Mathematics 
Use MathematicsQP 
Use Model_Data_NMSSM 
Use StandardModel 
Use TreeLevelMasses_NMSSM 
Use EffPotFunctions
Use DerivativesEffPotFunctions
 
Contains 
 
Subroutine CalculateCorrectionsEffPot(ti_ep2L,pi_ep2L,vd,vu,vS,g1,g2,g3,              & 
& Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Integer , Intent(inout):: kont 
Integer :: iout 
Real(dp) :: err,h_start,vevs(3) 
Real(dp), Intent(out) :: ti_ep2L(3)  
Real(dp), Intent(out) :: pi_ep2L(3,3)


err2L = 0._dp 
If (.not.PurelyNumericalEffPot) Then 
epsM = 1.0E-8_dp 
epsD = 1.0E-8_dp 
! 2nd deriv. also calculates the 1st deriv. of V
Call SecondDerivativeEffPot2Loop(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,               & 
& Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,pi_ep2L,ti_ep2L)

Else 
epsM = 1.0E-6_dp 
epsD = 1.0E-6_dp 
vevs = (/vd,vu,vS/) 
! Calculate 1st (ti_ep) and 2nd derivatives (pi_ep)
ti_ep2L(1) = partialDiff_Ridders(EffPotFunction2Loop,vevs,1,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
ti_ep2L(2) = partialDiff_Ridders(EffPotFunction2Loop,vevs,2,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
ti_ep2L(3) = partialDiff_Ridders(EffPotFunction2Loop,vevs,3,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(1,1) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,1,1,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(2,1) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,2,1,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(2,2) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,2,2,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(3,1) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,3,1,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(3,2) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,3,2,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(3,3) = partialDiffXY_Ridders(EffPotFunction2Loop,vevs,3,3,3,err,h_start,iout) 
If (err.gt.err2L) err2L = err 
pi_ep2L(1,2)=pi_ep2L(2,1)
pi_ep2L(1,3)=pi_ep2L(3,1)
pi_ep2L(2,3)=pi_ep2L(3,2)
End If 
Contains 

Real(dp) Function EffPotFunction(vevs) 
  ! a wrapping function to be passed to numerical differentiation 
  Implicit None 
  Real(dp), Intent(in) :: vevs(3) 
  Real(dp) :: effPot 
Call CalculateEffPot(vevs(1),vevs(2),vevs(3),g1,g2,g3,Yd,Ye,lam,kap,Yu,               & 
& Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,effPot)

  EffPotFunction = effPot 
  End Function 

Real(dp) Function EffPotFunction2Loop(vevs) 
  ! a wrapping function to be passed to numerical differentiation 
  Implicit None 
  Real(dp), Intent(in) :: vevs(3) 
  Real(dp) :: effPot2L 
Call CalculateEffPot2Loop(vevs(1),vevs(2),vevs(3),g1,g2,g3,Yd,Ye,lam,kap,             & 
& Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,effPot2L)

  EffPotFunction2Loop = effPot2L 
  End Function 

End subroutine CalculateCorrectionsEffPot 


Subroutine CalculateEffPot(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,             & 
& Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,effPot)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Integer, Intent(inout):: kont
Integer :: i 
Real(dp) :: effpot,Qscale,result,temp


Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,            & 
& mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,.True.,kont)

Qscale= getRenormalizationScale()
result=0._dp
temp=0._dp
! sum over real scalars (color *[2 if complex]) 
Do i=1,6
temp=temp+(3*2) * h_SMartin(MSd2(i),Qscale) ! Sd
End Do
Do i=1,3
temp=temp+(2)    * h_SMartin(MSv2(i),Qscale) ! Sv
End Do
Do i=1,6
temp=temp+(3*2) * h_SMartin(MSu2(i),Qscale) ! Su
End Do
Do i=1,6
temp=temp+(2)    * h_SMartin(MSe2(i),Qscale) ! Se
End Do
Do i=1,3
temp=temp+          h_SMartin(Mhh2(i),Qscale) ! hh
End Do
Do i=2,3
temp=temp+          h_SMartin(MAh2(i),Qscale) ! Ah
End Do
Do i=2,2
temp=temp+(2)    * h_SMartin(MHpm2(i),Qscale) ! Hpm
End Do
result=(+1)*temp !scalars

temp=0._dp
! sum over two-component fermions (*color [*2 if Dirac Fermion]) 
Do i=1,2
temp=temp+          h_SMartin(MCha2(i),Qscale)*2 ! Cha
End Do
Do i=1,5
temp=temp+          h_SMartin(MChi2(i),Qscale)*1 ! Chi
End Do
Do i=1,3
temp=temp+(3)   * h_SMartin(MFd2(i),Qscale)*2 ! Fd
End Do
Do i=1,3
temp=temp+          h_SMartin(MFe2(i),Qscale)*2 ! Fe
End Do
Do i=1,3
temp=temp+(3)   * h_SMartin(MFu2(i),Qscale)*2 ! Fu
End Do
Do i=1,3
temp=temp+          h_SMartin(0._dp,Qscale)*1 ! Fv
End Do
temp=temp+(8)   * h_SMartin(MGlu2,Qscale)*1 ! Glu
result=result+(-2)*temp ! fermions

temp=0._dp
! sum over real vectors (color *[2 if complex]) 
temp=temp+(8)   * h_SMartin(0._dp,Qscale) ! VG
temp=temp+          h_SMartin(0._dp,Qscale) ! VP
temp=temp+          h_SMartin(MVZ2,Qscale) ! VZ
temp=temp+(2)    * h_SMartin(MVWm2,Qscale) ! VWm
result=result+(+3)*temp ! vectors

effPot = result * oo16pi2

End Subroutine CalculateEffPot 



 
 
Subroutine CalculateEffPot2Loop(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,             & 
& Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,effPot2L)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Integer, Intent(inout):: kont
Real(dp), Intent(out) :: effpot2L
Integer :: i,i1,i2,i3,includeGhosts,NrContr 
Integer :: NrContr1,NrContr2 !nr of contributing diagrams
Real(dp) :: Qscale,result,colorfactor,coeff,coeffbar
Complex(dp) :: temp,coupx,coupxbar,coup1,coup2,coup1L,coup1R,coup2L,coup2R
Complex(dp) :: dcoupx,dcoupxbar,dcoup1,dcoup2,dcoup1L,dcoup1R,dcoup2L,dcoup2R
Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

Real(dp) :: results1(42),results2(24)


Call TreeMassesEffPot(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,.True.,kont)

Call CouplingsForEffPot3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,Yd,Td,ZD,Ye,               & 
& Te,ZE,Yu,Tu,ZU,ZV,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,cplAhAhhh,          & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,    & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,              & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,      & 
& cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,       & 
& cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR)

Call CouplingsForEffPot4(lam,kap,ZA,ZH,ZP,Yd,ZD,Ye,ZE,Yu,ZU,ZV,g3,cplAhAhAhAh,        & 
& cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,         & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,               & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,    & 
& cplSucSuVGVG)


Qscale = getRenormalizationScale()
result=0._dp
results1=0._dp
results2=0._dp
temp=0._dp
! ----- Topology1 (sunrise): diagrams w. 3 Particles and 2 Vertices

! ----- diagrams of type SSS, 14 ------ 
! ---- Ah,Ah,Ah ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhAh(i1,i2,i3)
coup2 = cplAhAhAh(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*1._dp/12._dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MAh2(i2),MAh2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Ah, Ah]' 
    End Do
  End Do
End Do
results1(1)=temp
! ---- Ah,Ah,hh ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhhh(i1,i2,i3)
coup2 = cplAhAhhh(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*0.25_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MAh2(i2),Mhh2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Ah, hh]' 
    End Do
  End Do
End Do
results1(2)=temp
! ---- Ah,hh,hh ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhhhhh(i1,i2,i3)
coup2 = cplAhhhhh(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*0.25_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),Mhh2(i2),Mhh2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, hh, hh]' 
    End Do
  End Do
End Do
results1(3)=temp
! ---- Ah,Hpm,conj[Hpm] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplAhHpmcHpm(i1,i2,i3)
coup2 = cplAhHpmcHpm(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MHpm2(i2),MHpm2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Hpm, conj[Hpm]]' 
    End Do
  End Do
End Do
results1(4)=temp
! ---- Ah,Sd,conj[Sd] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSdcSd(i1,i2,i3)
coup2 = cplAhSdcSd(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MSd2(i2),MSd2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Sd, conj[Sd]]' 
    End Do
  End Do
End Do
results1(5)=temp
! ---- Ah,Se,conj[Se] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSecSe(i1,i2,i3)
coup2 = cplAhSecSe(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MSe2(i2),MSe2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Se, conj[Se]]' 
    End Do
  End Do
End Do
results1(6)=temp
! ---- Ah,Su,conj[Su] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSucSu(i1,i2,i3)
coup2 = cplAhSucSu(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(MAh2(i1),MSu2(i2),MSu2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Su, conj[Su]]' 
    End Do
  End Do
End Do
results1(7)=temp
! ---- hh,hh,hh ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplhhhhhh(i1,i2,i3)
coup2 = cplhhhhhh(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*1._dp/12._dp*abs(coup1)**2*Fep_SSS(Mhh2(i1),Mhh2(i2),Mhh2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, hh, hh]' 
    End Do
  End Do
End Do
results1(8)=temp
! ---- hh,Hpm,conj[Hpm] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplhhHpmcHpm(i1,i2,i3)
coup2 = cplhhHpmcHpm(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(Mhh2(i1),MHpm2(i2),MHpm2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Hpm, conj[Hpm]]' 
    End Do
  End Do
End Do
results1(9)=temp
! ---- hh,Sd,conj[Sd] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSdcSd(i1,i2,i3)
coup2 = cplhhSdcSd(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(Mhh2(i1),MSd2(i2),MSd2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Sd, conj[Sd]]' 
    End Do
  End Do
End Do
results1(10)=temp
! ---- hh,Se,conj[Se] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSecSe(i1,i2,i3)
coup2 = cplhhSecSe(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(Mhh2(i1),MSe2(i2),MSe2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Se, conj[Se]]' 
    End Do
  End Do
End Do
results1(11)=temp
! ---- hh,Su,conj[Su] ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSucSu(i1,i2,i3)
coup2 = cplhhSucSu(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSS(Mhh2(i1),MSu2(i2),MSu2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Su, conj[Su]]' 
    End Do
  End Do
End Do
results1(12)=temp
! ---- Sd,conj[Hpm],conj[Su] ----
temp=0._dp
Do i1=1,6
 Do i2=1,2
    Do i3=1,6
coup1 = cplSdcHpmcSu(i1,i2,i3)
coup2 = cplHpmSucSd(i2,i3,i1)
colorfactor=3
temp=temp+colorfactor*1._dp*abs(coup1)**2*Fep_SSS(MSd2(i1),MHpm2(i2),MSu2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Sd, conj[Hpm], conj[Su]]' 
    End Do
  End Do
End Do
results1(13)=temp
! ---- Se,conj[Hpm],conj[Sv] ----
temp=0._dp
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1 = cplSecHpmcSv(i1,i2,i3)
coup2 = cplHpmSvcSe(i2,i3,i1)
colorfactor=1
temp=temp+colorfactor*1._dp*abs(coup1)**2*Fep_SSS(MSe2(i1),MHpm2(i2),MSv2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Se, conj[Hpm], conj[Sv]]' 
    End Do
  End Do
End Do
results1(14)=temp
! ----- diagrams of type FFS, 22 ------ 
! ---- Ah,Cha,bar[Cha] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChaAhL(i3,i2,i1)
coup1R = cplcChaChaAhR(i3,i2,i1)
coup2L = cplcChaChaAhL(i2,i3,i1)
coup2R = cplcChaChaAhR(i2,i3,i1)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MCha2(i3),MCha2(i2),MAh2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Cha, bar[Cha]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MCha(i2)*MCha(i3)*Fep_FFSbar(MCha2(i3),MCha2(i2),MAh2(i1),Qscale)
    End Do
  End Do
End Do
results1(15)=temp
! ---- Ah,Chi,Chi ----
temp=0._dp
Do i1=1,3
 Do i2=1,5
    Do i3=1,5
coup1L = cplChiChiAhL(i2,i3,i1)
coup1R = cplChiChiAhR(i2,i3,i1)
coup2L = cplChiChiAhL(i2,i3,i1)
coup2R = cplChiChiAhR(i2,i3,i1)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2)*Fep_FFS(MChi2(i3),MChi2(i2),MAh2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Chi, Chi]' 
temp=temp+colorfactor*0.5_dp*Real(coup1L**2,dp)*MChi(i2)*MChi(i3)*Fep_FFSbar(MChi2(i3),MChi2(i2),MAh2(i1),Qscale)
    End Do
  End Do
End Do
results1(16)=temp
! ---- Ah,Fd,bar[Fd] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdAhL(i3,i2,i1)
coup1R = cplcFdFdAhR(i3,i2,i1)
coup2L = cplcFdFdAhL(i2,i3,i1)
coup2R = cplcFdFdAhR(i2,i3,i1)
colorfactor=3
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFd2(i3),MFd2(i2),MAh2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fd, bar[Fd]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFd(i2)*MFd(i3)*Fep_FFSbar(MFd2(i3),MFd2(i2),MAh2(i1),Qscale)
    End Do
  End Do
End Do
results1(17)=temp
! ---- Ah,Fe,bar[Fe] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFeAhL(i3,i2,i1)
coup1R = cplcFeFeAhR(i3,i2,i1)
coup2L = cplcFeFeAhL(i2,i3,i1)
coup2R = cplcFeFeAhR(i2,i3,i1)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFe2(i3),MFe2(i2),MAh2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fe, bar[Fe]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFe(i2)*MFe(i3)*Fep_FFSbar(MFe2(i3),MFe2(i2),MAh2(i1),Qscale)
    End Do
  End Do
End Do
results1(18)=temp
! ---- Ah,Fu,bar[Fu] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuAhL(i3,i2,i1)
coup1R = cplcFuFuAhR(i3,i2,i1)
coup2L = cplcFuFuAhL(i2,i3,i1)
coup2R = cplcFuFuAhR(i2,i3,i1)
colorfactor=3
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFu2(i3),MFu2(i2),MAh2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fu, bar[Fu]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFu(i2)*MFu(i3)*Fep_FFSbar(MFu2(i3),MFu2(i2),MAh2(i1),Qscale)
    End Do
  End Do
End Do
results1(19)=temp
! ---- Cha,hh,bar[Cha] ----
temp=0._dp
Do i1=1,2
 Do i2=1,3
    Do i3=1,2
coup1L = cplcChaChahhL(i3,i1,i2)
coup1R = cplcChaChahhR(i3,i1,i2)
coup2L = cplcChaChahhL(i1,i3,i2)
coup2R = cplcChaChahhR(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MCha2(i3),MCha2(i1),Mhh2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Cha, hh, bar[Cha]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MCha(i1)*MCha(i3)*Fep_FFSbar(MCha2(i3),MCha2(i1),Mhh2(i2),Qscale)
    End Do
  End Do
End Do
results1(20)=temp
! ---- Chi,Chi,hh ----
temp=0._dp
Do i1=1,5
 Do i2=1,5
    Do i3=1,3
coup1L = cplChiChihhL(i1,i2,i3)
coup1R = cplChiChihhR(i1,i2,i3)
coup2L = cplChiChihhL(i1,i2,i3)
coup2R = cplChiChihhR(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2)*Fep_FFS(MChi2(i2),MChi2(i1),Mhh2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Chi, hh]' 
temp=temp+colorfactor*0.5_dp*Real(coup1L**2,dp)*MChi(i1)*MChi(i2)*Fep_FFSbar(MChi2(i2),MChi2(i1),Mhh2(i3),Qscale)
    End Do
  End Do
End Do
results1(21)=temp
! ---- Chi,Hpm,bar[Cha] ----
temp=0._dp
Do i1=1,5
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChiHpmL(i3,i1,i2)
coup1R = cplcChaChiHpmR(i3,i1,i2)
coup2L = cplChiChacHpmL(i1,i3,i2)
coup2R = cplChiChacHpmR(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MCha2(i3),MChi2(i1),MHpm2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Hpm, bar[Cha]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MChi(i1)*MCha(i3)*Fep_FFSbar(MCha2(i3),MChi2(i1),MHpm2(i2),Qscale)
    End Do
  End Do
End Do
results1(22)=temp
! ---- Chi,Sd,bar[Fd] ----
temp=0._dp
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdChiSdL(i3,i1,i2)
coup1R = cplcFdChiSdR(i3,i1,i2)
coup2L = cplChiFdcSdL(i1,i3,i2)
coup2R = cplChiFdcSdR(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFd2(i3),MChi2(i1),MSd2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Sd, bar[Fd]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MChi(i1)*MFd(i3)*Fep_FFSbar(MFd2(i3),MChi2(i1),MSd2(i2),Qscale)
    End Do
  End Do
End Do
results1(23)=temp
! ---- Chi,Se,bar[Fe] ----
temp=0._dp
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFeChiSeL(i3,i1,i2)
coup1R = cplcFeChiSeR(i3,i1,i2)
coup2L = cplChiFecSeL(i1,i3,i2)
coup2R = cplChiFecSeR(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFe2(i3),MChi2(i1),MSe2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Se, bar[Fe]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MChi(i1)*MFe(i3)*Fep_FFSbar(MFe2(i3),MChi2(i1),MSe2(i2),Qscale)
    End Do
  End Do
End Do
results1(24)=temp
! ---- Chi,Su,bar[Fu] ----
temp=0._dp
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuChiSuL(i3,i1,i2)
coup1R = cplcFuChiSuR(i3,i1,i2)
coup2L = cplChiFucSuL(i1,i3,i2)
coup2R = cplChiFucSuR(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFu2(i3),MChi2(i1),MSu2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Su, bar[Fu]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MChi(i1)*MFu(i3)*Fep_FFSbar(MFu2(i3),MChi2(i1),MSu2(i2),Qscale)
    End Do
  End Do
End Do
results1(25)=temp
! ---- Fd,hh,bar[Fd] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdhhL(i3,i1,i2)
coup1R = cplcFdFdhhR(i3,i1,i2)
coup2L = cplcFdFdhhL(i1,i3,i2)
coup2R = cplcFdFdhhR(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFd2(i3),MFd2(i1),Mhh2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fd, hh, bar[Fd]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFd(i1)*MFd(i3)*Fep_FFSbar(MFd2(i3),MFd2(i1),Mhh2(i2),Qscale)
    End Do
  End Do
End Do
results1(26)=temp
! ---- Fd,bar[Cha],conj[Su] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,6
coup1L = cplcChaFdcSuL(i2,i1,i3)
coup1R = cplcChaFdcSuR(i2,i1,i3)
coup2L = cplcFdChaSuL(i1,i2,i3)
coup2R = cplcFdChaSuR(i1,i2,i3)
colorfactor=3
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MCha2(i2),MFd2(i1),MSu2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fd, bar[Cha], conj[Su]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MFd(i1)*MCha(i2)*Fep_FFSbar(MCha2(i2),MFd2(i1),MSu2(i3),Qscale)
    End Do
  End Do
End Do
results1(27)=temp
! ---- Fe,hh,bar[Fe] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFehhL(i3,i1,i2)
coup1R = cplcFeFehhR(i3,i1,i2)
coup2L = cplcFeFehhL(i1,i3,i2)
coup2R = cplcFeFehhR(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFe2(i3),MFe2(i1),Mhh2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fe, hh, bar[Fe]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFe(i1)*MFe(i3)*Fep_FFSbar(MFe2(i3),MFe2(i1),Mhh2(i2),Qscale)
    End Do
  End Do
End Do
results1(28)=temp
! ---- Fe,bar[Cha],conj[Sv] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChaFecSvL(i2,i1,i3)
coup1R = cplcChaFecSvR(i2,i1,i3)
coup2L = cplcFeChaSvL(i1,i2,i3)
coup2R = cplcFeChaSvR(i1,i2,i3)
colorfactor=1
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MCha2(i2),MFe2(i1),MSv2(i3),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fe, bar[Cha], conj[Sv]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MFe(i1)*MCha(i2)*Fep_FFSbar(MCha2(i2),MFe2(i1),MSv2(i3),Qscale)
    End Do
  End Do
End Do
results1(29)=temp
! ---- Fu,hh,bar[Fu] ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuhhL(i3,i1,i2)
coup1R = cplcFuFuhhR(i3,i1,i2)
coup2L = cplcFuFuhhL(i1,i3,i2)
coup2R = cplcFuFuhhR(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFu2(i3),MFu2(i1),Mhh2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fu, hh, bar[Fu]]' 
temp=temp+colorfactor*0.5_dp*2*Real(coup1L*conjg(coup1R),dp)*MFu(i1)*MFu(i3)*Fep_FFSbar(MFu2(i3),MFu2(i1),Mhh2(i2),Qscale)
    End Do
  End Do
End Do
results1(30)=temp
! ---- Fu,Hpm,bar[Fd] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFdFuHpmL(i3,i1,i2)
coup1R = cplcFdFuHpmR(i3,i1,i2)
coup2L = cplcFuFdcHpmL(i1,i3,i2)
coup2R = cplcFuFdcHpmR(i1,i3,i2)
colorfactor=3
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFd2(i3),MFu2(i1),MHpm2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fu, Hpm, bar[Fd]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MFu(i1)*MFd(i3)*Fep_FFSbar(MFd2(i3),MFu2(i1),MHpm2(i2),Qscale)
    End Do
  End Do
End Do
results1(31)=temp
! ---- Fv,Hpm,bar[Fe] ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFeFvHpmL(i3,i1,i2)
coup1R = cplcFeFvHpmR(i3,i1,i2)
coup2L = cplcFvFecHpmL(i1,i3,i2)
coup2R = cplcFvFecHpmR(i1,i3,i2)
colorfactor=1
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFe2(i3),0._dp,MHpm2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fv, Hpm, bar[Fe]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*0.*MFe(i3)*Fep_FFSbar(MFe2(i3),0._dp,MHpm2(i2),Qscale)
    End Do
  End Do
End Do
results1(32)=temp
! ---- Glu,Sd,bar[Fd] ----
temp=0._dp
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdGluSdL(i3,i2)
coup1R = cplcFdGluSdR(i3,i2)
coup2L = cplGluFdcSdL(i3,i2)
coup2R = cplGluFdcSdR(i3,i2)
colorfactor=4
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFd2(i3),MGlu2,MSd2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Glu, Sd, bar[Fd]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MGlu*MFd(i3)*Fep_FFSbar(MFd2(i3),MGlu2,MSd2(i2),Qscale)
    End Do
  End Do
results1(33)=temp
! ---- Glu,Su,bar[Fu] ----
temp=0._dp
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuGluSuL(i3,i2)
coup1R = cplcFuGluSuR(i3,i2)
coup2L = cplGluFucSuL(i3,i2)
coup2R = cplGluFucSuR(i3,i2)
colorfactor=4
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFu2(i3),MGlu2,MSu2(i2),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Glu, Su, bar[Fu]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MGlu*MFu(i3)*Fep_FFSbar(MFu2(i3),MGlu2,MSu2(i2),Qscale)
    End Do
  End Do
results1(34)=temp
! ---- Sd,bar[Cha],bar[Fu] ----
temp=0._dp
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFuSdL(i2,i3,i1)
coup1R = cplcChacFuSdR(i2,i3,i1)
coup2L = cplChaFucSdL(i2,i3,i1)
coup2R = cplChaFucSdR(i2,i3,i1)
colorfactor=3
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(MFu2(i3),MCha2(i2),MSd2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Sd, bar[Cha], bar[Fu]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MCha(i2)*MFu(i3)*Fep_FFSbar(MFu2(i3),MCha2(i2),MSd2(i1),Qscale)
    End Do
  End Do
End Do
results1(35)=temp
! ---- Se,bar[Cha],bar[Fv] ----
temp=0._dp
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFvSeL(i2,i3,i1)
coup1R = cplcChacFvSeR(i2,i3,i1)
coup2L = cplChaFvcSeL(i2,i3,i1)
coup2R = cplChaFvcSeR(i2,i3,i1)
colorfactor=1
temp=temp+colorfactor*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFS(0._dp,MCha2(i2),MSe2(i1),Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Se, bar[Cha], bar[Fv]]' 
temp=temp+colorfactor*2*Real(coup1L*conjg(coup1R),dp)*MCha(i2)*0.*Fep_FFSbar(0._dp,MCha2(i2),MSe2(i1),Qscale)
    End Do
  End Do
End Do
results1(36)=temp
! ----- diagrams of type SSV, 2 ------ 
! ---- Sd,VG,conj[Sd] ----
temp=0._dp
Do i1=1,6
    Do i3=1,6
coup1 = cplSdcSdVG(i1,i3)
coup2 = cplSdcSdVG(i3,i1)
colorfactor=4
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSV(MSd2(i3),MSd2(i1),0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSV C[Sd, VG, conj[Sd]]' 
    End Do
End Do
results1(37)=temp
! ---- Su,VG,conj[Su] ----
temp=0._dp
Do i1=1,6
    Do i3=1,6
coup1 = cplSucSuVG(i1,i3)
coup2 = cplSucSuVG(i3,i1)
colorfactor=4
temp=temp+colorfactor*0.5_dp*abs(coup1)**2*Fep_SSV(MSu2(i3),MSu2(i1),0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSV C[Su, VG, conj[Su]]' 
    End Do
End Do
results1(38)=temp
! ----- diagrams of type FFV, 3 ------ 
! ---- Fd,VG,bar[Fd] ----
temp=0._dp
Do i1=1,3
    Do i3=1,3
coup1L = cplcFdFdVGL(i3,i1)
coup1R = cplcFdFdVGR(i3,i1)
coup2L = cplcFdFdVGL(i1,i3)
coup2R = cplcFdFdVGR(i1,i3)
colorfactor=4
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFV(MFd2(i3),MFd2(i1),0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Fd, VG, bar[Fd]]' 
temp=temp+colorfactor*0.5_dp*2*Real(-coup1L*conjg(coup1R),dp)*MFd(i1)*MFd(i3)*Fep_FFVbar(MFd2(i3),MFd2(i1),0._dp,Qscale)
    End Do
End Do
results1(39)=temp
! ---- Fu,VG,bar[Fu] ----
temp=0._dp
Do i1=1,3
    Do i3=1,3
coup1L = cplcFuFuVGL(i3,i1)
coup1R = cplcFuFuVGR(i3,i1)
coup2L = cplcFuFuVGL(i1,i3)
coup2R = cplcFuFuVGR(i1,i3)
colorfactor=4
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2+abs(coup1R)**2)*Fep_FFV(MFu2(i3),MFu2(i1),0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Fu, VG, bar[Fu]]' 
temp=temp+colorfactor*0.5_dp*2*Real(-coup1L*conjg(coup1R),dp)*MFu(i1)*MFu(i3)*Fep_FFVbar(MFu2(i3),MFu2(i1),0._dp,Qscale)
    End Do
End Do
results1(40)=temp
! ---- Glu,Glu,VG ----
temp=0._dp
coup1L = cplGluGluVGL
coup1R = cplGluGluVGR
coup2L = cplGluGluVGL
coup2R = cplGluGluVGR
colorfactor=24
temp=temp+colorfactor*0.5_dp*(abs(coup1L)**2)*Fep_FFV(MGlu2,MGlu2,0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Glu, Glu, VG]' 
temp=temp+colorfactor*0.5_dp*Real(coup1L**2,dp)*MGlu*MGlu*Fep_FFVbar(MGlu2,MGlu2,0._dp,Qscale)
results1(41)=temp
! ----- diagrams of type VVV, 1 ------ 
! ---- VG,VG,VG ----
temp=0._dp
coup1 = cplVGVGVG
coup2 = cplVGVGVG
colorfactor=24
temp=temp+colorfactor*1._dp/12._dp*(coup1)**2*Fep_gauge(0._dp,0._dp,0._dp,Qscale)
 if (.not.(temp.eq.temp))  write(*,*) 'NaN at VVV C[VG, VG, VG]' 
results1(42)=temp
! ----- Topology2: diagrams w. 2 Particles and 1 Vertex

! ----- diagrams of type SS, 22 ------ 
! ---- Ah,Ah ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhAhAh(i1,i1,i2,i2)
temp=temp+(-1._dp/8._dp)*(-coup1)*Fep_SS(MAh2(i1),MAh2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Ah, Ah]' 
  End Do
End Do
results2(1)=temp
! ---- Ah,hh ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhhhhh(i1,i1,i2,i2)
temp=temp+(-0.25_dp)*(-coup1)*Fep_SS(MAh2(i1),Mhh2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, hh, hh]' 
  End Do
End Do
results2(2)=temp
! ---- Ah,Hpm ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
coup1 = cplAhAhHpmcHpm(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MAh2(i1),MHpm2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Hpm, conj[Hpm]]' 
  End Do
End Do
results2(3)=temp
! ---- Ah,Sd ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSdcSd(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MAh2(i1),MSd2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Sd, conj[Sd]]' 
  End Do
End Do
results2(4)=temp
! ---- Ah,Se ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSecSe(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MAh2(i1),MSe2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Se, conj[Se]]' 
  End Do
End Do
results2(5)=temp
! ---- Ah,Su ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSucSu(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MAh2(i1),MSu2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Su, conj[Su]]' 
  End Do
End Do
results2(6)=temp
! ---- hh,hh ----
temp=0._dp
Do i1=1,3
 Do i2=1,3
coup1 = cplhhhhhhhh(i1,i1,i2,i2)
temp=temp+(-1._dp/8._dp)*(-coup1)*Fep_SS(Mhh2(i1),Mhh2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, hh, hh]' 
  End Do
End Do
results2(7)=temp
! ---- hh,Hpm ----
temp=0._dp
Do i1=1,3
 Do i2=1,2
coup1 = cplhhhhHpmcHpm(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(Mhh2(i1),MHpm2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Hpm, conj[Hpm]]' 
  End Do
End Do
results2(8)=temp
! ---- hh,Sd ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSdcSd(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(Mhh2(i1),MSd2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Sd, conj[Sd]]' 
  End Do
End Do
results2(9)=temp
! ---- hh,Se ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSecSe(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(Mhh2(i1),MSe2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Se, conj[Se]]' 
  End Do
End Do
results2(10)=temp
! ---- hh,Su ----
temp=0._dp
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSucSu(i1,i1,i2,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(Mhh2(i1),MSu2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Su, conj[Su]]' 
  End Do
End Do
results2(11)=temp
! ---- Hpm,Hpm ----
temp=0._dp
Do i1=1,2
 Do i2=1,2
coup1 = cplHpmHpmcHpmcHpm(i1,i2,i1,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MHpm2(i1),MHpm2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Hpm, conj[Hpm], conj[Hpm]]' 
  End Do
End Do
results2(12)=temp
! ---- Hpm,Sd ----
temp=0._dp
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSdcHpmcSd(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MHpm2(i1),MSd2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Sd, conj[Hpm], conj[Sd]]' 
  End Do
End Do
results2(13)=temp
! ---- Hpm,Se ----
temp=0._dp
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSecHpmcSe(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MHpm2(i1),MSe2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Se, conj[Hpm], conj[Se]]' 
  End Do
End Do
results2(14)=temp
! ---- Hpm,Su ----
temp=0._dp
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSucHpmcSu(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MHpm2(i1),MSu2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Su, conj[Hpm], conj[Su]]' 
  End Do
End Do
results2(15)=temp
! ---- Hpm,Sv ----
temp=0._dp
Do i1=1,2
 Do i2=1,3
coup1 = cplHpmSvcHpmcSv(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MHpm2(i1),MSv2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Sv, conj[Hpm], conj[Sv]]' 
  End Do
End Do
results2(16)=temp
! ---- Sd,Sd ----
temp=0._dp
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSdcSdcSd(i1,i2,i1,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MSd2(i1),MSd2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Sd, conj[Sd], conj[Sd]]' 
  End Do
End Do
results2(17)=temp
! ---- Sd,Se ----
temp=0._dp
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSecSdcSe(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MSd2(i1),MSe2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Se, conj[Sd], conj[Se]]' 
  End Do
End Do
results2(18)=temp
! ---- Sd,Su ----
temp=0._dp
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSucSdcSu(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MSd2(i1),MSu2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Su, conj[Sd], conj[Su]]' 
  End Do
End Do
results2(19)=temp
! ---- Se,Se ----
temp=0._dp
Do i1=1,6
 Do i2=1,6
coup1 = cplSeSecSecSe(i1,i2,i1,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MSe2(i1),MSe2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Se, Se, conj[Se], conj[Se]]' 
  End Do
End Do
results2(20)=temp
! ---- Se,Sv ----
temp=0._dp
Do i1=1,6
 Do i2=1,3
coup1 = cplSeSvcSecSv(i1,i2,i1,i2)
temp=temp+(-1._dp)*(-coup1)*Fep_SS(MSe2(i1),MSv2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Se, Sv, conj[Se], conj[Sv]]' 
  End Do
End Do
results2(21)=temp
! ---- Su,Su ----
temp=0._dp
Do i1=1,6
 Do i2=1,6
coup1 = cplSuSucSucSu(i1,i2,i1,i2)
temp=temp+(-0.5_dp)*(-coup1)*Fep_SS(MSu2(i1),MSu2(i2),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Su, Su, conj[Su], conj[Su]]' 
  End Do
End Do
results2(22)=temp
! ----- diagrams of type VS, 2 ------ 
! ---- Sd,VG ----
temp=0._dp
Do i1=1,6
coup1 = cplSdcSdVGVG(i1,i1)
temp=temp+0.25_dp*coup1*Fep_VS(0._dp,MSd2(i1),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at VS C[Sd, VG, VG, conj[Sd]]' 
End Do
results2(23)=temp
! ---- Su,VG ----
temp=0._dp
Do i1=1,6
coup1 = cplSucSuVGVG(i1,i1)
temp=temp+0.25_dp*coup1*Fep_VS(0._dp,MSu2(i1),Qscale)
if (.not.(temp.eq.temp))  write(*,*) 'NaN at VS C[Su, VG, VG, conj[Su]]' 
End Do
results2(24)=temp
result = sum(results1)+sum(results2) 
effPot2L = result * oo16pi2 * oo16Pi2
End Subroutine CalculateEffPot2Loop


Subroutine SecondDerivativeEffPot2Loop(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,               & 
& Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,pi2L,ti2L)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Integer, Intent(inout):: kont
Real(dp), Intent(out) :: pi2L(3,3),ti2L(3)
Integer :: i,i1,i2,i3,NrContr 
Integer :: iv1, iv2 
Integer :: NrContr1,NrContr2 !nr of contributing diagrams
Real(dp) :: Q2,colorfactor,coeff,coeffbar
Complex(dp) :: result,result_ti,temp,temp_ti,temp_tj,tempbar,tempbar_ti,tempbar_tj
Complex(dp) :: coup1,coup2,coup1L,coup1R,coup2L,coup2R,coupx,coupxbar
Complex(dp) :: Di_coup1,Di_coup2,Di_coup1L,Di_coup1R,Di_coup2L,Di_coup2R,Di_coupx,Di_coupxbar
Complex(dp) :: Dj_coup1,Dj_coup2,Dj_coup1L,Dj_coup1R,Dj_coup2L,Dj_coup2R,Dj_coupx,Dj_coupxbar
Complex(dp) :: DDcoup1,DDcoup2,DDcoup1L,DDcoup1R,DDcoup2L,DDcoup2R,DDcoupx,DDcoupxbar
Complex(dp) :: results1(42),results2(24)
Complex(dp) :: results1_ti(42),results2_ti(24)
Real(dp) :: gout(26796) 
Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

Complex(dp) :: dcplAhAhAh(3,3,3,3),dcplAhAhhh(3,3,3,3),dcplAhhhhh(3,3,3,3),dcplAhHpmcHpm(3,2,2,3),   & 
& dcplAhSdcSd(3,6,6,3),dcplAhSecSe(3,6,6,3),dcplAhSucSu(3,6,6,3),dcplhhhhhh(3,3,3,3),    & 
& dcplhhHpmcHpm(3,2,2,3),dcplhhSdcSd(3,6,6,3),dcplhhSecSe(3,6,6,3),dcplhhSucSu(3,6,6,3), & 
& dcplHpmSucSd(2,6,6,3),dcplHpmSvcSe(2,3,6,3),dcplSdcHpmcSu(6,2,6,3),dcplSecHpmcSv(6,2,3,3),& 
& dcplSdcSdVG(6,6,3),dcplSucSuVG(6,6,3),dcplVGVGVG(3),dcplcChaChaAhL(2,2,3,3),           & 
& dcplcChaChaAhR(2,2,3,3),dcplChiChiAhL(5,5,3,3),dcplChiChiAhR(5,5,3,3),dcplcFdFdAhL(3,3,3,3),& 
& dcplcFdFdAhR(3,3,3,3),dcplcFeFeAhL(3,3,3,3),dcplcFeFeAhR(3,3,3,3),dcplcFuFuAhL(3,3,3,3),& 
& dcplcFuFuAhR(3,3,3,3),dcplChiChacHpmL(5,2,2,3),dcplChiChacHpmR(5,2,2,3),               & 
& dcplChaFucSdL(2,3,6,3),dcplChaFucSdR(2,3,6,3),dcplChaFvcSeL(2,3,6,3),dcplChaFvcSeR(2,3,6,3),& 
& dcplcChaChahhL(2,2,3,3),dcplcChaChahhR(2,2,3,3),dcplcFdChaSuL(3,2,6,3),dcplcFdChaSuR(3,2,6,3),& 
& dcplcFeChaSvL(3,2,3,3),dcplcFeChaSvR(3,2,3,3),dcplChiChihhL(5,5,3,3),dcplChiChihhR(5,5,3,3),& 
& dcplChiFdcSdL(5,3,6,3),dcplChiFdcSdR(5,3,6,3),dcplChiFecSeL(5,3,6,3),dcplChiFecSeR(5,3,6,3),& 
& dcplChiFucSuL(5,3,6,3),dcplChiFucSuR(5,3,6,3),dcplcChaChiHpmL(2,5,2,3),dcplcChaChiHpmR(2,5,2,3),& 
& dcplcFdChiSdL(3,5,6,3),dcplcFdChiSdR(3,5,6,3),dcplcFeChiSeL(3,5,6,3),dcplcFeChiSeR(3,5,6,3),& 
& dcplcFuChiSuL(3,5,6,3),dcplcFuChiSuR(3,5,6,3),dcplGluFdcSdL(3,6,3),dcplGluFdcSdR(3,6,3),& 
& dcplcFdFdhhL(3,3,3,3),dcplcFdFdhhR(3,3,3,3),dcplcChaFdcSuL(2,3,6,3),dcplcChaFdcSuR(2,3,6,3),& 
& dcplcFuFdcHpmL(3,3,2,3),dcplcFuFdcHpmR(3,3,2,3),dcplcFeFehhL(3,3,3,3),dcplcFeFehhR(3,3,3,3),& 
& dcplcChaFecSvL(2,3,3,3),dcplcChaFecSvR(2,3,3,3),dcplcFvFecHpmL(3,3,2,3),               & 
& dcplcFvFecHpmR(3,3,2,3),dcplGluFucSuL(3,6,3),dcplGluFucSuR(3,6,3),dcplcFuFuhhL(3,3,3,3),& 
& dcplcFuFuhhR(3,3,3,3),dcplcFdFuHpmL(3,3,2,3),dcplcFdFuHpmR(3,3,2,3),dcplcFeFvHpmL(3,3,2,3),& 
& dcplcFeFvHpmR(3,3,2,3),dcplcFdGluSdL(3,6,3),dcplcFdGluSdR(3,6,3),dcplcFuGluSuL(3,6,3), & 
& dcplcFuGluSuR(3,6,3),dcplcChacFuSdL(2,3,6,3),dcplcChacFuSdR(2,3,6,3),dcplcChacFvSeL(2,3,6,3),& 
& dcplcChacFvSeR(2,3,6,3),dcplcFdFdVGL(3,3,3),dcplcFdFdVGR(3,3,3),dcplcFuFuVGL(3,3,3),   & 
& dcplcFuFuVGR(3,3,3),dcplGluGluVGL(3),dcplGluGluVGR(3)

Complex(dp) :: dcplAhAhAhAh(3,3,3,3,3),dcplAhAhhhhh(3,3,3,3,3),dcplAhAhHpmcHpm(3,3,2,2,3),           & 
& dcplAhAhSdcSd(3,3,6,6,3),dcplAhAhSecSe(3,3,6,6,3),dcplAhAhSucSu(3,3,6,6,3),            & 
& dcplhhhhhhhh(3,3,3,3,3),dcplhhhhHpmcHpm(3,3,2,2,3),dcplhhhhSdcSd(3,3,6,6,3),           & 
& dcplhhhhSecSe(3,3,6,6,3),dcplhhhhSucSu(3,3,6,6,3),dcplHpmHpmcHpmcHpm(2,2,2,2,3),       & 
& dcplHpmSdcHpmcSd(2,6,2,6,3),dcplHpmSecHpmcSe(2,6,2,6,3),dcplHpmSucHpmcSu(2,6,2,6,3),   & 
& dcplHpmSvcHpmcSv(2,3,2,3,3),dcplSdSdcSdcSd(6,6,6,6,3),dcplSdSecSdcSe(6,6,6,6,3),       & 
& dcplSdSucSdcSu(6,6,6,6,3),dcplSeSecSecSe(6,6,6,6,3),dcplSeSvcSecSv(6,3,6,3,3),         & 
& dcplSuSucSucSu(6,6,6,6,3),dcplSdcSdVGVG(6,6,3),dcplSucSuVGVG(6,6,3)

Complex(dp) :: ddcplAhAhAh(3,3,3,3,3),ddcplAhAhhh(3,3,3,3,3),ddcplAhhhhh(3,3,3,3,3),ddcplAhHpmcHpm(3,2,2,3,3),& 
& ddcplAhSdcSd(3,6,6,3,3),ddcplAhSecSe(3,6,6,3,3),ddcplAhSucSu(3,6,6,3,3),               & 
& ddcplhhhhhh(3,3,3,3,3),ddcplhhHpmcHpm(3,2,2,3,3),ddcplhhSdcSd(3,6,6,3,3),              & 
& ddcplhhSecSe(3,6,6,3,3),ddcplhhSucSu(3,6,6,3,3),ddcplHpmSucSd(2,6,6,3,3),              & 
& ddcplHpmSvcSe(2,3,6,3,3),ddcplSdcHpmcSu(6,2,6,3,3),ddcplSecHpmcSv(6,2,3,3,3),          & 
& ddcplSdcSdVG(6,6,3,3),ddcplSucSuVG(6,6,3,3),ddcplVGVGVG(3,3),ddcplcChaChaAhL(2,2,3,3,3),& 
& ddcplcChaChaAhR(2,2,3,3,3),ddcplChiChiAhL(5,5,3,3,3),ddcplChiChiAhR(5,5,3,3,3),        & 
& ddcplcFdFdAhL(3,3,3,3,3),ddcplcFdFdAhR(3,3,3,3,3),ddcplcFeFeAhL(3,3,3,3,3),            & 
& ddcplcFeFeAhR(3,3,3,3,3),ddcplcFuFuAhL(3,3,3,3,3),ddcplcFuFuAhR(3,3,3,3,3),            & 
& ddcplChiChacHpmL(5,2,2,3,3),ddcplChiChacHpmR(5,2,2,3,3),ddcplChaFucSdL(2,3,6,3,3),     & 
& ddcplChaFucSdR(2,3,6,3,3),ddcplChaFvcSeL(2,3,6,3,3),ddcplChaFvcSeR(2,3,6,3,3),         & 
& ddcplcChaChahhL(2,2,3,3,3),ddcplcChaChahhR(2,2,3,3,3),ddcplcFdChaSuL(3,2,6,3,3),       & 
& ddcplcFdChaSuR(3,2,6,3,3),ddcplcFeChaSvL(3,2,3,3,3),ddcplcFeChaSvR(3,2,3,3,3),         & 
& ddcplChiChihhL(5,5,3,3,3),ddcplChiChihhR(5,5,3,3,3),ddcplChiFdcSdL(5,3,6,3,3),         & 
& ddcplChiFdcSdR(5,3,6,3,3),ddcplChiFecSeL(5,3,6,3,3),ddcplChiFecSeR(5,3,6,3,3),         & 
& ddcplChiFucSuL(5,3,6,3,3),ddcplChiFucSuR(5,3,6,3,3),ddcplcChaChiHpmL(2,5,2,3,3),       & 
& ddcplcChaChiHpmR(2,5,2,3,3),ddcplcFdChiSdL(3,5,6,3,3),ddcplcFdChiSdR(3,5,6,3,3),       & 
& ddcplcFeChiSeL(3,5,6,3,3),ddcplcFeChiSeR(3,5,6,3,3),ddcplcFuChiSuL(3,5,6,3,3),         & 
& ddcplcFuChiSuR(3,5,6,3,3),ddcplGluFdcSdL(3,6,3,3),ddcplGluFdcSdR(3,6,3,3),             & 
& ddcplcFdFdhhL(3,3,3,3,3),ddcplcFdFdhhR(3,3,3,3,3),ddcplcChaFdcSuL(2,3,6,3,3),          & 
& ddcplcChaFdcSuR(2,3,6,3,3),ddcplcFuFdcHpmL(3,3,2,3,3),ddcplcFuFdcHpmR(3,3,2,3,3),      & 
& ddcplcFeFehhL(3,3,3,3,3),ddcplcFeFehhR(3,3,3,3,3),ddcplcChaFecSvL(2,3,3,3,3),          & 
& ddcplcChaFecSvR(2,3,3,3,3),ddcplcFvFecHpmL(3,3,2,3,3),ddcplcFvFecHpmR(3,3,2,3,3),      & 
& ddcplGluFucSuL(3,6,3,3),ddcplGluFucSuR(3,6,3,3),ddcplcFuFuhhL(3,3,3,3,3),              & 
& ddcplcFuFuhhR(3,3,3,3,3),ddcplcFdFuHpmL(3,3,2,3,3),ddcplcFdFuHpmR(3,3,2,3,3),          & 
& ddcplcFeFvHpmL(3,3,2,3,3),ddcplcFeFvHpmR(3,3,2,3,3),ddcplcFdGluSdL(3,6,3,3),           & 
& ddcplcFdGluSdR(3,6,3,3),ddcplcFuGluSuL(3,6,3,3),ddcplcFuGluSuR(3,6,3,3),               & 
& ddcplcChacFuSdL(2,3,6,3,3),ddcplcChacFuSdR(2,3,6,3,3),ddcplcChacFvSeL(2,3,6,3,3),      & 
& ddcplcChacFvSeR(2,3,6,3,3),ddcplcFdFdVGL(3,3,3,3),ddcplcFdFdVGR(3,3,3,3),              & 
& ddcplcFuFuVGL(3,3,3,3),ddcplcFuFuVGR(3,3,3,3),ddcplGluGluVGL(3,3),ddcplGluGluVGR(3,3)

Complex(dp) :: ddcplAhAhAhAh(3,3,3,3,3,3),ddcplAhAhhhhh(3,3,3,3,3,3),ddcplAhAhHpmcHpm(3,3,2,2,3,3),  & 
& ddcplAhAhSdcSd(3,3,6,6,3,3),ddcplAhAhSecSe(3,3,6,6,3,3),ddcplAhAhSucSu(3,3,6,6,3,3),   & 
& ddcplhhhhhhhh(3,3,3,3,3,3),ddcplhhhhHpmcHpm(3,3,2,2,3,3),ddcplhhhhSdcSd(3,3,6,6,3,3),  & 
& ddcplhhhhSecSe(3,3,6,6,3,3),ddcplhhhhSucSu(3,3,6,6,3,3),ddcplHpmHpmcHpmcHpm(2,2,2,2,3,3),& 
& ddcplHpmSdcHpmcSd(2,6,2,6,3,3),ddcplHpmSecHpmcSe(2,6,2,6,3,3),ddcplHpmSucHpmcSu(2,6,2,6,3,3),& 
& ddcplHpmSvcHpmcSv(2,3,2,3,3,3),ddcplSdSdcSdcSd(6,6,6,6,3,3),ddcplSdSecSdcSe(6,6,6,6,3,3),& 
& ddcplSdSucSdcSu(6,6,6,6,3,3),ddcplSeSecSecSe(6,6,6,6,3,3),ddcplSeSvcSecSv(6,3,6,3,3,3),& 
& ddcplSuSucSucSu(6,6,6,6,3,3),ddcplSdcSdVGVG(6,6,3,3),ddcplSucSuVGVG(6,6,3,3)

Real(dp) :: MSd(6),MSd2(6),MSv(3),MSv2(3),MSu(6),MSu2(6),MSe(6),MSe2(6),Mhh(3),Mhh2(3),           & 
& MAh(3),MAh2(3),MHpm(2),MHpm2(2),MChi(5),MChi2(5),MCha(2),MCha2(2),MFe(3),              & 
& MFe2(3),MFd(3),MFd2(3),MFu(3),MFu2(3),MGlu,MGlu2,MVZ,MVZ2,MVWm,MVWm2

Complex(dp) :: dMSd(6,3),dMSd2(6,3),dMSv(3,3),dMSv2(3,3),dMSu(6,3),dMSu2(6,3),dMSe(6,3),             & 
& dMSe2(6,3),dMhh(3,3),dMhh2(3,3),dMAh(3,3),dMAh2(3,3),dMHpm(2,3),dMHpm2(2,3),           & 
& dMChi(5,3),dMChi2(5,3),dMCha(2,3),dMCha2(2,3),dMFe(3,3),dMFe2(3,3),dMFd(3,3),          & 
& dMFd2(3,3),dMFu(3,3),dMFu2(3,3),dMGlu(1,3),dMGlu2(1,3),dMVZ(1,3),dMVZ2(1,3),           & 
& dMVWm(1,3),dMVWm2(1,3)

Complex(dp) :: ddMSd(6,3,3),ddMSd2(6,3,3),ddMSv(3,3,3),ddMSv2(3,3,3),ddMSu(6,3,3),ddMSu2(6,3,3),     & 
& ddMSe(6,3,3),ddMSe2(6,3,3),ddMhh(3,3,3),ddMhh2(3,3,3),ddMAh(3,3,3),ddMAh2(3,3,3),      & 
& ddMHpm(2,3,3),ddMHpm2(2,3,3),ddMChi(5,3,3),ddMChi2(5,3,3),ddMCha(2,3,3),               & 
& ddMCha2(2,3,3),ddMFe(3,3,3),ddMFe2(3,3,3),ddMFd(3,3,3),ddMFd2(3,3,3),ddMFu(3,3,3),     & 
& ddMFu2(3,3,3),ddMGlu(1,3,3),ddMGlu2(1,3,3),ddMVZ(1,3,3),ddMVZ2(1,3,3),ddMVWm(1,3,3),   & 
& ddMVWm2(1,3,3)

!! ------------------------------------------------- 
!! Calculate masses, couplings and their derivatives 
!! ------------------------------------------------- 

Do i1=1,3
Call FirstDerivativeMassesCoups(i1,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,             & 
& Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Call GToMassesCoups(gout,MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,MAh,            & 
& MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,           & 
& MVZ,MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,             & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,               & 
& cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,           & 
& cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,        & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,        & 
& cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,           & 
& cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,             & 
& cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,cplSucSuVGVG)

dMSd(:,i1) = MSd
dMSd2(:,i1) = MSd2
dMSv(:,i1) = MSv
dMSv2(:,i1) = MSv2
dMSu(:,i1) = MSu
dMSu2(:,i1) = MSu2
dMSe(:,i1) = MSe
dMSe2(:,i1) = MSe2
dMhh(:,i1) = Mhh
dMhh2(:,i1) = Mhh2
dMAh(:,i1) = MAh
dMAh2(:,i1) = MAh2
dMHpm(:,i1) = MHpm
dMHpm2(:,i1) = MHpm2
dMChi(:,i1) = MChi
dMChi2(:,i1) = MChi2
dMCha(:,i1) = MCha
dMCha2(:,i1) = MCha2
dMFe(:,i1) = MFe
dMFe2(:,i1) = MFe2
dMFd(:,i1) = MFd
dMFd2(:,i1) = MFd2
dMFu(:,i1) = MFu
dMFu2(:,i1) = MFu2
dMGlu(:,i1) = MGlu
dMGlu2(:,i1) = MGlu2
dMVZ(:,i1) = MVZ
dMVZ2(:,i1) = MVZ2
dMVWm(:,i1) = MVWm
dMVWm2(:,i1) = MVWm2
dcplAhAhAh(:,:,:,i1) = cplAhAhAh
dcplAhAhhh(:,:,:,i1) = cplAhAhhh
dcplAhhhhh(:,:,:,i1) = cplAhhhhh
dcplAhHpmcHpm(:,:,:,i1) = cplAhHpmcHpm
dcplAhSdcSd(:,:,:,i1) = cplAhSdcSd
dcplAhSecSe(:,:,:,i1) = cplAhSecSe
dcplAhSucSu(:,:,:,i1) = cplAhSucSu
dcplhhhhhh(:,:,:,i1) = cplhhhhhh
dcplhhHpmcHpm(:,:,:,i1) = cplhhHpmcHpm
dcplhhSdcSd(:,:,:,i1) = cplhhSdcSd
dcplhhSecSe(:,:,:,i1) = cplhhSecSe
dcplhhSucSu(:,:,:,i1) = cplhhSucSu
dcplHpmSucSd(:,:,:,i1) = cplHpmSucSd
dcplHpmSvcSe(:,:,:,i1) = cplHpmSvcSe
dcplSdcHpmcSu(:,:,:,i1) = cplSdcHpmcSu
dcplSecHpmcSv(:,:,:,i1) = cplSecHpmcSv
dcplSdcSdVG(:,:,i1) = cplSdcSdVG
dcplSucSuVG(:,:,i1) = cplSucSuVG
dcplVGVGVG(i1) = cplVGVGVG
dcplcChaChaAhL(:,:,:,i1) = cplcChaChaAhL
dcplcChaChaAhR(:,:,:,i1) = cplcChaChaAhR
dcplChiChiAhL(:,:,:,i1) = cplChiChiAhL
dcplChiChiAhR(:,:,:,i1) = cplChiChiAhR
dcplcFdFdAhL(:,:,:,i1) = cplcFdFdAhL
dcplcFdFdAhR(:,:,:,i1) = cplcFdFdAhR
dcplcFeFeAhL(:,:,:,i1) = cplcFeFeAhL
dcplcFeFeAhR(:,:,:,i1) = cplcFeFeAhR
dcplcFuFuAhL(:,:,:,i1) = cplcFuFuAhL
dcplcFuFuAhR(:,:,:,i1) = cplcFuFuAhR
dcplChiChacHpmL(:,:,:,i1) = cplChiChacHpmL
dcplChiChacHpmR(:,:,:,i1) = cplChiChacHpmR
dcplChaFucSdL(:,:,:,i1) = cplChaFucSdL
dcplChaFucSdR(:,:,:,i1) = cplChaFucSdR
dcplChaFvcSeL(:,:,:,i1) = cplChaFvcSeL
dcplChaFvcSeR(:,:,:,i1) = cplChaFvcSeR
dcplcChaChahhL(:,:,:,i1) = cplcChaChahhL
dcplcChaChahhR(:,:,:,i1) = cplcChaChahhR
dcplcFdChaSuL(:,:,:,i1) = cplcFdChaSuL
dcplcFdChaSuR(:,:,:,i1) = cplcFdChaSuR
dcplcFeChaSvL(:,:,:,i1) = cplcFeChaSvL
dcplcFeChaSvR(:,:,:,i1) = cplcFeChaSvR
dcplChiChihhL(:,:,:,i1) = cplChiChihhL
dcplChiChihhR(:,:,:,i1) = cplChiChihhR
dcplChiFdcSdL(:,:,:,i1) = cplChiFdcSdL
dcplChiFdcSdR(:,:,:,i1) = cplChiFdcSdR
dcplChiFecSeL(:,:,:,i1) = cplChiFecSeL
dcplChiFecSeR(:,:,:,i1) = cplChiFecSeR
dcplChiFucSuL(:,:,:,i1) = cplChiFucSuL
dcplChiFucSuR(:,:,:,i1) = cplChiFucSuR
dcplcChaChiHpmL(:,:,:,i1) = cplcChaChiHpmL
dcplcChaChiHpmR(:,:,:,i1) = cplcChaChiHpmR
dcplcFdChiSdL(:,:,:,i1) = cplcFdChiSdL
dcplcFdChiSdR(:,:,:,i1) = cplcFdChiSdR
dcplcFeChiSeL(:,:,:,i1) = cplcFeChiSeL
dcplcFeChiSeR(:,:,:,i1) = cplcFeChiSeR
dcplcFuChiSuL(:,:,:,i1) = cplcFuChiSuL
dcplcFuChiSuR(:,:,:,i1) = cplcFuChiSuR
dcplGluFdcSdL(:,:,i1) = cplGluFdcSdL
dcplGluFdcSdR(:,:,i1) = cplGluFdcSdR
dcplcFdFdhhL(:,:,:,i1) = cplcFdFdhhL
dcplcFdFdhhR(:,:,:,i1) = cplcFdFdhhR
dcplcChaFdcSuL(:,:,:,i1) = cplcChaFdcSuL
dcplcChaFdcSuR(:,:,:,i1) = cplcChaFdcSuR
dcplcFuFdcHpmL(:,:,:,i1) = cplcFuFdcHpmL
dcplcFuFdcHpmR(:,:,:,i1) = cplcFuFdcHpmR
dcplcFeFehhL(:,:,:,i1) = cplcFeFehhL
dcplcFeFehhR(:,:,:,i1) = cplcFeFehhR
dcplcChaFecSvL(:,:,:,i1) = cplcChaFecSvL
dcplcChaFecSvR(:,:,:,i1) = cplcChaFecSvR
dcplcFvFecHpmL(:,:,:,i1) = cplcFvFecHpmL
dcplcFvFecHpmR(:,:,:,i1) = cplcFvFecHpmR
dcplGluFucSuL(:,:,i1) = cplGluFucSuL
dcplGluFucSuR(:,:,i1) = cplGluFucSuR
dcplcFuFuhhL(:,:,:,i1) = cplcFuFuhhL
dcplcFuFuhhR(:,:,:,i1) = cplcFuFuhhR
dcplcFdFuHpmL(:,:,:,i1) = cplcFdFuHpmL
dcplcFdFuHpmR(:,:,:,i1) = cplcFdFuHpmR
dcplcFeFvHpmL(:,:,:,i1) = cplcFeFvHpmL
dcplcFeFvHpmR(:,:,:,i1) = cplcFeFvHpmR
dcplcFdGluSdL(:,:,i1) = cplcFdGluSdL
dcplcFdGluSdR(:,:,i1) = cplcFdGluSdR
dcplcFuGluSuL(:,:,i1) = cplcFuGluSuL
dcplcFuGluSuR(:,:,i1) = cplcFuGluSuR
dcplcChacFuSdL(:,:,:,i1) = cplcChacFuSdL
dcplcChacFuSdR(:,:,:,i1) = cplcChacFuSdR
dcplcChacFvSeL(:,:,:,i1) = cplcChacFvSeL
dcplcChacFvSeR(:,:,:,i1) = cplcChacFvSeR
dcplcFdFdVGL(:,:,i1) = cplcFdFdVGL
dcplcFdFdVGR(:,:,i1) = cplcFdFdVGR
dcplcFuFuVGL(:,:,i1) = cplcFuFuVGL
dcplcFuFuVGR(:,:,i1) = cplcFuFuVGR
dcplGluGluVGL(i1) = cplGluGluVGL
dcplGluGluVGR(i1) = cplGluGluVGR
dcplAhAhAhAh(:,:,:,:,i1) = cplAhAhAhAh
dcplAhAhhhhh(:,:,:,:,i1) = cplAhAhhhhh
dcplAhAhHpmcHpm(:,:,:,:,i1) = cplAhAhHpmcHpm
dcplAhAhSdcSd(:,:,:,:,i1) = cplAhAhSdcSd
dcplAhAhSecSe(:,:,:,:,i1) = cplAhAhSecSe
dcplAhAhSucSu(:,:,:,:,i1) = cplAhAhSucSu
dcplhhhhhhhh(:,:,:,:,i1) = cplhhhhhhhh
dcplhhhhHpmcHpm(:,:,:,:,i1) = cplhhhhHpmcHpm
dcplhhhhSdcSd(:,:,:,:,i1) = cplhhhhSdcSd
dcplhhhhSecSe(:,:,:,:,i1) = cplhhhhSecSe
dcplhhhhSucSu(:,:,:,:,i1) = cplhhhhSucSu
dcplHpmHpmcHpmcHpm(:,:,:,:,i1) = cplHpmHpmcHpmcHpm
dcplHpmSdcHpmcSd(:,:,:,:,i1) = cplHpmSdcHpmcSd
dcplHpmSecHpmcSe(:,:,:,:,i1) = cplHpmSecHpmcSe
dcplHpmSucHpmcSu(:,:,:,:,i1) = cplHpmSucHpmcSu
dcplHpmSvcHpmcSv(:,:,:,:,i1) = cplHpmSvcHpmcSv
dcplSdSdcSdcSd(:,:,:,:,i1) = cplSdSdcSdcSd
dcplSdSecSdcSe(:,:,:,:,i1) = cplSdSecSdcSe
dcplSdSucSdcSu(:,:,:,:,i1) = cplSdSucSdcSu
dcplSeSecSecSe(:,:,:,:,i1) = cplSeSecSecSe
dcplSeSvcSecSv(:,:,:,:,i1) = cplSeSvcSecSv
dcplSuSucSucSu(:,:,:,:,i1) = cplSuSucSucSu
dcplSdcSdVGVG(:,:,i1) = cplSdcSdVGVG
dcplSucSuVGVG(:,:,i1) = cplSucSuVGVG
End Do 
 
Do i1=1,3
  Do i2=i1,3
Call SecondDerivativeMassesCoups(i1,i2,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,               & 
& Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Call GToMassesCoups(gout,MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,MAh,            & 
& MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,           & 
& MVZ,MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,             & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,               & 
& cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,           & 
& cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,        & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,        & 
& cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,           & 
& cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,             & 
& cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,cplSucSuVGVG)

ddMSd(:,i1,i2) = MSd
ddMSd2(:,i1,i2) = MSd2
ddMSv(:,i1,i2) = MSv
ddMSv2(:,i1,i2) = MSv2
ddMSu(:,i1,i2) = MSu
ddMSu2(:,i1,i2) = MSu2
ddMSe(:,i1,i2) = MSe
ddMSe2(:,i1,i2) = MSe2
ddMhh(:,i1,i2) = Mhh
ddMhh2(:,i1,i2) = Mhh2
ddMAh(:,i1,i2) = MAh
ddMAh2(:,i1,i2) = MAh2
ddMHpm(:,i1,i2) = MHpm
ddMHpm2(:,i1,i2) = MHpm2
ddMChi(:,i1,i2) = MChi
ddMChi2(:,i1,i2) = MChi2
ddMCha(:,i1,i2) = MCha
ddMCha2(:,i1,i2) = MCha2
ddMFe(:,i1,i2) = MFe
ddMFe2(:,i1,i2) = MFe2
ddMFd(:,i1,i2) = MFd
ddMFd2(:,i1,i2) = MFd2
ddMFu(:,i1,i2) = MFu
ddMFu2(:,i1,i2) = MFu2
ddMGlu(:,i1,i2) = MGlu
ddMGlu2(:,i1,i2) = MGlu2
ddMVZ(:,i1,i2) = MVZ
ddMVZ2(:,i1,i2) = MVZ2
ddMVWm(:,i1,i2) = MVWm
ddMVWm2(:,i1,i2) = MVWm2
ddcplAhAhAh(:,:,:,i1,i2) = cplAhAhAh
ddcplAhAhhh(:,:,:,i1,i2) = cplAhAhhh
ddcplAhhhhh(:,:,:,i1,i2) = cplAhhhhh
ddcplAhHpmcHpm(:,:,:,i1,i2) = cplAhHpmcHpm
ddcplAhSdcSd(:,:,:,i1,i2) = cplAhSdcSd
ddcplAhSecSe(:,:,:,i1,i2) = cplAhSecSe
ddcplAhSucSu(:,:,:,i1,i2) = cplAhSucSu
ddcplhhhhhh(:,:,:,i1,i2) = cplhhhhhh
ddcplhhHpmcHpm(:,:,:,i1,i2) = cplhhHpmcHpm
ddcplhhSdcSd(:,:,:,i1,i2) = cplhhSdcSd
ddcplhhSecSe(:,:,:,i1,i2) = cplhhSecSe
ddcplhhSucSu(:,:,:,i1,i2) = cplhhSucSu
ddcplHpmSucSd(:,:,:,i1,i2) = cplHpmSucSd
ddcplHpmSvcSe(:,:,:,i1,i2) = cplHpmSvcSe
ddcplSdcHpmcSu(:,:,:,i1,i2) = cplSdcHpmcSu
ddcplSecHpmcSv(:,:,:,i1,i2) = cplSecHpmcSv
ddcplSdcSdVG(:,:,i1,i2) = cplSdcSdVG
ddcplSucSuVG(:,:,i1,i2) = cplSucSuVG
ddcplVGVGVG(i1,i2) = cplVGVGVG
ddcplcChaChaAhL(:,:,:,i1,i2) = cplcChaChaAhL
ddcplcChaChaAhR(:,:,:,i1,i2) = cplcChaChaAhR
ddcplChiChiAhL(:,:,:,i1,i2) = cplChiChiAhL
ddcplChiChiAhR(:,:,:,i1,i2) = cplChiChiAhR
ddcplcFdFdAhL(:,:,:,i1,i2) = cplcFdFdAhL
ddcplcFdFdAhR(:,:,:,i1,i2) = cplcFdFdAhR
ddcplcFeFeAhL(:,:,:,i1,i2) = cplcFeFeAhL
ddcplcFeFeAhR(:,:,:,i1,i2) = cplcFeFeAhR
ddcplcFuFuAhL(:,:,:,i1,i2) = cplcFuFuAhL
ddcplcFuFuAhR(:,:,:,i1,i2) = cplcFuFuAhR
ddcplChiChacHpmL(:,:,:,i1,i2) = cplChiChacHpmL
ddcplChiChacHpmR(:,:,:,i1,i2) = cplChiChacHpmR
ddcplChaFucSdL(:,:,:,i1,i2) = cplChaFucSdL
ddcplChaFucSdR(:,:,:,i1,i2) = cplChaFucSdR
ddcplChaFvcSeL(:,:,:,i1,i2) = cplChaFvcSeL
ddcplChaFvcSeR(:,:,:,i1,i2) = cplChaFvcSeR
ddcplcChaChahhL(:,:,:,i1,i2) = cplcChaChahhL
ddcplcChaChahhR(:,:,:,i1,i2) = cplcChaChahhR
ddcplcFdChaSuL(:,:,:,i1,i2) = cplcFdChaSuL
ddcplcFdChaSuR(:,:,:,i1,i2) = cplcFdChaSuR
ddcplcFeChaSvL(:,:,:,i1,i2) = cplcFeChaSvL
ddcplcFeChaSvR(:,:,:,i1,i2) = cplcFeChaSvR
ddcplChiChihhL(:,:,:,i1,i2) = cplChiChihhL
ddcplChiChihhR(:,:,:,i1,i2) = cplChiChihhR
ddcplChiFdcSdL(:,:,:,i1,i2) = cplChiFdcSdL
ddcplChiFdcSdR(:,:,:,i1,i2) = cplChiFdcSdR
ddcplChiFecSeL(:,:,:,i1,i2) = cplChiFecSeL
ddcplChiFecSeR(:,:,:,i1,i2) = cplChiFecSeR
ddcplChiFucSuL(:,:,:,i1,i2) = cplChiFucSuL
ddcplChiFucSuR(:,:,:,i1,i2) = cplChiFucSuR
ddcplcChaChiHpmL(:,:,:,i1,i2) = cplcChaChiHpmL
ddcplcChaChiHpmR(:,:,:,i1,i2) = cplcChaChiHpmR
ddcplcFdChiSdL(:,:,:,i1,i2) = cplcFdChiSdL
ddcplcFdChiSdR(:,:,:,i1,i2) = cplcFdChiSdR
ddcplcFeChiSeL(:,:,:,i1,i2) = cplcFeChiSeL
ddcplcFeChiSeR(:,:,:,i1,i2) = cplcFeChiSeR
ddcplcFuChiSuL(:,:,:,i1,i2) = cplcFuChiSuL
ddcplcFuChiSuR(:,:,:,i1,i2) = cplcFuChiSuR
ddcplGluFdcSdL(:,:,i1,i2) = cplGluFdcSdL
ddcplGluFdcSdR(:,:,i1,i2) = cplGluFdcSdR
ddcplcFdFdhhL(:,:,:,i1,i2) = cplcFdFdhhL
ddcplcFdFdhhR(:,:,:,i1,i2) = cplcFdFdhhR
ddcplcChaFdcSuL(:,:,:,i1,i2) = cplcChaFdcSuL
ddcplcChaFdcSuR(:,:,:,i1,i2) = cplcChaFdcSuR
ddcplcFuFdcHpmL(:,:,:,i1,i2) = cplcFuFdcHpmL
ddcplcFuFdcHpmR(:,:,:,i1,i2) = cplcFuFdcHpmR
ddcplcFeFehhL(:,:,:,i1,i2) = cplcFeFehhL
ddcplcFeFehhR(:,:,:,i1,i2) = cplcFeFehhR
ddcplcChaFecSvL(:,:,:,i1,i2) = cplcChaFecSvL
ddcplcChaFecSvR(:,:,:,i1,i2) = cplcChaFecSvR
ddcplcFvFecHpmL(:,:,:,i1,i2) = cplcFvFecHpmL
ddcplcFvFecHpmR(:,:,:,i1,i2) = cplcFvFecHpmR
ddcplGluFucSuL(:,:,i1,i2) = cplGluFucSuL
ddcplGluFucSuR(:,:,i1,i2) = cplGluFucSuR
ddcplcFuFuhhL(:,:,:,i1,i2) = cplcFuFuhhL
ddcplcFuFuhhR(:,:,:,i1,i2) = cplcFuFuhhR
ddcplcFdFuHpmL(:,:,:,i1,i2) = cplcFdFuHpmL
ddcplcFdFuHpmR(:,:,:,i1,i2) = cplcFdFuHpmR
ddcplcFeFvHpmL(:,:,:,i1,i2) = cplcFeFvHpmL
ddcplcFeFvHpmR(:,:,:,i1,i2) = cplcFeFvHpmR
ddcplcFdGluSdL(:,:,i1,i2) = cplcFdGluSdL
ddcplcFdGluSdR(:,:,i1,i2) = cplcFdGluSdR
ddcplcFuGluSuL(:,:,i1,i2) = cplcFuGluSuL
ddcplcFuGluSuR(:,:,i1,i2) = cplcFuGluSuR
ddcplcChacFuSdL(:,:,:,i1,i2) = cplcChacFuSdL
ddcplcChacFuSdR(:,:,:,i1,i2) = cplcChacFuSdR
ddcplcChacFvSeL(:,:,:,i1,i2) = cplcChacFvSeL
ddcplcChacFvSeR(:,:,:,i1,i2) = cplcChacFvSeR
ddcplcFdFdVGL(:,:,i1,i2) = cplcFdFdVGL
ddcplcFdFdVGR(:,:,i1,i2) = cplcFdFdVGR
ddcplcFuFuVGL(:,:,i1,i2) = cplcFuFuVGL
ddcplcFuFuVGR(:,:,i1,i2) = cplcFuFuVGR
ddcplGluGluVGL(i1,i2) = cplGluGluVGL
ddcplGluGluVGR(i1,i2) = cplGluGluVGR
ddcplAhAhAhAh(:,:,:,:,i1,i2) = cplAhAhAhAh
ddcplAhAhhhhh(:,:,:,:,i1,i2) = cplAhAhhhhh
ddcplAhAhHpmcHpm(:,:,:,:,i1,i2) = cplAhAhHpmcHpm
ddcplAhAhSdcSd(:,:,:,:,i1,i2) = cplAhAhSdcSd
ddcplAhAhSecSe(:,:,:,:,i1,i2) = cplAhAhSecSe
ddcplAhAhSucSu(:,:,:,:,i1,i2) = cplAhAhSucSu
ddcplhhhhhhhh(:,:,:,:,i1,i2) = cplhhhhhhhh
ddcplhhhhHpmcHpm(:,:,:,:,i1,i2) = cplhhhhHpmcHpm
ddcplhhhhSdcSd(:,:,:,:,i1,i2) = cplhhhhSdcSd
ddcplhhhhSecSe(:,:,:,:,i1,i2) = cplhhhhSecSe
ddcplhhhhSucSu(:,:,:,:,i1,i2) = cplhhhhSucSu
ddcplHpmHpmcHpmcHpm(:,:,:,:,i1,i2) = cplHpmHpmcHpmcHpm
ddcplHpmSdcHpmcSd(:,:,:,:,i1,i2) = cplHpmSdcHpmcSd
ddcplHpmSecHpmcSe(:,:,:,:,i1,i2) = cplHpmSecHpmcSe
ddcplHpmSucHpmcSu(:,:,:,:,i1,i2) = cplHpmSucHpmcSu
ddcplHpmSvcHpmcSv(:,:,:,:,i1,i2) = cplHpmSvcHpmcSv
ddcplSdSdcSdcSd(:,:,:,:,i1,i2) = cplSdSdcSdcSd
ddcplSdSecSdcSe(:,:,:,:,i1,i2) = cplSdSecSdcSe
ddcplSdSucSdcSu(:,:,:,:,i1,i2) = cplSdSucSdcSu
ddcplSeSecSecSe(:,:,:,:,i1,i2) = cplSeSecSecSe
ddcplSeSvcSecSv(:,:,:,:,i1,i2) = cplSeSvcSecSv
ddcplSuSucSucSu(:,:,:,:,i1,i2) = cplSuSucSucSu
ddcplSdcSdVGVG(:,:,i1,i2) = cplSdcSdVGVG
ddcplSucSuVGVG(:,:,i1,i2) = cplSucSuVGVG
  End Do 
 End Do 
 
Call TreeMassesEffPot(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,.True.,kont)

Call CouplingsForEffPot3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,Yd,Td,ZD,Ye,               & 
& Te,ZE,Yu,Tu,ZU,ZV,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,cplAhAhhh,          & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,    & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,              & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,      & 
& cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,       & 
& cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR)

Call CouplingsForEffPot4(lam,kap,ZA,ZH,ZP,Yd,ZD,Ye,ZE,Yu,ZU,ZV,g3,cplAhAhAhAh,        & 
& cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,         & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,               & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,    & 
& cplSucSuVGVG)



!! ------------------------------------------------- 
!! Calculate derivative of effective potential      
!! ------------------------------------------------- 



Q2 = getRenormalizationScale()
Do iv1=1,3
  Do iv2=iv1,3
    result = ZeroC
    result_ti = ZeroC
    results1 = ZeroC
    results1_ti = ZeroC
    results2 = ZeroC
    results2_ti = ZeroC


! ----- Topology1 (sunrise): diagrams w. 3 Particles and 2 Vertices


! ----- diagrams of type SSS, 14 ------ 

! ---- Ah,Ah,Ah ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhAh(i1,i2,i3)
coup2 = cplAhAhAh(i1,i2,i3)
Di_coup1 = dcplAhAhAh(i1,i2,i3,iv1)
Dj_coup1 = dcplAhAhAh(i1,i2,i3,iv2)
DDcoup1 = ddcplAhAhAh(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MAh2(i2),MAh2(i3),dMAh2(i1,iv1)            & 
& ,dMAh2(i2,iv1),dMAh2(i3,iv1),dMAh2(i1,iv2),dMAh2(i2,iv2),dMAh2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMAh2(i2,iv1,iv2),ddMAh2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 1._dp/12._dp
colorfactor = 1
results1(1)=results1(1) + coeff*colorfactor*temp
results1_ti(1)=results1_ti(1) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(1).eq.results1(1)))  write(*,*) 'NaN at SSS C[Ah, Ah, Ah]' 
! ---- Ah,Ah,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhhh(i1,i2,i3)
coup2 = cplAhAhhh(i1,i2,i3)
Di_coup1 = dcplAhAhhh(i1,i2,i3,iv1)
Dj_coup1 = dcplAhAhhh(i1,i2,i3,iv2)
DDcoup1 = ddcplAhAhhh(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MAh2(i2),Mhh2(i3),dMAh2(i1,iv1)            & 
& ,dMAh2(i2,iv1),dMhh2(i3,iv1),dMAh2(i1,iv2),dMAh2(i2,iv2),dMhh2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMAh2(i2,iv1,iv2),ddMhh2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.25_dp
colorfactor = 1
results1(2)=results1(2) + coeff*colorfactor*temp
results1_ti(2)=results1_ti(2) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(2).eq.results1(2)))  write(*,*) 'NaN at SSS C[Ah, Ah, hh]' 
! ---- Ah,hh,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhhhhh(i1,i2,i3)
coup2 = cplAhhhhh(i1,i2,i3)
Di_coup1 = dcplAhhhhh(i1,i2,i3,iv1)
Dj_coup1 = dcplAhhhhh(i1,i2,i3,iv2)
DDcoup1 = ddcplAhhhhh(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),Mhh2(i2),Mhh2(i3),dMAh2(i1,iv1)            & 
& ,dMhh2(i2,iv1),dMhh2(i3,iv1),dMAh2(i1,iv2),dMhh2(i2,iv2),dMhh2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMhh2(i2,iv1,iv2),ddMhh2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.25_dp
colorfactor = 1
results1(3)=results1(3) + coeff*colorfactor*temp
results1_ti(3)=results1_ti(3) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(3).eq.results1(3)))  write(*,*) 'NaN at SSS C[Ah, hh, hh]' 
! ---- Ah,Hpm,conj[Hpm] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplAhHpmcHpm(i1,i2,i3)
coup2 = cplAhHpmcHpm(i1,i3,i2)
Di_coup1 = dcplAhHpmcHpm(i1,i2,i3,iv1)
Dj_coup1 = dcplAhHpmcHpm(i1,i2,i3,iv2)
DDcoup1 = ddcplAhHpmcHpm(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MHpm2(i2),MHpm2(i3),dMAh2(i1,iv1)          & 
& ,dMHpm2(i2,iv1),dMHpm2(i3,iv1),dMAh2(i1,iv2),dMHpm2(i2,iv2),dMHpm2(i3,iv2)             & 
& ,ddMAh2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),ddMHpm2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 1
results1(4)=results1(4) + coeff*colorfactor*temp
results1_ti(4)=results1_ti(4) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(4).eq.results1(4)))  write(*,*) 'NaN at SSS C[Ah, Hpm, conj[Hpm]]' 
! ---- Ah,Sd,conj[Sd] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSdcSd(i1,i2,i3)
coup2 = cplAhSdcSd(i1,i3,i2)
Di_coup1 = dcplAhSdcSd(i1,i2,i3,iv1)
Dj_coup1 = dcplAhSdcSd(i1,i2,i3,iv2)
DDcoup1 = ddcplAhSdcSd(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MSd2(i2),MSd2(i3),dMAh2(i1,iv1)            & 
& ,dMSd2(i2,iv1),dMSd2(i3,iv1),dMAh2(i1,iv2),dMSd2(i2,iv2),dMSd2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMSd2(i2,iv1,iv2),ddMSd2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 3
results1(5)=results1(5) + coeff*colorfactor*temp
results1_ti(5)=results1_ti(5) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(5).eq.results1(5)))  write(*,*) 'NaN at SSS C[Ah, Sd, conj[Sd]]' 
! ---- Ah,Se,conj[Se] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSecSe(i1,i2,i3)
coup2 = cplAhSecSe(i1,i3,i2)
Di_coup1 = dcplAhSecSe(i1,i2,i3,iv1)
Dj_coup1 = dcplAhSecSe(i1,i2,i3,iv2)
DDcoup1 = ddcplAhSecSe(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MSe2(i2),MSe2(i3),dMAh2(i1,iv1)            & 
& ,dMSe2(i2,iv1),dMSe2(i3,iv1),dMAh2(i1,iv2),dMSe2(i2,iv2),dMSe2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMSe2(i2,iv1,iv2),ddMSe2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 1
results1(6)=results1(6) + coeff*colorfactor*temp
results1_ti(6)=results1_ti(6) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(6).eq.results1(6)))  write(*,*) 'NaN at SSS C[Ah, Se, conj[Se]]' 
! ---- Ah,Su,conj[Su] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSucSu(i1,i2,i3)
coup2 = cplAhSucSu(i1,i3,i2)
Di_coup1 = dcplAhSucSu(i1,i2,i3,iv1)
Dj_coup1 = dcplAhSucSu(i1,i2,i3,iv2)
DDcoup1 = ddcplAhSucSu(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MAh2(i1),MSu2(i2),MSu2(i3),dMAh2(i1,iv1)            & 
& ,dMSu2(i2,iv1),dMSu2(i3,iv1),dMAh2(i1,iv2),dMSu2(i2,iv2),dMSu2(i3,iv2),ddMAh2(i1,iv1,iv2)& 
& ,ddMSu2(i2,iv1,iv2),ddMSu2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 3
results1(7)=results1(7) + coeff*colorfactor*temp
results1_ti(7)=results1_ti(7) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(7).eq.results1(7)))  write(*,*) 'NaN at SSS C[Ah, Su, conj[Su]]' 
! ---- hh,hh,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplhhhhhh(i1,i2,i3)
coup2 = cplhhhhhh(i1,i2,i3)
Di_coup1 = dcplhhhhhh(i1,i2,i3,iv1)
Dj_coup1 = dcplhhhhhh(i1,i2,i3,iv2)
DDcoup1 = ddcplhhhhhh(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(Mhh2(i1),Mhh2(i2),Mhh2(i3),dMhh2(i1,iv1)            & 
& ,dMhh2(i2,iv1),dMhh2(i3,iv1),dMhh2(i1,iv2),dMhh2(i2,iv2),dMhh2(i3,iv2),ddMhh2(i1,iv1,iv2)& 
& ,ddMhh2(i2,iv1,iv2),ddMhh2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 1._dp/12._dp
colorfactor = 1
results1(8)=results1(8) + coeff*colorfactor*temp
results1_ti(8)=results1_ti(8) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(8).eq.results1(8)))  write(*,*) 'NaN at SSS C[hh, hh, hh]' 
! ---- hh,Hpm,conj[Hpm] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplhhHpmcHpm(i1,i2,i3)
coup2 = cplhhHpmcHpm(i1,i3,i2)
Di_coup1 = dcplhhHpmcHpm(i1,i2,i3,iv1)
Dj_coup1 = dcplhhHpmcHpm(i1,i2,i3,iv2)
DDcoup1 = ddcplhhHpmcHpm(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(Mhh2(i1),MHpm2(i2),MHpm2(i3),dMhh2(i1,iv1)          & 
& ,dMHpm2(i2,iv1),dMHpm2(i3,iv1),dMhh2(i1,iv2),dMHpm2(i2,iv2),dMHpm2(i3,iv2)             & 
& ,ddMhh2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),ddMHpm2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 1
results1(9)=results1(9) + coeff*colorfactor*temp
results1_ti(9)=results1_ti(9) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(9).eq.results1(9)))  write(*,*) 'NaN at SSS C[hh, Hpm, conj[Hpm]]' 
! ---- hh,Sd,conj[Sd] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSdcSd(i1,i2,i3)
coup2 = cplhhSdcSd(i1,i3,i2)
Di_coup1 = dcplhhSdcSd(i1,i2,i3,iv1)
Dj_coup1 = dcplhhSdcSd(i1,i2,i3,iv2)
DDcoup1 = ddcplhhSdcSd(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(Mhh2(i1),MSd2(i2),MSd2(i3),dMhh2(i1,iv1)            & 
& ,dMSd2(i2,iv1),dMSd2(i3,iv1),dMhh2(i1,iv2),dMSd2(i2,iv2),dMSd2(i3,iv2),ddMhh2(i1,iv1,iv2)& 
& ,ddMSd2(i2,iv1,iv2),ddMSd2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 3
results1(10)=results1(10) + coeff*colorfactor*temp
results1_ti(10)=results1_ti(10) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(10).eq.results1(10)))  write(*,*) 'NaN at SSS C[hh, Sd, conj[Sd]]' 
! ---- hh,Se,conj[Se] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSecSe(i1,i2,i3)
coup2 = cplhhSecSe(i1,i3,i2)
Di_coup1 = dcplhhSecSe(i1,i2,i3,iv1)
Dj_coup1 = dcplhhSecSe(i1,i2,i3,iv2)
DDcoup1 = ddcplhhSecSe(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(Mhh2(i1),MSe2(i2),MSe2(i3),dMhh2(i1,iv1)            & 
& ,dMSe2(i2,iv1),dMSe2(i3,iv1),dMhh2(i1,iv2),dMSe2(i2,iv2),dMSe2(i3,iv2),ddMhh2(i1,iv1,iv2)& 
& ,ddMSe2(i2,iv1,iv2),ddMSe2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 1
results1(11)=results1(11) + coeff*colorfactor*temp
results1_ti(11)=results1_ti(11) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(11).eq.results1(11)))  write(*,*) 'NaN at SSS C[hh, Se, conj[Se]]' 
! ---- hh,Su,conj[Su] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSucSu(i1,i2,i3)
coup2 = cplhhSucSu(i1,i3,i2)
Di_coup1 = dcplhhSucSu(i1,i2,i3,iv1)
Dj_coup1 = dcplhhSucSu(i1,i2,i3,iv2)
DDcoup1 = ddcplhhSucSu(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(Mhh2(i1),MSu2(i2),MSu2(i3),dMhh2(i1,iv1)            & 
& ,dMSu2(i2,iv1),dMSu2(i3,iv1),dMhh2(i1,iv2),dMSu2(i2,iv2),dMSu2(i3,iv2),ddMhh2(i1,iv1,iv2)& 
& ,ddMSu2(i2,iv1,iv2),ddMSu2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 3
results1(12)=results1(12) + coeff*colorfactor*temp
results1_ti(12)=results1_ti(12) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(12).eq.results1(12)))  write(*,*) 'NaN at SSS C[hh, Su, conj[Su]]' 
! ---- Sd,conj[Hpm],conj[Su] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,6
coup1 = cplSdcHpmcSu(i1,i2,i3)
coup2 = cplHpmSucSd(i2,i3,i1)
Di_coup1 = dcplSdcHpmcSu(i1,i2,i3,iv1)
Dj_coup1 = dcplSdcHpmcSu(i1,i2,i3,iv2)
DDcoup1 = ddcplSdcHpmcSu(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MSd2(i1),MHpm2(i2),MSu2(i3),dMSd2(i1,iv1)           & 
& ,dMHpm2(i2,iv1),dMSu2(i3,iv1),dMSd2(i1,iv2),dMHpm2(i2,iv2),dMSu2(i3,iv2)               & 
& ,ddMSd2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),ddMSu2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 1._dp
colorfactor = 3
results1(13)=results1(13) + coeff*colorfactor*temp
results1_ti(13)=results1_ti(13) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(13).eq.results1(13)))  write(*,*) 'NaN at SSS C[Sd, conj[Hpm], conj[Su]]' 
! ---- Se,conj[Hpm],conj[Sv] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1 = cplSecHpmcSv(i1,i2,i3)
coup2 = cplHpmSvcSe(i2,i3,i1)
Di_coup1 = dcplSecHpmcSv(i1,i2,i3,iv1)
Dj_coup1 = dcplSecHpmcSv(i1,i2,i3,iv2)
DDcoup1 = ddcplSecHpmcSv(i1,i2,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MSe2(i1),MHpm2(i2),MSv2(i3),dMSe2(i1,iv1)           & 
& ,dMHpm2(i2,iv1),dMSv2(i3,iv1),dMSe2(i1,iv2),dMHpm2(i2,iv2),dMSv2(i3,iv2)               & 
& ,ddMSe2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),ddMSv2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'SSS   ',Q2,temp,temp_ti,temp_tj)
coeff = 1._dp
colorfactor = 1
results1(14)=results1(14) + coeff*colorfactor*temp
results1_ti(14)=results1_ti(14) + coeff*colorfactor*temp_ti
    End Do
  End Do
End Do
if (.not.(results1(14).eq.results1(14)))  write(*,*) 'NaN at SSS C[Se, conj[Hpm], conj[Sv]]' 

! ----- diagrams of type FFS, 22 ------ 

! ---- Ah,Cha,bar[Cha] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChaAhL(i3,i2,i1)
coup1R = cplcChaChaAhR(i3,i2,i1)
coup2L = cplcChaChaAhL(i2,i3,i1)
coup2R = cplcChaChaAhR(i2,i3,i1)
Di_coup1L = dcplcChaChaAhL(i3,i2,i1,iv1)
Di_coup1R = dcplcChaChaAhR(i3,i2,i1,iv1)
Dj_coup1L = dcplcChaChaAhL(i3,i2,i1,iv2)
Dj_coup1R = dcplcChaChaAhR(i3,i2,i1,iv2)
DDcoup1L = ddcplcChaChaAhL(i3,i2,i1,iv1,iv2)
DDcoup1R = ddcplcChaChaAhR(i3,i2,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MCha2(i3),MCha2(i2),MAh2(i1),dMCha2(i3,iv1)         & 
& ,dMCha2(i2,iv1),dMAh2(i1,iv1),dMCha2(i3,iv2),dMCha2(i2,iv2),dMAh2(i1,iv2)              & 
& ,ddMCha2(i3,iv1,iv2),ddMCha2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MCha2(i3),MCha2(i2),MAh2(i1),dMCha2(i3,iv1)         & 
& ,dMCha2(i2,iv1),dMAh2(i1,iv1),dMCha2(i3,iv2),dMCha2(i2,iv2),dMAh2(i1,iv2)              & 
& ,ddMCha2(i3,iv1,iv2),ddMCha2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(15)=results1(15) + coeff*colorfactor*temp
results1_ti(15)=results1_ti(15) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(15)=results1(15) + coeffbar*colorfactor*tempbar
results1_ti(15)=results1_ti(15) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(15).eq.results1(15)))  write(*,*) 'NaN at FFS C[Ah, Cha, bar[Cha]]' 
! ---- Ah,Chi,Chi ----
Do i1=1,3
 Do i2=1,5
    Do i3=1,5
coup1L = cplChiChiAhL(i2,i3,i1)
coup1R = cplChiChiAhR(i2,i3,i1)
coup2L = cplChiChiAhL(i2,i3,i1)
coup2R = cplChiChiAhR(i2,i3,i1)
Di_coup1L = dcplChiChiAhL(i2,i3,i1,iv1)
Di_coup1R = dcplChiChiAhR(i2,i3,i1,iv1)
Dj_coup1L = dcplChiChiAhL(i2,i3,i1,iv2)
Dj_coup1R = dcplChiChiAhR(i2,i3,i1,iv2)
DDcoup1L = ddcplChiChiAhL(i2,i3,i1,iv1,iv2)
DDcoup1R = ddcplChiChiAhR(i2,i3,i1,iv1,iv2)
coupx = abs(coup1L)**2
Di_coupx=Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) 
Dj_coupx=Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L)  
Call SecondDerivativeVeff_sunrise(MChi2(i3),MChi2(i2),MAh2(i1),dMChi2(i3,iv1)         & 
& ,dMChi2(i2,iv1),dMAh2(i1,iv1),dMChi2(i3,iv2),dMChi2(i2,iv2),dMAh2(i1,iv2)              & 
& ,ddMChi2(i3,iv1,iv2),ddMChi2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = Real(coup1L**2,dp) 
Di_coupxbar = Real(2*Di_coup1L*coup1L,dp) 
Dj_coupxbar = Real(2*Dj_coup1L*coup1L,dp) 
DDcoupxbar = Real(2*DDcoup1L*coup1L + 2*Di_coup1L*Dj_coup1L,dp) 
Call SecondDerivativeVeff_sunrise(MChi2(i3),MChi2(i2),MAh2(i1),dMChi2(i3,iv1)         & 
& ,dMChi2(i2,iv1),dMAh2(i1,iv1),dMChi2(i3,iv2),dMChi2(i2,iv2),dMAh2(i1,iv2)              & 
& ,ddMChi2(i3,iv1,iv2),ddMChi2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(16)=results1(16) + coeff*colorfactor*temp
results1_ti(16)=results1_ti(16) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(16)=results1(16) + coeffbar*colorfactor*tempbar
results1_ti(16)=results1_ti(16) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(16).eq.results1(16)))  write(*,*) 'NaN at FFS C[Ah, Chi, Chi]' 
! ---- Ah,Fd,bar[Fd] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdAhL(i3,i2,i1)
coup1R = cplcFdFdAhR(i3,i2,i1)
coup2L = cplcFdFdAhL(i2,i3,i1)
coup2R = cplcFdFdAhR(i2,i3,i1)
Di_coup1L = dcplcFdFdAhL(i3,i2,i1,iv1)
Di_coup1R = dcplcFdFdAhR(i3,i2,i1,iv1)
Dj_coup1L = dcplcFdFdAhL(i3,i2,i1,iv2)
Dj_coup1R = dcplcFdFdAhR(i3,i2,i1,iv2)
DDcoup1L = ddcplcFdFdAhL(i3,i2,i1,iv1,iv2)
DDcoup1R = ddcplcFdFdAhR(i3,i2,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i2),MAh2(i1),dMFd2(i3,iv1)            & 
& ,dMFd2(i2,iv1),dMAh2(i1,iv1),dMFd2(i3,iv2),dMFd2(i2,iv2),dMAh2(i1,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMFd2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i2),MAh2(i1),dMFd2(i3,iv1)            & 
& ,dMFd2(i2,iv1),dMAh2(i1,iv1),dMFd2(i3,iv2),dMFd2(i2,iv2),dMAh2(i1,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMFd2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 3
results1(17)=results1(17) + coeff*colorfactor*temp
results1_ti(17)=results1_ti(17) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(17)=results1(17) + coeffbar*colorfactor*tempbar
results1_ti(17)=results1_ti(17) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(17).eq.results1(17)))  write(*,*) 'NaN at FFS C[Ah, Fd, bar[Fd]]' 
! ---- Ah,Fe,bar[Fe] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFeAhL(i3,i2,i1)
coup1R = cplcFeFeAhR(i3,i2,i1)
coup2L = cplcFeFeAhL(i2,i3,i1)
coup2R = cplcFeFeAhR(i2,i3,i1)
Di_coup1L = dcplcFeFeAhL(i3,i2,i1,iv1)
Di_coup1R = dcplcFeFeAhR(i3,i2,i1,iv1)
Dj_coup1L = dcplcFeFeAhL(i3,i2,i1,iv2)
Dj_coup1R = dcplcFeFeAhR(i3,i2,i1,iv2)
DDcoup1L = ddcplcFeFeAhL(i3,i2,i1,iv1,iv2)
DDcoup1R = ddcplcFeFeAhR(i3,i2,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFe2(i3),MFe2(i2),MAh2(i1),dMFe2(i3,iv1)            & 
& ,dMFe2(i2,iv1),dMAh2(i1,iv1),dMFe2(i3,iv2),dMFe2(i2,iv2),dMAh2(i1,iv2),ddMFe2(i3,iv1,iv2)& 
& ,ddMFe2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFe2(i3),MFe2(i2),MAh2(i1),dMFe2(i3,iv1)            & 
& ,dMFe2(i2,iv1),dMAh2(i1,iv1),dMFe2(i3,iv2),dMFe2(i2,iv2),dMAh2(i1,iv2),ddMFe2(i3,iv1,iv2)& 
& ,ddMFe2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(18)=results1(18) + coeff*colorfactor*temp
results1_ti(18)=results1_ti(18) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(18)=results1(18) + coeffbar*colorfactor*tempbar
results1_ti(18)=results1_ti(18) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(18).eq.results1(18)))  write(*,*) 'NaN at FFS C[Ah, Fe, bar[Fe]]' 
! ---- Ah,Fu,bar[Fu] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuAhL(i3,i2,i1)
coup1R = cplcFuFuAhR(i3,i2,i1)
coup2L = cplcFuFuAhL(i2,i3,i1)
coup2R = cplcFuFuAhR(i2,i3,i1)
Di_coup1L = dcplcFuFuAhL(i3,i2,i1,iv1)
Di_coup1R = dcplcFuFuAhR(i3,i2,i1,iv1)
Dj_coup1L = dcplcFuFuAhL(i3,i2,i1,iv2)
Dj_coup1R = dcplcFuFuAhR(i3,i2,i1,iv2)
DDcoup1L = ddcplcFuFuAhL(i3,i2,i1,iv1,iv2)
DDcoup1R = ddcplcFuFuAhR(i3,i2,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i2),MAh2(i1),dMFu2(i3,iv1)            & 
& ,dMFu2(i2,iv1),dMAh2(i1,iv1),dMFu2(i3,iv2),dMFu2(i2,iv2),dMAh2(i1,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMFu2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i2),MAh2(i1),dMFu2(i3,iv1)            & 
& ,dMFu2(i2,iv1),dMAh2(i1,iv1),dMFu2(i3,iv2),dMFu2(i2,iv2),dMAh2(i1,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMFu2(i2,iv1,iv2),ddMAh2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 3
results1(19)=results1(19) + coeff*colorfactor*temp
results1_ti(19)=results1_ti(19) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(19)=results1(19) + coeffbar*colorfactor*tempbar
results1_ti(19)=results1_ti(19) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(19).eq.results1(19)))  write(*,*) 'NaN at FFS C[Ah, Fu, bar[Fu]]' 
! ---- Cha,hh,bar[Cha] ----
Do i1=1,2
 Do i2=1,3
    Do i3=1,2
coup1L = cplcChaChahhL(i3,i1,i2)
coup1R = cplcChaChahhR(i3,i1,i2)
coup2L = cplcChaChahhL(i1,i3,i2)
coup2R = cplcChaChahhR(i1,i3,i2)
Di_coup1L = dcplcChaChahhL(i3,i1,i2,iv1)
Di_coup1R = dcplcChaChahhR(i3,i1,i2,iv1)
Dj_coup1L = dcplcChaChahhL(i3,i1,i2,iv2)
Dj_coup1R = dcplcChaChahhR(i3,i1,i2,iv2)
DDcoup1L = ddcplcChaChahhL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcChaChahhR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MCha2(i3),MCha2(i1),Mhh2(i2),dMCha2(i3,iv1)         & 
& ,dMCha2(i1,iv1),dMhh2(i2,iv1),dMCha2(i3,iv2),dMCha2(i1,iv2),dMhh2(i2,iv2)              & 
& ,ddMCha2(i3,iv1,iv2),ddMCha2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MCha2(i3),MCha2(i1),Mhh2(i2),dMCha2(i3,iv1)         & 
& ,dMCha2(i1,iv1),dMhh2(i2,iv1),dMCha2(i3,iv2),dMCha2(i1,iv2),dMhh2(i2,iv2)              & 
& ,ddMCha2(i3,iv1,iv2),ddMCha2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(20)=results1(20) + coeff*colorfactor*temp
results1_ti(20)=results1_ti(20) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(20)=results1(20) + coeffbar*colorfactor*tempbar
results1_ti(20)=results1_ti(20) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(20).eq.results1(20)))  write(*,*) 'NaN at FFS C[Cha, hh, bar[Cha]]' 
! ---- Chi,Chi,hh ----
Do i1=1,5
 Do i2=1,5
    Do i3=1,3
coup1L = cplChiChihhL(i1,i2,i3)
coup1R = cplChiChihhR(i1,i2,i3)
coup2L = cplChiChihhL(i1,i2,i3)
coup2R = cplChiChihhR(i1,i2,i3)
Di_coup1L = dcplChiChihhL(i1,i2,i3,iv1)
Di_coup1R = dcplChiChihhR(i1,i2,i3,iv1)
Dj_coup1L = dcplChiChihhL(i1,i2,i3,iv2)
Dj_coup1R = dcplChiChihhR(i1,i2,i3,iv2)
DDcoup1L = ddcplChiChihhL(i1,i2,i3,iv1,iv2)
DDcoup1R = ddcplChiChihhR(i1,i2,i3,iv1,iv2)
coupx = abs(coup1L)**2
Di_coupx=Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) 
Dj_coupx=Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L)  
Call SecondDerivativeVeff_sunrise(MChi2(i2),MChi2(i1),Mhh2(i3),dMChi2(i2,iv1)         & 
& ,dMChi2(i1,iv1),dMhh2(i3,iv1),dMChi2(i2,iv2),dMChi2(i1,iv2),dMhh2(i3,iv2)              & 
& ,ddMChi2(i2,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMhh2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = Real(coup1L**2,dp) 
Di_coupxbar = Real(2*Di_coup1L*coup1L,dp) 
Dj_coupxbar = Real(2*Dj_coup1L*coup1L,dp) 
DDcoupxbar = Real(2*DDcoup1L*coup1L + 2*Di_coup1L*Dj_coup1L,dp) 
Call SecondDerivativeVeff_sunrise(MChi2(i2),MChi2(i1),Mhh2(i3),dMChi2(i2,iv1)         & 
& ,dMChi2(i1,iv1),dMhh2(i3,iv1),dMChi2(i2,iv2),dMChi2(i1,iv2),dMhh2(i3,iv2)              & 
& ,ddMChi2(i2,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMhh2(i3,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(21)=results1(21) + coeff*colorfactor*temp
results1_ti(21)=results1_ti(21) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(21)=results1(21) + coeffbar*colorfactor*tempbar
results1_ti(21)=results1_ti(21) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(21).eq.results1(21)))  write(*,*) 'NaN at FFS C[Chi, Chi, hh]' 
! ---- Chi,Hpm,bar[Cha] ----
Do i1=1,5
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChiHpmL(i3,i1,i2)
coup1R = cplcChaChiHpmR(i3,i1,i2)
coup2L = cplChiChacHpmL(i1,i3,i2)
coup2R = cplChiChacHpmR(i1,i3,i2)
Di_coup1L = dcplcChaChiHpmL(i3,i1,i2,iv1)
Di_coup1R = dcplcChaChiHpmR(i3,i1,i2,iv1)
Dj_coup1L = dcplcChaChiHpmL(i3,i1,i2,iv2)
Dj_coup1R = dcplcChaChiHpmR(i3,i1,i2,iv2)
DDcoup1L = ddcplcChaChiHpmL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcChaChiHpmR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MCha2(i3),MChi2(i1),MHpm2(i2),dMCha2(i3,iv1)        & 
& ,dMChi2(i1,iv1),dMHpm2(i2,iv1),dMCha2(i3,iv2),dMChi2(i1,iv2),dMHpm2(i2,iv2)            & 
& ,ddMCha2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MCha2(i3),MChi2(i1),MHpm2(i2),dMCha2(i3,iv1)        & 
& ,dMChi2(i1,iv1),dMHpm2(i2,iv1),dMCha2(i3,iv2),dMChi2(i1,iv2),dMHpm2(i2,iv2)            & 
& ,ddMCha2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 1
results1(22)=results1(22) + coeff*colorfactor*temp
results1_ti(22)=results1_ti(22) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(22)=results1(22) + coeffbar*colorfactor*tempbar
results1_ti(22)=results1_ti(22) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(22).eq.results1(22)))  write(*,*) 'NaN at FFS C[Chi, Hpm, bar[Cha]]' 
! ---- Chi,Sd,bar[Fd] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdChiSdL(i3,i1,i2)
coup1R = cplcFdChiSdR(i3,i1,i2)
coup2L = cplChiFdcSdL(i1,i3,i2)
coup2R = cplChiFdcSdR(i1,i3,i2)
Di_coup1L = dcplcFdChiSdL(i3,i1,i2,iv1)
Di_coup1R = dcplcFdChiSdR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFdChiSdL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFdChiSdR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFdChiSdL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFdChiSdR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MChi2(i1),MSd2(i2),dMFd2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSd2(i2,iv1),dMFd2(i3,iv2),dMChi2(i1,iv2),dMSd2(i2,iv2)               & 
& ,ddMFd2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MChi2(i1),MSd2(i2),dMFd2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSd2(i2,iv1),dMFd2(i3,iv2),dMChi2(i1,iv2),dMSd2(i2,iv2)               & 
& ,ddMFd2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 3
results1(23)=results1(23) + coeff*colorfactor*temp
results1_ti(23)=results1_ti(23) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(23)=results1(23) + coeffbar*colorfactor*tempbar
results1_ti(23)=results1_ti(23) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(23).eq.results1(23)))  write(*,*) 'NaN at FFS C[Chi, Sd, bar[Fd]]' 
! ---- Chi,Se,bar[Fe] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFeChiSeL(i3,i1,i2)
coup1R = cplcFeChiSeR(i3,i1,i2)
coup2L = cplChiFecSeL(i1,i3,i2)
coup2R = cplChiFecSeR(i1,i3,i2)
Di_coup1L = dcplcFeChiSeL(i3,i1,i2,iv1)
Di_coup1R = dcplcFeChiSeR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFeChiSeL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFeChiSeR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFeChiSeL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFeChiSeR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFe2(i3),MChi2(i1),MSe2(i2),dMFe2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSe2(i2,iv1),dMFe2(i3,iv2),dMChi2(i1,iv2),dMSe2(i2,iv2)               & 
& ,ddMFe2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFe2(i3),MChi2(i1),MSe2(i2),dMFe2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSe2(i2,iv1),dMFe2(i3,iv2),dMChi2(i1,iv2),dMSe2(i2,iv2)               & 
& ,ddMFe2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 1
results1(24)=results1(24) + coeff*colorfactor*temp
results1_ti(24)=results1_ti(24) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(24)=results1(24) + coeffbar*colorfactor*tempbar
results1_ti(24)=results1_ti(24) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(24).eq.results1(24)))  write(*,*) 'NaN at FFS C[Chi, Se, bar[Fe]]' 
! ---- Chi,Su,bar[Fu] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuChiSuL(i3,i1,i2)
coup1R = cplcFuChiSuR(i3,i1,i2)
coup2L = cplChiFucSuL(i1,i3,i2)
coup2R = cplChiFucSuR(i1,i3,i2)
Di_coup1L = dcplcFuChiSuL(i3,i1,i2,iv1)
Di_coup1R = dcplcFuChiSuR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFuChiSuL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFuChiSuR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFuChiSuL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFuChiSuR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MChi2(i1),MSu2(i2),dMFu2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSu2(i2,iv1),dMFu2(i3,iv2),dMChi2(i1,iv2),dMSu2(i2,iv2)               & 
& ,ddMFu2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MChi2(i1),MSu2(i2),dMFu2(i3,iv1)           & 
& ,dMChi2(i1,iv1),dMSu2(i2,iv1),dMFu2(i3,iv2),dMChi2(i1,iv2),dMSu2(i2,iv2)               & 
& ,ddMFu2(i3,iv1,iv2),ddMChi2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 3
results1(25)=results1(25) + coeff*colorfactor*temp
results1_ti(25)=results1_ti(25) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(25)=results1(25) + coeffbar*colorfactor*tempbar
results1_ti(25)=results1_ti(25) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(25).eq.results1(25)))  write(*,*) 'NaN at FFS C[Chi, Su, bar[Fu]]' 
! ---- Fd,hh,bar[Fd] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdhhL(i3,i1,i2)
coup1R = cplcFdFdhhR(i3,i1,i2)
coup2L = cplcFdFdhhL(i1,i3,i2)
coup2R = cplcFdFdhhR(i1,i3,i2)
Di_coup1L = dcplcFdFdhhL(i3,i1,i2,iv1)
Di_coup1R = dcplcFdFdhhR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFdFdhhL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFdFdhhR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFdFdhhL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFdFdhhR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),Mhh2(i2),dMFd2(i3,iv1)            & 
& ,dMFd2(i1,iv1),dMhh2(i2,iv1),dMFd2(i3,iv2),dMFd2(i1,iv2),dMhh2(i2,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMFd2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),Mhh2(i2),dMFd2(i3,iv1)            & 
& ,dMFd2(i1,iv1),dMhh2(i2,iv1),dMFd2(i3,iv2),dMFd2(i1,iv2),dMhh2(i2,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMFd2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 3
results1(26)=results1(26) + coeff*colorfactor*temp
results1_ti(26)=results1_ti(26) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(26)=results1(26) + coeffbar*colorfactor*tempbar
results1_ti(26)=results1_ti(26) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(26).eq.results1(26)))  write(*,*) 'NaN at FFS C[Fd, hh, bar[Fd]]' 
! ---- Fd,bar[Cha],conj[Su] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,6
coup1L = cplcChaFdcSuL(i2,i1,i3)
coup1R = cplcChaFdcSuR(i2,i1,i3)
coup2L = cplcFdChaSuL(i1,i2,i3)
coup2R = cplcFdChaSuR(i1,i2,i3)
Di_coup1L = dcplcChaFdcSuL(i2,i1,i3,iv1)
Di_coup1R = dcplcChaFdcSuR(i2,i1,i3,iv1)
Dj_coup1L = dcplcChaFdcSuL(i2,i1,i3,iv2)
Dj_coup1R = dcplcChaFdcSuR(i2,i1,i3,iv2)
DDcoup1L = ddcplcChaFdcSuL(i2,i1,i3,iv1,iv2)
DDcoup1R = ddcplcChaFdcSuR(i2,i1,i3,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MCha2(i2),MFd2(i1),MSu2(i3),dMCha2(i2,iv1)          & 
& ,dMFd2(i1,iv1),dMSu2(i3,iv1),dMCha2(i2,iv2),dMFd2(i1,iv2),dMSu2(i3,iv2),ddMCha2(i2,iv1,iv2)& 
& ,ddMFd2(i1,iv1,iv2),ddMSu2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MCha2(i2),MFd2(i1),MSu2(i3),dMCha2(i2,iv1)          & 
& ,dMFd2(i1,iv1),dMSu2(i3,iv1),dMCha2(i2,iv2),dMFd2(i1,iv2),dMSu2(i3,iv2),ddMCha2(i2,iv1,iv2)& 
& ,ddMFd2(i1,iv1,iv2),ddMSu2(i3,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 3
results1(27)=results1(27) + coeff*colorfactor*temp
results1_ti(27)=results1_ti(27) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(27)=results1(27) + coeffbar*colorfactor*tempbar
results1_ti(27)=results1_ti(27) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(27).eq.results1(27)))  write(*,*) 'NaN at FFS C[Fd, bar[Cha], conj[Su]]' 
! ---- Fe,hh,bar[Fe] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFehhL(i3,i1,i2)
coup1R = cplcFeFehhR(i3,i1,i2)
coup2L = cplcFeFehhL(i1,i3,i2)
coup2R = cplcFeFehhR(i1,i3,i2)
Di_coup1L = dcplcFeFehhL(i3,i1,i2,iv1)
Di_coup1R = dcplcFeFehhR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFeFehhL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFeFehhR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFeFehhL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFeFehhR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFe2(i3),MFe2(i1),Mhh2(i2),dMFe2(i3,iv1)            & 
& ,dMFe2(i1,iv1),dMhh2(i2,iv1),dMFe2(i3,iv2),dMFe2(i1,iv2),dMhh2(i2,iv2),ddMFe2(i3,iv1,iv2)& 
& ,ddMFe2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFe2(i3),MFe2(i1),Mhh2(i2),dMFe2(i3,iv1)            & 
& ,dMFe2(i1,iv1),dMhh2(i2,iv1),dMFe2(i3,iv2),dMFe2(i1,iv2),dMhh2(i2,iv2),ddMFe2(i3,iv1,iv2)& 
& ,ddMFe2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 1
results1(28)=results1(28) + coeff*colorfactor*temp
results1_ti(28)=results1_ti(28) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(28)=results1(28) + coeffbar*colorfactor*tempbar
results1_ti(28)=results1_ti(28) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(28).eq.results1(28)))  write(*,*) 'NaN at FFS C[Fe, hh, bar[Fe]]' 
! ---- Fe,bar[Cha],conj[Sv] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChaFecSvL(i2,i1,i3)
coup1R = cplcChaFecSvR(i2,i1,i3)
coup2L = cplcFeChaSvL(i1,i2,i3)
coup2R = cplcFeChaSvR(i1,i2,i3)
Di_coup1L = dcplcChaFecSvL(i2,i1,i3,iv1)
Di_coup1R = dcplcChaFecSvR(i2,i1,i3,iv1)
Dj_coup1L = dcplcChaFecSvL(i2,i1,i3,iv2)
Dj_coup1R = dcplcChaFecSvR(i2,i1,i3,iv2)
DDcoup1L = ddcplcChaFecSvL(i2,i1,i3,iv1,iv2)
DDcoup1R = ddcplcChaFecSvR(i2,i1,i3,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MCha2(i2),MFe2(i1),MSv2(i3),dMCha2(i2,iv1)          & 
& ,dMFe2(i1,iv1),dMSv2(i3,iv1),dMCha2(i2,iv2),dMFe2(i1,iv2),dMSv2(i3,iv2),ddMCha2(i2,iv1,iv2)& 
& ,ddMFe2(i1,iv1,iv2),ddMSv2(i3,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MCha2(i2),MFe2(i1),MSv2(i3),dMCha2(i2,iv1)          & 
& ,dMFe2(i1,iv1),dMSv2(i3,iv1),dMCha2(i2,iv2),dMFe2(i1,iv2),dMSv2(i3,iv2),ddMCha2(i2,iv1,iv2)& 
& ,ddMFe2(i1,iv1,iv2),ddMSv2(i3,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 1
results1(29)=results1(29) + coeff*colorfactor*temp
results1_ti(29)=results1_ti(29) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(29)=results1(29) + coeffbar*colorfactor*tempbar
results1_ti(29)=results1_ti(29) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(29).eq.results1(29)))  write(*,*) 'NaN at FFS C[Fe, bar[Cha], conj[Sv]]' 
! ---- Fu,hh,bar[Fu] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuhhL(i3,i1,i2)
coup1R = cplcFuFuhhR(i3,i1,i2)
coup2L = cplcFuFuhhL(i1,i3,i2)
coup2R = cplcFuFuhhR(i1,i3,i2)
Di_coup1L = dcplcFuFuhhL(i3,i1,i2,iv1)
Di_coup1R = dcplcFuFuhhR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFuFuhhL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFuFuhhR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFuFuhhL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFuFuhhR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),Mhh2(i2),dMFu2(i3,iv1)            & 
& ,dMFu2(i1,iv1),dMhh2(i2,iv1),dMFu2(i3,iv2),dMFu2(i1,iv2),dMhh2(i2,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMFu2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),Mhh2(i2),dMFu2(i3,iv1)            & 
& ,dMFu2(i1,iv1),dMhh2(i2,iv1),dMFu2(i3,iv2),dMFu2(i1,iv2),dMhh2(i2,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMFu2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 3
results1(30)=results1(30) + coeff*colorfactor*temp
results1_ti(30)=results1_ti(30) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(30)=results1(30) + coeffbar*colorfactor*tempbar
results1_ti(30)=results1_ti(30) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(30).eq.results1(30)))  write(*,*) 'NaN at FFS C[Fu, hh, bar[Fu]]' 
! ---- Fu,Hpm,bar[Fd] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFdFuHpmL(i3,i1,i2)
coup1R = cplcFdFuHpmR(i3,i1,i2)
coup2L = cplcFuFdcHpmL(i1,i3,i2)
coup2R = cplcFuFdcHpmR(i1,i3,i2)
Di_coup1L = dcplcFdFuHpmL(i3,i1,i2,iv1)
Di_coup1R = dcplcFdFuHpmR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFdFuHpmL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFdFuHpmR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFdFuHpmL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFdFuHpmR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFu2(i1),MHpm2(i2),dMFd2(i3,iv1)           & 
& ,dMFu2(i1,iv1),dMHpm2(i2,iv1),dMFd2(i3,iv2),dMFu2(i1,iv2),dMHpm2(i2,iv2)               & 
& ,ddMFd2(i3,iv1,iv2),ddMFu2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFu2(i1),MHpm2(i2),dMFd2(i3,iv1)           & 
& ,dMFu2(i1,iv1),dMHpm2(i2,iv1),dMFd2(i3,iv2),dMFu2(i1,iv2),dMHpm2(i2,iv2)               & 
& ,ddMFd2(i3,iv1,iv2),ddMFu2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 3
results1(31)=results1(31) + coeff*colorfactor*temp
results1_ti(31)=results1_ti(31) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(31)=results1(31) + coeffbar*colorfactor*tempbar
results1_ti(31)=results1_ti(31) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(31).eq.results1(31)))  write(*,*) 'NaN at FFS C[Fu, Hpm, bar[Fd]]' 
! ---- Fv,Hpm,bar[Fe] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFeFvHpmL(i3,i1,i2)
coup1R = cplcFeFvHpmR(i3,i1,i2)
coup2L = cplcFvFecHpmL(i1,i3,i2)
coup2R = cplcFvFecHpmR(i1,i3,i2)
Di_coup1L = dcplcFeFvHpmL(i3,i1,i2,iv1)
Di_coup1R = dcplcFeFvHpmR(i3,i1,i2,iv1)
Dj_coup1L = dcplcFeFvHpmL(i3,i1,i2,iv2)
Dj_coup1R = dcplcFeFvHpmR(i3,i1,i2,iv2)
DDcoup1L = ddcplcFeFvHpmL(i3,i1,i2,iv1,iv2)
DDcoup1R = ddcplcFeFvHpmR(i3,i1,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFe2(i3),0._dp,MHpm2(i2),dMFe2(i3,iv1)              & 
& ,ZeroC,dMHpm2(i2,iv1),dMFe2(i3,iv2),ZeroC,dMHpm2(i2,iv2),ddMFe2(i3,iv1,iv2)            & 
& ,ZeroC,ddMHpm2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFe2(i3),0._dp,MHpm2(i2),dMFe2(i3,iv1)              & 
& ,ZeroC,dMHpm2(i2,iv1),dMFe2(i3,iv2),ZeroC,dMHpm2(i2,iv2),ddMFe2(i3,iv1,iv2)            & 
& ,ZeroC,ddMHpm2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 1
results1(32)=results1(32) + coeff*colorfactor*temp
results1_ti(32)=results1_ti(32) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(32)=results1(32) + coeffbar*colorfactor*tempbar
results1_ti(32)=results1_ti(32) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(32).eq.results1(32)))  write(*,*) 'NaN at FFS C[Fv, Hpm, bar[Fe]]' 
! ---- Glu,Sd,bar[Fd] ----
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdGluSdL(i3,i2)
coup1R = cplcFdGluSdR(i3,i2)
coup2L = cplGluFdcSdL(i3,i2)
coup2R = cplGluFdcSdR(i3,i2)
Di_coup1L = dcplcFdGluSdL(i3,i2,iv1)
Di_coup1R = dcplcFdGluSdR(i3,i2,iv1)
Dj_coup1L = dcplcFdGluSdL(i3,i2,iv2)
Dj_coup1R = dcplcFdGluSdR(i3,i2,iv2)
DDcoup1L = ddcplcFdGluSdL(i3,i2,iv1,iv2)
DDcoup1R = ddcplcFdGluSdR(i3,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MGlu2,MSd2(i2),dMFd2(i3,iv1)               & 
& ,dMGlu2(1,iv1),dMSd2(i2,iv1),dMFd2(i3,iv2),dMGlu2(1,iv2),dMSd2(i2,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMGlu2(1,iv1,iv2),ddMSd2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MGlu2,MSd2(i2),dMFd2(i3,iv1)               & 
& ,dMGlu2(1,iv1),dMSd2(i2,iv1),dMFd2(i3,iv2),dMGlu2(1,iv2),dMSd2(i2,iv2),ddMFd2(i3,iv1,iv2)& 
& ,ddMGlu2(1,iv1,iv2),ddMSd2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 4
results1(33)=results1(33) + coeff*colorfactor*temp
results1_ti(33)=results1_ti(33) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(33)=results1(33) + coeffbar*colorfactor*tempbar
results1_ti(33)=results1_ti(33) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
if (.not.(results1(33).eq.results1(33)))  write(*,*) 'NaN at FFS C[Glu, Sd, bar[Fd]]' 
! ---- Glu,Su,bar[Fu] ----
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuGluSuL(i3,i2)
coup1R = cplcFuGluSuR(i3,i2)
coup2L = cplGluFucSuL(i3,i2)
coup2R = cplGluFucSuR(i3,i2)
Di_coup1L = dcplcFuGluSuL(i3,i2,iv1)
Di_coup1R = dcplcFuGluSuR(i3,i2,iv1)
Dj_coup1L = dcplcFuGluSuL(i3,i2,iv2)
Dj_coup1R = dcplcFuGluSuR(i3,i2,iv2)
DDcoup1L = ddcplcFuGluSuL(i3,i2,iv1,iv2)
DDcoup1R = ddcplcFuGluSuR(i3,i2,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MGlu2,MSu2(i2),dMFu2(i3,iv1)               & 
& ,dMGlu2(1,iv1),dMSu2(i2,iv1),dMFu2(i3,iv2),dMGlu2(1,iv2),dMSu2(i2,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMGlu2(1,iv1,iv2),ddMSu2(i2,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MGlu2,MSu2(i2),dMFu2(i3,iv1)               & 
& ,dMGlu2(1,iv1),dMSu2(i2,iv1),dMFu2(i3,iv2),dMGlu2(1,iv2),dMSu2(i2,iv2),ddMFu2(i3,iv1,iv2)& 
& ,ddMGlu2(1,iv1,iv2),ddMSu2(i2,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 4
results1(34)=results1(34) + coeff*colorfactor*temp
results1_ti(34)=results1_ti(34) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(34)=results1(34) + coeffbar*colorfactor*tempbar
results1_ti(34)=results1_ti(34) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
if (.not.(results1(34).eq.results1(34)))  write(*,*) 'NaN at FFS C[Glu, Su, bar[Fu]]' 
! ---- Sd,bar[Cha],bar[Fu] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFuSdL(i2,i3,i1)
coup1R = cplcChacFuSdR(i2,i3,i1)
coup2L = cplChaFucSdL(i2,i3,i1)
coup2R = cplChaFucSdR(i2,i3,i1)
Di_coup1L = dcplcChacFuSdL(i2,i3,i1,iv1)
Di_coup1R = dcplcChacFuSdR(i2,i3,i1,iv1)
Dj_coup1L = dcplcChacFuSdL(i2,i3,i1,iv2)
Dj_coup1R = dcplcChacFuSdR(i2,i3,i1,iv2)
DDcoup1L = ddcplcChacFuSdL(i2,i3,i1,iv1,iv2)
DDcoup1R = ddcplcChacFuSdR(i2,i3,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MCha2(i2),MSd2(i1),dMFu2(i3,iv1)           & 
& ,dMCha2(i2,iv1),dMSd2(i1,iv1),dMFu2(i3,iv2),dMCha2(i2,iv2),dMSd2(i1,iv2)               & 
& ,ddMFu2(i3,iv1,iv2),ddMCha2(i2,iv1,iv2),ddMSd2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MCha2(i2),MSd2(i1),dMFu2(i3,iv1)           & 
& ,dMCha2(i2,iv1),dMSd2(i1,iv1),dMFu2(i3,iv2),dMCha2(i2,iv2),dMSd2(i1,iv2)               & 
& ,ddMFu2(i3,iv1,iv2),ddMCha2(i2,iv1,iv2),ddMSd2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 3
results1(35)=results1(35) + coeff*colorfactor*temp
results1_ti(35)=results1_ti(35) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(35)=results1(35) + coeffbar*colorfactor*tempbar
results1_ti(35)=results1_ti(35) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(35).eq.results1(35)))  write(*,*) 'NaN at FFS C[Sd, bar[Cha], bar[Fu]]' 
! ---- Se,bar[Cha],bar[Fv] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFvSeL(i2,i3,i1)
coup1R = cplcChacFvSeR(i2,i3,i1)
coup2L = cplChaFvcSeL(i2,i3,i1)
coup2R = cplChaFvcSeR(i2,i3,i1)
Di_coup1L = dcplcChacFvSeL(i2,i3,i1,iv1)
Di_coup1R = dcplcChacFvSeR(i2,i3,i1,iv1)
Dj_coup1L = dcplcChacFvSeL(i2,i3,i1,iv2)
Dj_coup1R = dcplcChacFvSeR(i2,i3,i1,iv2)
DDcoup1L = ddcplcChacFvSeL(i2,i3,i1,iv1,iv2)
DDcoup1R = ddcplcChacFvSeR(i2,i3,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(0._dp,MCha2(i2),MSe2(i1),ZeroC,dMCha2(i2,iv1)       & 
& ,dMSe2(i1,iv1),ZeroC,dMCha2(i2,iv2),dMSe2(i1,iv2),ZeroC,ddMCha2(i2,iv1,iv2)            & 
& ,ddMSe2(i1,iv1,iv2),coupx,Di_coupx,Dj_coupx,DDcoupx,'FFS   ',Q2,temp,temp_ti,temp_tj)
coupxbar = 2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = 2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = 2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = 2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(0._dp,MCha2(i2),MSe2(i1),ZeroC,dMCha2(i2,iv1)       & 
& ,dMSe2(i1,iv1),ZeroC,dMCha2(i2,iv2),dMSe2(i1,iv2),ZeroC,ddMCha2(i2,iv1,iv2)            & 
& ,ddMSe2(i1,iv1,iv2),coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFSbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 1._dp
colorfactor = 1
results1(36)=results1(36) + coeff*colorfactor*temp
results1_ti(36)=results1_ti(36) + coeff*colorfactor*temp_ti
coeffbar = 1._dp
results1(36)=results1(36) + coeffbar*colorfactor*tempbar
results1_ti(36)=results1_ti(36) + coeffbar*colorfactor*tempbar_ti
    End Do
  End Do
End Do
if (.not.(results1(36).eq.results1(36)))  write(*,*) 'NaN at FFS C[Se, bar[Cha], bar[Fv]]' 

! ----- diagrams of type SSV, 2 ------ 

! ---- Sd,VG,conj[Sd] ----
Do i1=1,6
    Do i3=1,6
coup1 = cplSdcSdVG(i1,i3)
coup2 = cplSdcSdVG(i3,i1)
Di_coup1 = dcplSdcSdVG(i1,i3,iv1)
Dj_coup1 = dcplSdcSdVG(i1,i3,iv2)
DDcoup1 = ddcplSdcSdVG(i1,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MSd2(i3),MSd2(i1),0._dp,dMSd2(i3,iv1)               & 
& ,dMSd2(i1,iv1),ZeroC,dMSd2(i3,iv2),dMSd2(i1,iv2),ZeroC,ddMSd2(i3,iv1,iv2)              & 
& ,ddMSd2(i1,iv1,iv2),ZeroC,coupx,Di_coupx,Dj_coupx,DDcoupx,'SSV   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 4
results1(37)=results1(37) + coeff*colorfactor*temp
results1_ti(37)=results1_ti(37) + coeff*colorfactor*temp_ti
    End Do
End Do
if (.not.(results1(37).eq.results1(37)))  write(*,*) 'NaN at SSV C[Sd, VG, conj[Sd]]' 
! ---- Su,VG,conj[Su] ----
Do i1=1,6
    Do i3=1,6
coup1 = cplSucSuVG(i1,i3)
coup2 = cplSucSuVG(i3,i1)
Di_coup1 = dcplSucSuVG(i1,i3,iv1)
Dj_coup1 = dcplSucSuVG(i1,i3,iv2)
DDcoup1 = ddcplSucSuVG(i1,i3,iv1,iv2)
coupx=abs(coup1)**2 
Di_coupx=Di_coup1*conjg(coup1)+coup1*conjg(Di_coup1) 
Dj_coupx=Dj_coup1*conjg(coup1)+coup1*conjg(Dj_coup1) 
DDcoupx = DDcoup1*conjg(coup1)+coup1*conjg(DDcoup1) & 
& + Di_coup1*conjg(Dj_coup1)+Dj_coup1*conjg(Di_coup1)  
Call SecondDerivativeVeff_sunrise(MSu2(i3),MSu2(i1),0._dp,dMSu2(i3,iv1)               & 
& ,dMSu2(i1,iv1),ZeroC,dMSu2(i3,iv2),dMSu2(i1,iv2),ZeroC,ddMSu2(i3,iv1,iv2)              & 
& ,ddMSu2(i1,iv1,iv2),ZeroC,coupx,Di_coupx,Dj_coupx,DDcoupx,'SSV   ',Q2,temp,temp_ti,temp_tj)
coeff = 0.5_dp
colorfactor = 4
results1(38)=results1(38) + coeff*colorfactor*temp
results1_ti(38)=results1_ti(38) + coeff*colorfactor*temp_ti
    End Do
End Do
if (.not.(results1(38).eq.results1(38)))  write(*,*) 'NaN at SSV C[Su, VG, conj[Su]]' 

! ----- diagrams of type FFV, 3 ------ 

! ---- Fd,VG,bar[Fd] ----
Do i1=1,3
    Do i3=1,3
coup1L = cplcFdFdVGL(i3,i1)
coup1R = cplcFdFdVGR(i3,i1)
coup2L = cplcFdFdVGL(i1,i3)
coup2R = cplcFdFdVGR(i1,i3)
Di_coup1L = dcplcFdFdVGL(i3,i1,iv1)
Di_coup1R = dcplcFdFdVGR(i3,i1,iv1)
Dj_coup1L = dcplcFdFdVGL(i3,i1,iv2)
Dj_coup1R = dcplcFdFdVGR(i3,i1,iv2)
DDcoup1L = ddcplcFdFdVGL(i3,i1,iv1,iv2)
DDcoup1R = ddcplcFdFdVGR(i3,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),0._dp,dMFd2(i3,iv1)               & 
& ,dMFd2(i1,iv1),ZeroC,dMFd2(i3,iv2),dMFd2(i1,iv2),ZeroC,ddMFd2(i3,iv1,iv2)              & 
& ,ddMFd2(i1,iv1,iv2),ZeroC,coupx,Di_coupx,Dj_coupx,DDcoupx,'FFV   ',Q2,temp,temp_ti,temp_tj)
coupxbar = -2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = -2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = -2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = -2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),0._dp,dMFd2(i3,iv1)               & 
& ,dMFd2(i1,iv1),ZeroC,dMFd2(i3,iv2),dMFd2(i1,iv2),ZeroC,ddMFd2(i3,iv1,iv2)              & 
& ,ddMFd2(i1,iv1,iv2),ZeroC,coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFVbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 4
results1(39)=results1(39) + coeff*colorfactor*temp
results1_ti(39)=results1_ti(39) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(39)=results1(39) + coeffbar*colorfactor*tempbar
results1_ti(39)=results1_ti(39) + coeffbar*colorfactor*tempbar_ti
    End Do
End Do
if (.not.(results1(39).eq.results1(39)))  write(*,*) 'NaN at FFV C[Fd, VG, bar[Fd]]' 
! ---- Fu,VG,bar[Fu] ----
Do i1=1,3
    Do i3=1,3
coup1L = cplcFuFuVGL(i3,i1)
coup1R = cplcFuFuVGR(i3,i1)
coup2L = cplcFuFuVGL(i1,i3)
coup2R = cplcFuFuVGR(i1,i3)
Di_coup1L = dcplcFuFuVGL(i3,i1,iv1)
Di_coup1R = dcplcFuFuVGR(i3,i1,iv1)
Dj_coup1L = dcplcFuFuVGL(i3,i1,iv2)
Dj_coup1R = dcplcFuFuVGR(i3,i1,iv2)
DDcoup1L = ddcplcFuFuVGL(i3,i1,iv1,iv2)
DDcoup1R = ddcplcFuFuVGR(i3,i1,iv1,iv2)
coupx = (abs(coup1L)**2 + abs(coup1R)**2) 
Di_coupx = Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) &
& + Di_coup1R*conjg(coup1R)+coup1R*conjg(Di_coup1R) 
Dj_coupx = Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) &
& + Dj_coup1R*conjg(coup1R)+coup1R*conjg(Dj_coup1R) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L) & 
& + DDcoup1R*conjg(coup1R)+coup1R*conjg(DDcoup1R) & 
& + Di_coup1R*conjg(Dj_coup1R)+Dj_coup1R*conjg(Di_coup1R)  
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),0._dp,dMFu2(i3,iv1)               & 
& ,dMFu2(i1,iv1),ZeroC,dMFu2(i3,iv2),dMFu2(i1,iv2),ZeroC,ddMFu2(i3,iv1,iv2)              & 
& ,ddMFu2(i1,iv1,iv2),ZeroC,coupx,Di_coupx,Dj_coupx,DDcoupx,'FFV   ',Q2,temp,temp_ti,temp_tj)
coupxbar = -2*Real(coup1L*conjg(coup1R),dp) 
Di_coupxbar = -2*Real(Di_coup1L*conjg(coup1R)+coup1L*conjg(Di_coup1R),dp) 
Dj_coupxbar = -2*Real(Dj_coup1L*conjg(coup1R)+coup1L*conjg(Dj_coup1R),dp) 
DDcoupxbar = -2*Real(DDcoup1L*conjg(coup1R)+coup1L*conjg(DDcoup1R) &  
&          + Di_coup1L*conjg(Dj_coup1R)+Dj_coup1L*conjg(Di_coup1R)  ,dp) 
Call SecondDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),0._dp,dMFu2(i3,iv1)               & 
& ,dMFu2(i1,iv1),ZeroC,dMFu2(i3,iv2),dMFu2(i1,iv2),ZeroC,ddMFu2(i3,iv1,iv2)              & 
& ,ddMFu2(i1,iv1,iv2),ZeroC,coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFVbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 4
results1(40)=results1(40) + coeff*colorfactor*temp
results1_ti(40)=results1_ti(40) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(40)=results1(40) + coeffbar*colorfactor*tempbar
results1_ti(40)=results1_ti(40) + coeffbar*colorfactor*tempbar_ti
    End Do
End Do
if (.not.(results1(40).eq.results1(40)))  write(*,*) 'NaN at FFV C[Fu, VG, bar[Fu]]' 
! ---- Glu,Glu,VG ----
coup1L = cplGluGluVGL
coup1R = cplGluGluVGR
coup2L = cplGluGluVGL
coup2R = cplGluGluVGR
Di_coup1L = dcplGluGluVGL(iv1)
Di_coup1R = dcplGluGluVGR(iv1)
Dj_coup1L = dcplGluGluVGL(iv2)
Dj_coup1R = dcplGluGluVGR(iv2)
DDcoup1L = ddcplGluGluVGL(iv1,iv2)
DDcoup1R = ddcplGluGluVGR(iv1,iv2)
coupx = abs(coup1L)**2
Di_coupx=Di_coup1L*conjg(coup1L)+coup1L*conjg(Di_coup1L) 
Dj_coupx=Dj_coup1L*conjg(coup1L)+coup1L*conjg(Dj_coup1L) 
DDcoupx = DDcoup1L*conjg(coup1L)+coup1L*conjg(DDcoup1L) & 
& + Di_coup1L*conjg(Dj_coup1L)+Dj_coup1L*conjg(Di_coup1L)  
Call SecondDerivativeVeff_sunrise(MGlu2,MGlu2,0._dp,dMGlu2(1,iv1),dMGlu2(1,iv1)       & 
& ,ZeroC,dMGlu2(1,iv2),dMGlu2(1,iv2),ZeroC,ddMGlu2(1,iv1,iv2),ddMGlu2(1,iv1,iv2)         & 
& ,ZeroC,coupx,Di_coupx,Dj_coupx,DDcoupx,'FFV   ',Q2,temp,temp_ti,temp_tj)
coupxbar = Real(coup1L**2,dp) 
Di_coupxbar = Real(2*Di_coup1L*coup1L,dp) 
Dj_coupxbar = Real(2*Dj_coup1L*coup1L,dp) 
DDcoupxbar = Real(2*DDcoup1L*coup1L + 2*Di_coup1L*Dj_coup1L,dp) 
Call SecondDerivativeVeff_sunrise(MGlu2,MGlu2,0._dp,dMGlu2(1,iv1),dMGlu2(1,iv1)       & 
& ,ZeroC,dMGlu2(1,iv2),dMGlu2(1,iv2),ZeroC,ddMGlu2(1,iv1,iv2),ddMGlu2(1,iv1,iv2)         & 
& ,ZeroC,coupxbar,Di_coupxbar,Dj_coupxbar,DDcoupxbar,'FFVbar',Q2,tempbar,tempbar_ti,tempbar_tj)
coeff = 0.5_dp
colorfactor = 24
results1(41)=results1(41) + coeff*colorfactor*temp
results1_ti(41)=results1_ti(41) + coeff*colorfactor*temp_ti
coeffbar = 0.5_dp
results1(41)=results1(41) + coeffbar*colorfactor*tempbar
results1_ti(41)=results1_ti(41) + coeffbar*colorfactor*tempbar_ti
if (.not.(results1(41).eq.results1(41)))  write(*,*) 'NaN at FFV C[Glu, Glu, VG]' 

! ----- diagrams of type VVV, 1 ------ 

! ---- VG,VG,VG ----
coup1 = cplVGVGVG
coup2 = cplVGVGVG
Di_coup1 = dcplVGVGVG(iv1)
Dj_coup1 = dcplVGVGVG(iv2)
DDcoup1 = ddcplVGVGVG(iv1,iv2)
coeff = 0.000
colorfactor = 24
results1(42)=results1(42) + coeff*colorfactor*temp
results1_ti(42)=results1_ti(42) + coeff*colorfactor*temp_ti
if (.not.(results1(42).eq.results1(42)))  write(*,*) 'NaN at VVV C[VG, VG, VG]' 
! ----- Topology2: diagrams w. 2 Particles and 1 Vertex


! ----- diagrams of type SS, 22 ------ 

! ---- Ah,Ah ----
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhAhAh(i1,i1,i2,i2)
Di_coup1 = dcplAhAhAhAh(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhAhAh(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhAhAh(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),MAh2(i2),dMAh2(i1,iv1),dMAh2(i2,iv1)         & 
& ,dMAh2(i1,iv2),dMAh2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMAh2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp/8._dp)
results2(1)=results2(1) + coeff*temp
results2_ti(1)=results2_ti(1) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(1).eq.results2(1)))  write(*,*) 'NaN at SS C[Ah, Ah, Ah, Ah]' 
! ---- Ah,hh ----
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhhhhh(i1,i1,i2,i2)
Di_coup1 = dcplAhAhhhhh(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhhhhh(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhhhhh(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),Mhh2(i2),dMAh2(i1,iv1),dMhh2(i2,iv1)         & 
& ,dMAh2(i1,iv2),dMhh2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.25_dp)
results2(2)=results2(2) + coeff*temp
results2_ti(2)=results2_ti(2) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(2).eq.results2(2)))  write(*,*) 'NaN at SS C[Ah, Ah, hh, hh]' 
! ---- Ah,Hpm ----
Do i1=1,3
 Do i2=1,2
coup1 = cplAhAhHpmcHpm(i1,i1,i2,i2)
Di_coup1 = dcplAhAhHpmcHpm(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhHpmcHpm(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhHpmcHpm(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),MHpm2(i2),dMAh2(i1,iv1),dMHpm2(i2,iv1)       & 
& ,dMAh2(i1,iv2),dMHpm2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(3)=results2(3) + coeff*temp
results2_ti(3)=results2_ti(3) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(3).eq.results2(3)))  write(*,*) 'NaN at SS C[Ah, Ah, Hpm, conj[Hpm]]' 
! ---- Ah,Sd ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSdcSd(i1,i1,i2,i2)
Di_coup1 = dcplAhAhSdcSd(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhSdcSd(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhSdcSd(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),MSd2(i2),dMAh2(i1,iv1),dMSd2(i2,iv1)         & 
& ,dMAh2(i1,iv2),dMSd2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(4)=results2(4) + coeff*temp
results2_ti(4)=results2_ti(4) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(4).eq.results2(4)))  write(*,*) 'NaN at SS C[Ah, Ah, Sd, conj[Sd]]' 
! ---- Ah,Se ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSecSe(i1,i1,i2,i2)
Di_coup1 = dcplAhAhSecSe(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhSecSe(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhSecSe(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),MSe2(i2),dMAh2(i1,iv1),dMSe2(i2,iv1)         & 
& ,dMAh2(i1,iv2),dMSe2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(5)=results2(5) + coeff*temp
results2_ti(5)=results2_ti(5) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(5).eq.results2(5)))  write(*,*) 'NaN at SS C[Ah, Ah, Se, conj[Se]]' 
! ---- Ah,Su ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSucSu(i1,i1,i2,i2)
Di_coup1 = dcplAhAhSucSu(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplAhAhSucSu(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplAhAhSucSu(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MAh2(i1),MSu2(i2),dMAh2(i1,iv1),dMSu2(i2,iv1)         & 
& ,dMAh2(i1,iv2),dMSu2(i2,iv2),ddMAh2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(6)=results2(6) + coeff*temp
results2_ti(6)=results2_ti(6) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(6).eq.results2(6)))  write(*,*) 'NaN at SS C[Ah, Ah, Su, conj[Su]]' 
! ---- hh,hh ----
Do i1=1,3
 Do i2=1,3
coup1 = cplhhhhhhhh(i1,i1,i2,i2)
Di_coup1 = dcplhhhhhhhh(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplhhhhhhhh(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplhhhhhhhh(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(Mhh2(i1),Mhh2(i2),dMhh2(i1,iv1),dMhh2(i2,iv1)         & 
& ,dMhh2(i1,iv2),dMhh2(i2,iv2),ddMhh2(i1,iv1,iv2),ddMhh2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp/8._dp)
results2(7)=results2(7) + coeff*temp
results2_ti(7)=results2_ti(7) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(7).eq.results2(7)))  write(*,*) 'NaN at SS C[hh, hh, hh, hh]' 
! ---- hh,Hpm ----
Do i1=1,3
 Do i2=1,2
coup1 = cplhhhhHpmcHpm(i1,i1,i2,i2)
Di_coup1 = dcplhhhhHpmcHpm(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplhhhhHpmcHpm(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplhhhhHpmcHpm(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(Mhh2(i1),MHpm2(i2),dMhh2(i1,iv1),dMHpm2(i2,iv1)       & 
& ,dMhh2(i1,iv2),dMHpm2(i2,iv2),ddMhh2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(8)=results2(8) + coeff*temp
results2_ti(8)=results2_ti(8) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(8).eq.results2(8)))  write(*,*) 'NaN at SS C[hh, hh, Hpm, conj[Hpm]]' 
! ---- hh,Sd ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSdcSd(i1,i1,i2,i2)
Di_coup1 = dcplhhhhSdcSd(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplhhhhSdcSd(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplhhhhSdcSd(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(Mhh2(i1),MSd2(i2),dMhh2(i1,iv1),dMSd2(i2,iv1)         & 
& ,dMhh2(i1,iv2),dMSd2(i2,iv2),ddMhh2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(9)=results2(9) + coeff*temp
results2_ti(9)=results2_ti(9) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(9).eq.results2(9)))  write(*,*) 'NaN at SS C[hh, hh, Sd, conj[Sd]]' 
! ---- hh,Se ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSecSe(i1,i1,i2,i2)
Di_coup1 = dcplhhhhSecSe(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplhhhhSecSe(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplhhhhSecSe(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(Mhh2(i1),MSe2(i2),dMhh2(i1,iv1),dMSe2(i2,iv1)         & 
& ,dMhh2(i1,iv2),dMSe2(i2,iv2),ddMhh2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(10)=results2(10) + coeff*temp
results2_ti(10)=results2_ti(10) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(10).eq.results2(10)))  write(*,*) 'NaN at SS C[hh, hh, Se, conj[Se]]' 
! ---- hh,Su ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSucSu(i1,i1,i2,i2)
Di_coup1 = dcplhhhhSucSu(i1,i1,i2,i2,iv1)
Dj_coup1 = dcplhhhhSucSu(i1,i1,i2,i2,iv2)
DDcoup1 = ddcplhhhhSucSu(i1,i1,i2,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(Mhh2(i1),MSu2(i2),dMhh2(i1,iv1),dMSu2(i2,iv1)         & 
& ,dMhh2(i1,iv2),dMSu2(i2,iv2),ddMhh2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(11)=results2(11) + coeff*temp
results2_ti(11)=results2_ti(11) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(11).eq.results2(11)))  write(*,*) 'NaN at SS C[hh, hh, Su, conj[Su]]' 
! ---- Hpm,Hpm ----
Do i1=1,2
 Do i2=1,2
coup1 = cplHpmHpmcHpmcHpm(i1,i2,i1,i2)
Di_coup1 = dcplHpmHpmcHpmcHpm(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplHpmHpmcHpmcHpm(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplHpmHpmcHpmcHpm(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MHpm2(i1),MHpm2(i2),dMHpm2(i1,iv1),dMHpm2(i2,iv1)     & 
& ,dMHpm2(i1,iv2),dMHpm2(i2,iv2),ddMHpm2(i1,iv1,iv2),ddMHpm2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(12)=results2(12) + coeff*temp
results2_ti(12)=results2_ti(12) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(12).eq.results2(12)))  write(*,*) 'NaN at SS C[Hpm, Hpm, conj[Hpm], conj[Hpm]]' 
! ---- Hpm,Sd ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSdcHpmcSd(i1,i2,i1,i2)
Di_coup1 = dcplHpmSdcHpmcSd(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplHpmSdcHpmcSd(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplHpmSdcHpmcSd(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MHpm2(i1),MSd2(i2),dMHpm2(i1,iv1),dMSd2(i2,iv1)       & 
& ,dMHpm2(i1,iv2),dMSd2(i2,iv2),ddMHpm2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(13)=results2(13) + coeff*temp
results2_ti(13)=results2_ti(13) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(13).eq.results2(13)))  write(*,*) 'NaN at SS C[Hpm, Sd, conj[Hpm], conj[Sd]]' 
! ---- Hpm,Se ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSecHpmcSe(i1,i2,i1,i2)
Di_coup1 = dcplHpmSecHpmcSe(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplHpmSecHpmcSe(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplHpmSecHpmcSe(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MHpm2(i1),MSe2(i2),dMHpm2(i1,iv1),dMSe2(i2,iv1)       & 
& ,dMHpm2(i1,iv2),dMSe2(i2,iv2),ddMHpm2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(14)=results2(14) + coeff*temp
results2_ti(14)=results2_ti(14) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(14).eq.results2(14)))  write(*,*) 'NaN at SS C[Hpm, Se, conj[Hpm], conj[Se]]' 
! ---- Hpm,Su ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSucHpmcSu(i1,i2,i1,i2)
Di_coup1 = dcplHpmSucHpmcSu(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplHpmSucHpmcSu(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplHpmSucHpmcSu(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MHpm2(i1),MSu2(i2),dMHpm2(i1,iv1),dMSu2(i2,iv1)       & 
& ,dMHpm2(i1,iv2),dMSu2(i2,iv2),ddMHpm2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(15)=results2(15) + coeff*temp
results2_ti(15)=results2_ti(15) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(15).eq.results2(15)))  write(*,*) 'NaN at SS C[Hpm, Su, conj[Hpm], conj[Su]]' 
! ---- Hpm,Sv ----
Do i1=1,2
 Do i2=1,3
coup1 = cplHpmSvcHpmcSv(i1,i2,i1,i2)
Di_coup1 = dcplHpmSvcHpmcSv(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplHpmSvcHpmcSv(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplHpmSvcHpmcSv(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MHpm2(i1),MSv2(i2),dMHpm2(i1,iv1),dMSv2(i2,iv1)       & 
& ,dMHpm2(i1,iv2),dMSv2(i2,iv2),ddMHpm2(i1,iv1,iv2),ddMSv2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(16)=results2(16) + coeff*temp
results2_ti(16)=results2_ti(16) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(16).eq.results2(16)))  write(*,*) 'NaN at SS C[Hpm, Sv, conj[Hpm], conj[Sv]]' 
! ---- Sd,Sd ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSdcSdcSd(i1,i2,i1,i2)
Di_coup1 = dcplSdSdcSdcSd(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSdSdcSdcSd(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSdSdcSdcSd(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSd2(i1),MSd2(i2),dMSd2(i1,iv1),dMSd2(i2,iv1)         & 
& ,dMSd2(i1,iv2),dMSd2(i2,iv2),ddMSd2(i1,iv1,iv2),ddMSd2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(17)=results2(17) + coeff*temp
results2_ti(17)=results2_ti(17) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(17).eq.results2(17)))  write(*,*) 'NaN at SS C[Sd, Sd, conj[Sd], conj[Sd]]' 
! ---- Sd,Se ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSecSdcSe(i1,i2,i1,i2)
Di_coup1 = dcplSdSecSdcSe(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSdSecSdcSe(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSdSecSdcSe(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSd2(i1),MSe2(i2),dMSd2(i1,iv1),dMSe2(i2,iv1)         & 
& ,dMSd2(i1,iv2),dMSe2(i2,iv2),ddMSd2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(18)=results2(18) + coeff*temp
results2_ti(18)=results2_ti(18) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(18).eq.results2(18)))  write(*,*) 'NaN at SS C[Sd, Se, conj[Sd], conj[Se]]' 
! ---- Sd,Su ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSucSdcSu(i1,i2,i1,i2)
Di_coup1 = dcplSdSucSdcSu(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSdSucSdcSu(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSdSucSdcSu(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSd2(i1),MSu2(i2),dMSd2(i1,iv1),dMSu2(i2,iv1)         & 
& ,dMSd2(i1,iv2),dMSu2(i2,iv2),ddMSd2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(19)=results2(19) + coeff*temp
results2_ti(19)=results2_ti(19) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(19).eq.results2(19)))  write(*,*) 'NaN at SS C[Sd, Su, conj[Sd], conj[Su]]' 
! ---- Se,Se ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSeSecSecSe(i1,i2,i1,i2)
Di_coup1 = dcplSeSecSecSe(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSeSecSecSe(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSeSecSecSe(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSe2(i1),MSe2(i2),dMSe2(i1,iv1),dMSe2(i2,iv1)         & 
& ,dMSe2(i1,iv2),dMSe2(i2,iv2),ddMSe2(i1,iv1,iv2),ddMSe2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(20)=results2(20) + coeff*temp
results2_ti(20)=results2_ti(20) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(20).eq.results2(20)))  write(*,*) 'NaN at SS C[Se, Se, conj[Se], conj[Se]]' 
! ---- Se,Sv ----
Do i1=1,6
 Do i2=1,3
coup1 = cplSeSvcSecSv(i1,i2,i1,i2)
Di_coup1 = dcplSeSvcSecSv(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSeSvcSecSv(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSeSvcSecSv(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSe2(i1),MSv2(i2),dMSe2(i1,iv1),dMSv2(i2,iv1)         & 
& ,dMSe2(i1,iv2),dMSv2(i2,iv2),ddMSe2(i1,iv1,iv2),ddMSv2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-1._dp)
results2(21)=results2(21) + coeff*temp
results2_ti(21)=results2_ti(21) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(21).eq.results2(21)))  write(*,*) 'NaN at SS C[Se, Sv, conj[Se], conj[Sv]]' 
! ---- Su,Su ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSuSucSucSu(i1,i2,i1,i2)
Di_coup1 = dcplSuSucSucSu(i1,i2,i1,i2,iv1)
Dj_coup1 = dcplSuSucSucSu(i1,i2,i1,i2,iv2)
DDcoup1 = ddcplSuSucSucSu(i1,i2,i1,i2,iv1,iv2)
Call SecondDerivativeVeff_balls(MSu2(i1),MSu2(i2),dMSu2(i1,iv1),dMSu2(i2,iv1)         & 
& ,dMSu2(i1,iv2),dMSu2(i2,iv2),ddMSu2(i1,iv1,iv2),ddMSu2(i2,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'SS',Q2,temp,temp_ti,temp_tj)
coeff = (-0.5_dp)
results2(22)=results2(22) + coeff*temp
results2_ti(22)=results2_ti(22) + coeff*temp_ti
  End Do
End Do
if (.not.(results2(22).eq.results2(22)))  write(*,*) 'NaN at SS C[Su, Su, conj[Su], conj[Su]]' 

! ----- diagrams of type VS, 2 ------ 

! ---- Sd,VG ----
Do i1=1,6
coup1 = cplSdcSdVGVG(i1,i1)
Di_coup1 = dcplSdcSdVGVG(i1,i1,iv1)
Dj_coup1 = dcplSdcSdVGVG(i1,i1,iv2)
DDcoup1 = ddcplSdcSdVGVG(i1,i1,iv1,iv2)
Call SecondDerivativeVeff_balls(0._dp,MSd2(i1),ZeroC,dMSd2(i1,iv1),ZeroC,dMSd2(i1,iv2)& 
& ,ZeroC,ddMSd2(i1,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'VS',Q2,temp,temp_ti,temp_tj)
coeff = 0._dp
results2(23)=results2(23) + coeff*temp
results2_ti(23)=results2_ti(23) + coeff*temp_ti
End Do
if (.not.(results2(23).eq.results2(23)))  write(*,*) 'NaN at VS C[Sd, VG, VG, conj[Sd]]' 
! ---- Su,VG ----
Do i1=1,6
coup1 = cplSucSuVGVG(i1,i1)
Di_coup1 = dcplSucSuVGVG(i1,i1,iv1)
Dj_coup1 = dcplSucSuVGVG(i1,i1,iv2)
DDcoup1 = ddcplSucSuVGVG(i1,i1,iv1,iv2)
Call SecondDerivativeVeff_balls(0._dp,MSu2(i1),ZeroC,dMSu2(i1,iv1),ZeroC,dMSu2(i1,iv2)& 
& ,ZeroC,ddMSu2(i1,iv1,iv2),coup1,Di_coup1,Dj_coup1,DDcoup1,'VS',Q2,temp,temp_ti,temp_tj)
coeff = 0._dp
results2(24)=results2(24) + coeff*temp
results2_ti(24)=results2_ti(24) + coeff*temp_ti
End Do
if (.not.(results2(24).eq.results2(24)))  write(*,*) 'NaN at VS C[Su, VG, VG, conj[Su]]' 

  result = sum(results1)+sum(results2) ! 2nd deriv. of V
  result_ti = sum(results1_ti)+sum(results2_ti) ! 1st deriv. of V
  pi2L(iv1,iv2) = oo16pi2**2 * Real(result,dp) 
  End Do 
  ti2L(iv1) = oo16pi2**2 * Real(result_ti,dp) 
End Do 
Do iv1=1,3
  Do iv2=1,iv1-1
  pi2L(iv1,iv2) = pi2L(iv2,iv1) 
  End Do 
End Do 
End Subroutine SecondDerivativeEffPot2Loop 





Subroutine FirstDerivativeEffPot2Loop(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,             & 
& Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,kont,ti2L)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Integer, Intent(inout):: kont
Real(dp), Intent(out) :: ti2L(3)
Integer :: i,i1,i2,i3,includeGhosts,NrContr 
Integer :: iv1, iv2 
Integer :: NrContr1,NrContr2 !nr of contributing diagrams
Real(dp) :: Q2,colorfactor,coeff,coeffbar
Complex(dp) :: result,temp,tempbar
Complex(dp) :: coup1,coup2,coup1L,coup1R,coup2L,coup2R,coupx,coupxbar
Complex(dp) :: dcoup1,dcoup2,dcoup1L,dcoup1R,dcoup2L,dcoup2R,dcoupx,dcoupxbar
Real(dp) :: gout(26796) 
Real(dp) :: results1(42),results2(24)
Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

Complex(dp) :: dcplAhAhAh(3,3,3,3),dcplAhAhhh(3,3,3,3),dcplAhhhhh(3,3,3,3),dcplAhHpmcHpm(3,2,2,3),   & 
& dcplAhSdcSd(3,6,6,3),dcplAhSecSe(3,6,6,3),dcplAhSucSu(3,6,6,3),dcplhhhhhh(3,3,3,3),    & 
& dcplhhHpmcHpm(3,2,2,3),dcplhhSdcSd(3,6,6,3),dcplhhSecSe(3,6,6,3),dcplhhSucSu(3,6,6,3), & 
& dcplHpmSucSd(2,6,6,3),dcplHpmSvcSe(2,3,6,3),dcplSdcHpmcSu(6,2,6,3),dcplSecHpmcSv(6,2,3,3),& 
& dcplSdcSdVG(6,6,3),dcplSucSuVG(6,6,3),dcplVGVGVG(3),dcplcChaChaAhL(2,2,3,3),           & 
& dcplcChaChaAhR(2,2,3,3),dcplChiChiAhL(5,5,3,3),dcplChiChiAhR(5,5,3,3),dcplcFdFdAhL(3,3,3,3),& 
& dcplcFdFdAhR(3,3,3,3),dcplcFeFeAhL(3,3,3,3),dcplcFeFeAhR(3,3,3,3),dcplcFuFuAhL(3,3,3,3),& 
& dcplcFuFuAhR(3,3,3,3),dcplChiChacHpmL(5,2,2,3),dcplChiChacHpmR(5,2,2,3),               & 
& dcplChaFucSdL(2,3,6,3),dcplChaFucSdR(2,3,6,3),dcplChaFvcSeL(2,3,6,3),dcplChaFvcSeR(2,3,6,3),& 
& dcplcChaChahhL(2,2,3,3),dcplcChaChahhR(2,2,3,3),dcplcFdChaSuL(3,2,6,3),dcplcFdChaSuR(3,2,6,3),& 
& dcplcFeChaSvL(3,2,3,3),dcplcFeChaSvR(3,2,3,3),dcplChiChihhL(5,5,3,3),dcplChiChihhR(5,5,3,3),& 
& dcplChiFdcSdL(5,3,6,3),dcplChiFdcSdR(5,3,6,3),dcplChiFecSeL(5,3,6,3),dcplChiFecSeR(5,3,6,3),& 
& dcplChiFucSuL(5,3,6,3),dcplChiFucSuR(5,3,6,3),dcplcChaChiHpmL(2,5,2,3),dcplcChaChiHpmR(2,5,2,3),& 
& dcplcFdChiSdL(3,5,6,3),dcplcFdChiSdR(3,5,6,3),dcplcFeChiSeL(3,5,6,3),dcplcFeChiSeR(3,5,6,3),& 
& dcplcFuChiSuL(3,5,6,3),dcplcFuChiSuR(3,5,6,3),dcplGluFdcSdL(3,6,3),dcplGluFdcSdR(3,6,3),& 
& dcplcFdFdhhL(3,3,3,3),dcplcFdFdhhR(3,3,3,3),dcplcChaFdcSuL(2,3,6,3),dcplcChaFdcSuR(2,3,6,3),& 
& dcplcFuFdcHpmL(3,3,2,3),dcplcFuFdcHpmR(3,3,2,3),dcplcFeFehhL(3,3,3,3),dcplcFeFehhR(3,3,3,3),& 
& dcplcChaFecSvL(2,3,3,3),dcplcChaFecSvR(2,3,3,3),dcplcFvFecHpmL(3,3,2,3),               & 
& dcplcFvFecHpmR(3,3,2,3),dcplGluFucSuL(3,6,3),dcplGluFucSuR(3,6,3),dcplcFuFuhhL(3,3,3,3),& 
& dcplcFuFuhhR(3,3,3,3),dcplcFdFuHpmL(3,3,2,3),dcplcFdFuHpmR(3,3,2,3),dcplcFeFvHpmL(3,3,2,3),& 
& dcplcFeFvHpmR(3,3,2,3),dcplcFdGluSdL(3,6,3),dcplcFdGluSdR(3,6,3),dcplcFuGluSuL(3,6,3), & 
& dcplcFuGluSuR(3,6,3),dcplcChacFuSdL(2,3,6,3),dcplcChacFuSdR(2,3,6,3),dcplcChacFvSeL(2,3,6,3),& 
& dcplcChacFvSeR(2,3,6,3),dcplcFdFdVGL(3,3,3),dcplcFdFdVGR(3,3,3),dcplcFuFuVGL(3,3,3),   & 
& dcplcFuFuVGR(3,3,3),dcplGluGluVGL(3),dcplGluGluVGR(3)

Complex(dp) :: dcplAhAhAhAh(3,3,3,3,3),dcplAhAhhhhh(3,3,3,3,3),dcplAhAhHpmcHpm(3,3,2,2,3),           & 
& dcplAhAhSdcSd(3,3,6,6,3),dcplAhAhSecSe(3,3,6,6,3),dcplAhAhSucSu(3,3,6,6,3),            & 
& dcplhhhhhhhh(3,3,3,3,3),dcplhhhhHpmcHpm(3,3,2,2,3),dcplhhhhSdcSd(3,3,6,6,3),           & 
& dcplhhhhSecSe(3,3,6,6,3),dcplhhhhSucSu(3,3,6,6,3),dcplHpmHpmcHpmcHpm(2,2,2,2,3),       & 
& dcplHpmSdcHpmcSd(2,6,2,6,3),dcplHpmSecHpmcSe(2,6,2,6,3),dcplHpmSucHpmcSu(2,6,2,6,3),   & 
& dcplHpmSvcHpmcSv(2,3,2,3,3),dcplSdSdcSdcSd(6,6,6,6,3),dcplSdSecSdcSe(6,6,6,6,3),       & 
& dcplSdSucSdcSu(6,6,6,6,3),dcplSeSecSecSe(6,6,6,6,3),dcplSeSvcSecSv(6,3,6,3,3),         & 
& dcplSuSucSucSu(6,6,6,6,3),dcplSdcSdVGVG(6,6,3),dcplSucSuVGVG(6,6,3)

Real(dp) :: MSd(6),MSd2(6),MSv(3),MSv2(3),MSu(6),MSu2(6),MSe(6),MSe2(6),Mhh(3),Mhh2(3),           & 
& MAh(3),MAh2(3),MHpm(2),MHpm2(2),MChi(5),MChi2(5),MCha(2),MCha2(2),MFe(3),              & 
& MFe2(3),MFd(3),MFd2(3),MFu(3),MFu2(3),MGlu,MGlu2,MVZ,MVZ2,MVWm,MVWm2

Complex(dp) :: dMSd(6,3),dMSd2(6,3),dMSv(3,3),dMSv2(3,3),dMSu(6,3),dMSu2(6,3),dMSe(6,3),             & 
& dMSe2(6,3),dMhh(3,3),dMhh2(3,3),dMAh(3,3),dMAh2(3,3),dMHpm(2,3),dMHpm2(2,3),           & 
& dMChi(5,3),dMChi2(5,3),dMCha(2,3),dMCha2(2,3),dMFe(3,3),dMFe2(3,3),dMFd(3,3),          & 
& dMFd2(3,3),dMFu(3,3),dMFu2(3,3),dMGlu(1,3),dMGlu2(1,3),dMVZ(1,3),dMVZ2(1,3),           & 
& dMVWm(1,3),dMVWm2(1,3)

!! ------------------------------------------------- 
!! Calculate masses, couplings and their derivatives 
!! ------------------------------------------------- 

Do i1=1,3
Call FirstDerivativeMassesCoups(i1,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,             & 
& Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Call GToMassesCoups(gout,MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,MAh,            & 
& MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,           & 
& MVZ,MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,             & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,               & 
& cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,           & 
& cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,        & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,        & 
& cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,           & 
& cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,             & 
& cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,cplSucSuVGVG)

dMSd(:,i1) = MSd
dMSd2(:,i1) = MSd2
dMSv(:,i1) = MSv
dMSv2(:,i1) = MSv2
dMSu(:,i1) = MSu
dMSu2(:,i1) = MSu2
dMSe(:,i1) = MSe
dMSe2(:,i1) = MSe2
dMhh(:,i1) = Mhh
dMhh2(:,i1) = Mhh2
dMAh(:,i1) = MAh
dMAh2(:,i1) = MAh2
dMHpm(:,i1) = MHpm
dMHpm2(:,i1) = MHpm2
dMChi(:,i1) = MChi
dMChi2(:,i1) = MChi2
dMCha(:,i1) = MCha
dMCha2(:,i1) = MCha2
dMFe(:,i1) = MFe
dMFe2(:,i1) = MFe2
dMFd(:,i1) = MFd
dMFd2(:,i1) = MFd2
dMFu(:,i1) = MFu
dMFu2(:,i1) = MFu2
dMGlu(:,i1) = MGlu
dMGlu2(:,i1) = MGlu2
dMVZ(:,i1) = MVZ
dMVZ2(:,i1) = MVZ2
dMVWm(:,i1) = MVWm
dMVWm2(:,i1) = MVWm2
dcplAhAhAh(:,:,:,i1) = cplAhAhAh
dcplAhAhhh(:,:,:,i1) = cplAhAhhh
dcplAhhhhh(:,:,:,i1) = cplAhhhhh
dcplAhHpmcHpm(:,:,:,i1) = cplAhHpmcHpm
dcplAhSdcSd(:,:,:,i1) = cplAhSdcSd
dcplAhSecSe(:,:,:,i1) = cplAhSecSe
dcplAhSucSu(:,:,:,i1) = cplAhSucSu
dcplhhhhhh(:,:,:,i1) = cplhhhhhh
dcplhhHpmcHpm(:,:,:,i1) = cplhhHpmcHpm
dcplhhSdcSd(:,:,:,i1) = cplhhSdcSd
dcplhhSecSe(:,:,:,i1) = cplhhSecSe
dcplhhSucSu(:,:,:,i1) = cplhhSucSu
dcplHpmSucSd(:,:,:,i1) = cplHpmSucSd
dcplHpmSvcSe(:,:,:,i1) = cplHpmSvcSe
dcplSdcHpmcSu(:,:,:,i1) = cplSdcHpmcSu
dcplSecHpmcSv(:,:,:,i1) = cplSecHpmcSv
dcplSdcSdVG(:,:,i1) = cplSdcSdVG
dcplSucSuVG(:,:,i1) = cplSucSuVG
dcplVGVGVG(i1) = cplVGVGVG
dcplcChaChaAhL(:,:,:,i1) = cplcChaChaAhL
dcplcChaChaAhR(:,:,:,i1) = cplcChaChaAhR
dcplChiChiAhL(:,:,:,i1) = cplChiChiAhL
dcplChiChiAhR(:,:,:,i1) = cplChiChiAhR
dcplcFdFdAhL(:,:,:,i1) = cplcFdFdAhL
dcplcFdFdAhR(:,:,:,i1) = cplcFdFdAhR
dcplcFeFeAhL(:,:,:,i1) = cplcFeFeAhL
dcplcFeFeAhR(:,:,:,i1) = cplcFeFeAhR
dcplcFuFuAhL(:,:,:,i1) = cplcFuFuAhL
dcplcFuFuAhR(:,:,:,i1) = cplcFuFuAhR
dcplChiChacHpmL(:,:,:,i1) = cplChiChacHpmL
dcplChiChacHpmR(:,:,:,i1) = cplChiChacHpmR
dcplChaFucSdL(:,:,:,i1) = cplChaFucSdL
dcplChaFucSdR(:,:,:,i1) = cplChaFucSdR
dcplChaFvcSeL(:,:,:,i1) = cplChaFvcSeL
dcplChaFvcSeR(:,:,:,i1) = cplChaFvcSeR
dcplcChaChahhL(:,:,:,i1) = cplcChaChahhL
dcplcChaChahhR(:,:,:,i1) = cplcChaChahhR
dcplcFdChaSuL(:,:,:,i1) = cplcFdChaSuL
dcplcFdChaSuR(:,:,:,i1) = cplcFdChaSuR
dcplcFeChaSvL(:,:,:,i1) = cplcFeChaSvL
dcplcFeChaSvR(:,:,:,i1) = cplcFeChaSvR
dcplChiChihhL(:,:,:,i1) = cplChiChihhL
dcplChiChihhR(:,:,:,i1) = cplChiChihhR
dcplChiFdcSdL(:,:,:,i1) = cplChiFdcSdL
dcplChiFdcSdR(:,:,:,i1) = cplChiFdcSdR
dcplChiFecSeL(:,:,:,i1) = cplChiFecSeL
dcplChiFecSeR(:,:,:,i1) = cplChiFecSeR
dcplChiFucSuL(:,:,:,i1) = cplChiFucSuL
dcplChiFucSuR(:,:,:,i1) = cplChiFucSuR
dcplcChaChiHpmL(:,:,:,i1) = cplcChaChiHpmL
dcplcChaChiHpmR(:,:,:,i1) = cplcChaChiHpmR
dcplcFdChiSdL(:,:,:,i1) = cplcFdChiSdL
dcplcFdChiSdR(:,:,:,i1) = cplcFdChiSdR
dcplcFeChiSeL(:,:,:,i1) = cplcFeChiSeL
dcplcFeChiSeR(:,:,:,i1) = cplcFeChiSeR
dcplcFuChiSuL(:,:,:,i1) = cplcFuChiSuL
dcplcFuChiSuR(:,:,:,i1) = cplcFuChiSuR
dcplGluFdcSdL(:,:,i1) = cplGluFdcSdL
dcplGluFdcSdR(:,:,i1) = cplGluFdcSdR
dcplcFdFdhhL(:,:,:,i1) = cplcFdFdhhL
dcplcFdFdhhR(:,:,:,i1) = cplcFdFdhhR
dcplcChaFdcSuL(:,:,:,i1) = cplcChaFdcSuL
dcplcChaFdcSuR(:,:,:,i1) = cplcChaFdcSuR
dcplcFuFdcHpmL(:,:,:,i1) = cplcFuFdcHpmL
dcplcFuFdcHpmR(:,:,:,i1) = cplcFuFdcHpmR
dcplcFeFehhL(:,:,:,i1) = cplcFeFehhL
dcplcFeFehhR(:,:,:,i1) = cplcFeFehhR
dcplcChaFecSvL(:,:,:,i1) = cplcChaFecSvL
dcplcChaFecSvR(:,:,:,i1) = cplcChaFecSvR
dcplcFvFecHpmL(:,:,:,i1) = cplcFvFecHpmL
dcplcFvFecHpmR(:,:,:,i1) = cplcFvFecHpmR
dcplGluFucSuL(:,:,i1) = cplGluFucSuL
dcplGluFucSuR(:,:,i1) = cplGluFucSuR
dcplcFuFuhhL(:,:,:,i1) = cplcFuFuhhL
dcplcFuFuhhR(:,:,:,i1) = cplcFuFuhhR
dcplcFdFuHpmL(:,:,:,i1) = cplcFdFuHpmL
dcplcFdFuHpmR(:,:,:,i1) = cplcFdFuHpmR
dcplcFeFvHpmL(:,:,:,i1) = cplcFeFvHpmL
dcplcFeFvHpmR(:,:,:,i1) = cplcFeFvHpmR
dcplcFdGluSdL(:,:,i1) = cplcFdGluSdL
dcplcFdGluSdR(:,:,i1) = cplcFdGluSdR
dcplcFuGluSuL(:,:,i1) = cplcFuGluSuL
dcplcFuGluSuR(:,:,i1) = cplcFuGluSuR
dcplcChacFuSdL(:,:,:,i1) = cplcChacFuSdL
dcplcChacFuSdR(:,:,:,i1) = cplcChacFuSdR
dcplcChacFvSeL(:,:,:,i1) = cplcChacFvSeL
dcplcChacFvSeR(:,:,:,i1) = cplcChacFvSeR
dcplcFdFdVGL(:,:,i1) = cplcFdFdVGL
dcplcFdFdVGR(:,:,i1) = cplcFdFdVGR
dcplcFuFuVGL(:,:,i1) = cplcFuFuVGL
dcplcFuFuVGR(:,:,i1) = cplcFuFuVGR
dcplGluGluVGL(i1) = cplGluGluVGL
dcplGluGluVGR(i1) = cplGluGluVGR
dcplAhAhAhAh(:,:,:,:,i1) = cplAhAhAhAh
dcplAhAhhhhh(:,:,:,:,i1) = cplAhAhhhhh
dcplAhAhHpmcHpm(:,:,:,:,i1) = cplAhAhHpmcHpm
dcplAhAhSdcSd(:,:,:,:,i1) = cplAhAhSdcSd
dcplAhAhSecSe(:,:,:,:,i1) = cplAhAhSecSe
dcplAhAhSucSu(:,:,:,:,i1) = cplAhAhSucSu
dcplhhhhhhhh(:,:,:,:,i1) = cplhhhhhhhh
dcplhhhhHpmcHpm(:,:,:,:,i1) = cplhhhhHpmcHpm
dcplhhhhSdcSd(:,:,:,:,i1) = cplhhhhSdcSd
dcplhhhhSecSe(:,:,:,:,i1) = cplhhhhSecSe
dcplhhhhSucSu(:,:,:,:,i1) = cplhhhhSucSu
dcplHpmHpmcHpmcHpm(:,:,:,:,i1) = cplHpmHpmcHpmcHpm
dcplHpmSdcHpmcSd(:,:,:,:,i1) = cplHpmSdcHpmcSd
dcplHpmSecHpmcSe(:,:,:,:,i1) = cplHpmSecHpmcSe
dcplHpmSucHpmcSu(:,:,:,:,i1) = cplHpmSucHpmcSu
dcplHpmSvcHpmcSv(:,:,:,:,i1) = cplHpmSvcHpmcSv
dcplSdSdcSdcSd(:,:,:,:,i1) = cplSdSdcSdcSd
dcplSdSecSdcSe(:,:,:,:,i1) = cplSdSecSdcSe
dcplSdSucSdcSu(:,:,:,:,i1) = cplSdSucSdcSu
dcplSeSecSecSe(:,:,:,:,i1) = cplSeSecSecSe
dcplSeSvcSecSv(:,:,:,:,i1) = cplSeSvcSecSv
dcplSuSucSucSu(:,:,:,:,i1) = cplSuSucSucSu
dcplSdcSdVGVG(:,:,i1) = cplSdcSdVGVG
dcplSucSuVGVG(:,:,i1) = cplSucSuVGVG
End Do 
 
Call TreeMassesEffPot(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,.True.,kont)

Call CouplingsForEffPot3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,Yd,Td,ZD,Ye,               & 
& Te,ZE,Yu,Tu,ZU,ZV,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,cplAhAhhh,          & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,    & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,              & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,      & 
& cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,       & 
& cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR)

Call CouplingsForEffPot4(lam,kap,ZA,ZH,ZP,Yd,ZD,Ye,ZE,Yu,ZU,ZV,g3,cplAhAhAhAh,        & 
& cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,         & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,               & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,    & 
& cplSucSuVGVG)



!! ------------------------------------------------- 
!! Calculate derivative of effective potential      
!! ------------------------------------------------- 



Q2 = getRenormalizationScale()
ti2L = 0._dp
result = ZeroC
results1 = ZeroC
results2 = ZeroC
Do iv1=1,3
! ----- Topology1 (sunrise): diagrams w. 3 Particles and 2 Vertices

! ----- diagrams of type SSS, 14 ------ 
! ---- Ah,Ah,Ah ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhAh(i1,i2,i3)
coup2 = cplAhAhAh(i1,i2,i3)
dcoup1 = dcplAhAhAh(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MAh2(i2),MAh2(i3),dMAh2(i1,iv1)             & 
& ,dMAh2(i2,iv1),dMAh2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 1._dp/12._dp
colorfactor = 1
results1(1)=results1(1) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Ah, Ah]' 
    End Do
  End Do
End Do
! ---- Ah,Ah,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhAhhh(i1,i2,i3)
coup2 = cplAhAhhh(i1,i2,i3)
dcoup1 = dcplAhAhhh(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MAh2(i2),Mhh2(i3),dMAh2(i1,iv1)             & 
& ,dMAh2(i2,iv1),dMhh2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.25_dp
colorfactor = 1
results1(2)=results1(2) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Ah, hh]' 
    End Do
  End Do
End Do
! ---- Ah,hh,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplAhhhhh(i1,i2,i3)
coup2 = cplAhhhhh(i1,i2,i3)
dcoup1 = dcplAhhhhh(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),Mhh2(i2),Mhh2(i3),dMAh2(i1,iv1)             & 
& ,dMhh2(i2,iv1),dMhh2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.25_dp
colorfactor = 1
results1(3)=results1(3) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, hh, hh]' 
    End Do
  End Do
End Do
! ---- Ah,Hpm,conj[Hpm] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplAhHpmcHpm(i1,i2,i3)
coup2 = cplAhHpmcHpm(i1,i3,i2)
dcoup1 = dcplAhHpmcHpm(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MHpm2(i2),MHpm2(i3),dMAh2(i1,iv1)           & 
& ,dMHpm2(i2,iv1),dMHpm2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 1
results1(4)=results1(4) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Hpm, conj[Hpm]]' 
    End Do
  End Do
End Do
! ---- Ah,Sd,conj[Sd] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSdcSd(i1,i2,i3)
coup2 = cplAhSdcSd(i1,i3,i2)
dcoup1 = dcplAhSdcSd(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MSd2(i2),MSd2(i3),dMAh2(i1,iv1)             & 
& ,dMSd2(i2,iv1),dMSd2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 3
results1(5)=results1(5) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Sd, conj[Sd]]' 
    End Do
  End Do
End Do
! ---- Ah,Se,conj[Se] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSecSe(i1,i2,i3)
coup2 = cplAhSecSe(i1,i3,i2)
dcoup1 = dcplAhSecSe(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MSe2(i2),MSe2(i3),dMAh2(i1,iv1)             & 
& ,dMSe2(i2,iv1),dMSe2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 1
results1(6)=results1(6) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Se, conj[Se]]' 
    End Do
  End Do
End Do
! ---- Ah,Su,conj[Su] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplAhSucSu(i1,i2,i3)
coup2 = cplAhSucSu(i1,i3,i2)
dcoup1 = dcplAhSucSu(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MAh2(i1),MSu2(i2),MSu2(i3),dMAh2(i1,iv1)             & 
& ,dMSu2(i2,iv1),dMSu2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 3
results1(7)=results1(7) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Ah, Su, conj[Su]]' 
    End Do
  End Do
End Do
! ---- hh,hh,hh ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1 = cplhhhhhh(i1,i2,i3)
coup2 = cplhhhhhh(i1,i2,i3)
dcoup1 = dcplhhhhhh(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(Mhh2(i1),Mhh2(i2),Mhh2(i3),dMhh2(i1,iv1)             & 
& ,dMhh2(i2,iv1),dMhh2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 1._dp/12._dp
colorfactor = 1
results1(8)=results1(8) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, hh, hh]' 
    End Do
  End Do
End Do
! ---- hh,Hpm,conj[Hpm] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1 = cplhhHpmcHpm(i1,i2,i3)
coup2 = cplhhHpmcHpm(i1,i3,i2)
dcoup1 = dcplhhHpmcHpm(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(Mhh2(i1),MHpm2(i2),MHpm2(i3),dMhh2(i1,iv1)           & 
& ,dMHpm2(i2,iv1),dMHpm2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 1
results1(9)=results1(9) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Hpm, conj[Hpm]]' 
    End Do
  End Do
End Do
! ---- hh,Sd,conj[Sd] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSdcSd(i1,i2,i3)
coup2 = cplhhSdcSd(i1,i3,i2)
dcoup1 = dcplhhSdcSd(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(Mhh2(i1),MSd2(i2),MSd2(i3),dMhh2(i1,iv1)             & 
& ,dMSd2(i2,iv1),dMSd2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 3
results1(10)=results1(10) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Sd, conj[Sd]]' 
    End Do
  End Do
End Do
! ---- hh,Se,conj[Se] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSecSe(i1,i2,i3)
coup2 = cplhhSecSe(i1,i3,i2)
dcoup1 = dcplhhSecSe(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(Mhh2(i1),MSe2(i2),MSe2(i3),dMhh2(i1,iv1)             & 
& ,dMSe2(i2,iv1),dMSe2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 1
results1(11)=results1(11) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Se, conj[Se]]' 
    End Do
  End Do
End Do
! ---- hh,Su,conj[Su] ----
Do i1=1,3
 Do i2=1,6
    Do i3=1,6
coup1 = cplhhSucSu(i1,i2,i3)
coup2 = cplhhSucSu(i1,i3,i2)
dcoup1 = dcplhhSucSu(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(Mhh2(i1),MSu2(i2),MSu2(i3),dMhh2(i1,iv1)             & 
& ,dMSu2(i2,iv1),dMSu2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 3
results1(12)=results1(12) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[hh, Su, conj[Su]]' 
    End Do
  End Do
End Do
! ---- Sd,conj[Hpm],conj[Su] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,6
coup1 = cplSdcHpmcSu(i1,i2,i3)
coup2 = cplHpmSucSd(i2,i3,i1)
dcoup1 = dcplSdcHpmcSu(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MSd2(i1),MHpm2(i2),MSu2(i3),dMSd2(i1,iv1)            & 
& ,dMHpm2(i2,iv1),dMSu2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 1._dp
colorfactor = 3
results1(13)=results1(13) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Sd, conj[Hpm], conj[Su]]' 
    End Do
  End Do
End Do
! ---- Se,conj[Hpm],conj[Sv] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1 = cplSecHpmcSv(i1,i2,i3)
coup2 = cplHpmSvcSe(i2,i3,i1)
dcoup1 = dcplSecHpmcSv(i1,i2,i3,iv1)
coupx=abs(coup1)**2 
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MSe2(i1),MHpm2(i2),MSv2(i3),dMSe2(i1,iv1)            & 
& ,dMHpm2(i2,iv1),dMSv2(i3,iv1),coupx,dcoupx,'SSS   ',Q2,temp)
coeff = 1._dp
colorfactor = 1
results1(14)=results1(14) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSS C[Se, conj[Hpm], conj[Sv]]' 
    End Do
  End Do
End Do
! ----- diagrams of type FFS, 22 ------ 
! ---- Ah,Cha,bar[Cha] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChaAhL(i3,i2,i1)
coup1R = cplcChaChaAhR(i3,i2,i1)
coup2L = cplcChaChaAhL(i2,i3,i1)
coup2R = cplcChaChaAhR(i2,i3,i1)
dcoup1L = dcplcChaChaAhL(i3,i2,i1,iv1)
dcoup1R = dcplcChaChaAhR(i3,i2,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MCha2(i3),MCha2(i2),MAh2(i1),dMCha2(i3,iv1)          & 
& ,dMCha2(i2,iv1),dMAh2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MCha2(i3),MCha2(i2),MAh2(i1),dMCha2(i3,iv1)          & 
& ,dMCha2(i2,iv1),dMAh2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(15)=results1(15) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Cha, bar[Cha]]' 
coeffbar = 0.5_dp
results1(15)=results1(15) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Ah,Chi,Chi ----
Do i1=1,3
 Do i2=1,5
    Do i3=1,5
coup1L = cplChiChiAhL(i2,i3,i1)
coup1R = cplChiChiAhR(i2,i3,i1)
coup2L = cplChiChiAhL(i2,i3,i1)
coup2R = cplChiChiAhR(i2,i3,i1)
dcoup1L = dcplChiChiAhL(i2,i3,i1,iv1)
dcoup1R = dcplChiChiAhR(i2,i3,i1,iv1)
coupx=(abs(coup1L)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L) 
coupxbar=Real(coup1L**2,dp) 
dcoupxbar=Real(2*dcoup1L*coup1L,dp) 
Call FirstDerivativeVeff_sunrise(MChi2(i3),MChi2(i2),MAh2(i1),dMChi2(i3,iv1)          & 
& ,dMChi2(i2,iv1),dMAh2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MChi2(i3),MChi2(i2),MAh2(i1),dMChi2(i3,iv1)          & 
& ,dMChi2(i2,iv1),dMAh2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(16)=results1(16) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Chi, Chi]' 
coeffbar = 0.5_dp
results1(16)=results1(16) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Ah,Fd,bar[Fd] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdAhL(i3,i2,i1)
coup1R = cplcFdFdAhR(i3,i2,i1)
coup2L = cplcFdFdAhL(i2,i3,i1)
coup2R = cplcFdFdAhR(i2,i3,i1)
dcoup1L = dcplcFdFdAhL(i3,i2,i1,iv1)
dcoup1R = dcplcFdFdAhR(i3,i2,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i2),MAh2(i1),dMFd2(i3,iv1)             & 
& ,dMFd2(i2,iv1),dMAh2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i2),MAh2(i1),dMFd2(i3,iv1)             & 
& ,dMFd2(i2,iv1),dMAh2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 3
results1(17)=results1(17) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fd, bar[Fd]]' 
coeffbar = 0.5_dp
results1(17)=results1(17) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Ah,Fe,bar[Fe] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFeAhL(i3,i2,i1)
coup1R = cplcFeFeAhR(i3,i2,i1)
coup2L = cplcFeFeAhL(i2,i3,i1)
coup2R = cplcFeFeAhR(i2,i3,i1)
dcoup1L = dcplcFeFeAhL(i3,i2,i1,iv1)
dcoup1R = dcplcFeFeAhR(i3,i2,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFe2(i3),MFe2(i2),MAh2(i1),dMFe2(i3,iv1)             & 
& ,dMFe2(i2,iv1),dMAh2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFe2(i3),MFe2(i2),MAh2(i1),dMFe2(i3,iv1)             & 
& ,dMFe2(i2,iv1),dMAh2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(18)=results1(18) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fe, bar[Fe]]' 
coeffbar = 0.5_dp
results1(18)=results1(18) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Ah,Fu,bar[Fu] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuAhL(i3,i2,i1)
coup1R = cplcFuFuAhR(i3,i2,i1)
coup2L = cplcFuFuAhL(i2,i3,i1)
coup2R = cplcFuFuAhR(i2,i3,i1)
dcoup1L = dcplcFuFuAhL(i3,i2,i1,iv1)
dcoup1R = dcplcFuFuAhR(i3,i2,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i2),MAh2(i1),dMFu2(i3,iv1)             & 
& ,dMFu2(i2,iv1),dMAh2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i2),MAh2(i1),dMFu2(i3,iv1)             & 
& ,dMFu2(i2,iv1),dMAh2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 3
results1(19)=results1(19) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Ah, Fu, bar[Fu]]' 
coeffbar = 0.5_dp
results1(19)=results1(19) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Cha,hh,bar[Cha] ----
Do i1=1,2
 Do i2=1,3
    Do i3=1,2
coup1L = cplcChaChahhL(i3,i1,i2)
coup1R = cplcChaChahhR(i3,i1,i2)
coup2L = cplcChaChahhL(i1,i3,i2)
coup2R = cplcChaChahhR(i1,i3,i2)
dcoup1L = dcplcChaChahhL(i3,i1,i2,iv1)
dcoup1R = dcplcChaChahhR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MCha2(i3),MCha2(i1),Mhh2(i2),dMCha2(i3,iv1)          & 
& ,dMCha2(i1,iv1),dMhh2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MCha2(i3),MCha2(i1),Mhh2(i2),dMCha2(i3,iv1)          & 
& ,dMCha2(i1,iv1),dMhh2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(20)=results1(20) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Cha, hh, bar[Cha]]' 
coeffbar = 0.5_dp
results1(20)=results1(20) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Chi,Chi,hh ----
Do i1=1,5
 Do i2=1,5
    Do i3=1,3
coup1L = cplChiChihhL(i1,i2,i3)
coup1R = cplChiChihhR(i1,i2,i3)
coup2L = cplChiChihhL(i1,i2,i3)
coup2R = cplChiChihhR(i1,i2,i3)
dcoup1L = dcplChiChihhL(i1,i2,i3,iv1)
dcoup1R = dcplChiChihhR(i1,i2,i3,iv1)
coupx=(abs(coup1L)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L) 
coupxbar=Real(coup1L**2,dp) 
dcoupxbar=Real(2*dcoup1L*coup1L,dp) 
Call FirstDerivativeVeff_sunrise(MChi2(i2),MChi2(i1),Mhh2(i3),dMChi2(i2,iv1)          & 
& ,dMChi2(i1,iv1),dMhh2(i3,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MChi2(i2),MChi2(i1),Mhh2(i3),dMChi2(i2,iv1)          & 
& ,dMChi2(i1,iv1),dMhh2(i3,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(21)=results1(21) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Chi, hh]' 
coeffbar = 0.5_dp
results1(21)=results1(21) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Chi,Hpm,bar[Cha] ----
Do i1=1,5
 Do i2=1,2
    Do i3=1,2
coup1L = cplcChaChiHpmL(i3,i1,i2)
coup1R = cplcChaChiHpmR(i3,i1,i2)
coup2L = cplChiChacHpmL(i1,i3,i2)
coup2R = cplChiChacHpmR(i1,i3,i2)
dcoup1L = dcplcChaChiHpmL(i3,i1,i2,iv1)
dcoup1R = dcplcChaChiHpmR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MCha2(i3),MChi2(i1),MHpm2(i2),dMCha2(i3,iv1)         & 
& ,dMChi2(i1,iv1),dMHpm2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MCha2(i3),MChi2(i1),MHpm2(i2),dMCha2(i3,iv1)         & 
& ,dMChi2(i1,iv1),dMHpm2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 1
results1(22)=results1(22) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Hpm, bar[Cha]]' 
coeffbar = 1._dp
results1(22)=results1(22) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Chi,Sd,bar[Fd] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdChiSdL(i3,i1,i2)
coup1R = cplcFdChiSdR(i3,i1,i2)
coup2L = cplChiFdcSdL(i1,i3,i2)
coup2R = cplChiFdcSdR(i1,i3,i2)
dcoup1L = dcplcFdChiSdL(i3,i1,i2,iv1)
dcoup1R = dcplcFdChiSdR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MChi2(i1),MSd2(i2),dMFd2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSd2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MChi2(i1),MSd2(i2),dMFd2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSd2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 3
results1(23)=results1(23) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Sd, bar[Fd]]' 
coeffbar = 1._dp
results1(23)=results1(23) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Chi,Se,bar[Fe] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFeChiSeL(i3,i1,i2)
coup1R = cplcFeChiSeR(i3,i1,i2)
coup2L = cplChiFecSeL(i1,i3,i2)
coup2R = cplChiFecSeR(i1,i3,i2)
dcoup1L = dcplcFeChiSeL(i3,i1,i2,iv1)
dcoup1R = dcplcFeChiSeR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFe2(i3),MChi2(i1),MSe2(i2),dMFe2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSe2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFe2(i3),MChi2(i1),MSe2(i2),dMFe2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSe2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 1
results1(24)=results1(24) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Se, bar[Fe]]' 
coeffbar = 1._dp
results1(24)=results1(24) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Chi,Su,bar[Fu] ----
Do i1=1,5
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuChiSuL(i3,i1,i2)
coup1R = cplcFuChiSuR(i3,i1,i2)
coup2L = cplChiFucSuL(i1,i3,i2)
coup2R = cplChiFucSuR(i1,i3,i2)
dcoup1L = dcplcFuChiSuL(i3,i1,i2,iv1)
dcoup1R = dcplcFuChiSuR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MChi2(i1),MSu2(i2),dMFu2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSu2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MChi2(i1),MSu2(i2),dMFu2(i3,iv1)            & 
& ,dMChi2(i1,iv1),dMSu2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 3
results1(25)=results1(25) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Chi, Su, bar[Fu]]' 
coeffbar = 1._dp
results1(25)=results1(25) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fd,hh,bar[Fd] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFdFdhhL(i3,i1,i2)
coup1R = cplcFdFdhhR(i3,i1,i2)
coup2L = cplcFdFdhhL(i1,i3,i2)
coup2R = cplcFdFdhhR(i1,i3,i2)
dcoup1L = dcplcFdFdhhL(i3,i1,i2,iv1)
dcoup1R = dcplcFdFdhhR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),Mhh2(i2),dMFd2(i3,iv1)             & 
& ,dMFd2(i1,iv1),dMhh2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),Mhh2(i2),dMFd2(i3,iv1)             & 
& ,dMFd2(i1,iv1),dMhh2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 3
results1(26)=results1(26) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fd, hh, bar[Fd]]' 
coeffbar = 0.5_dp
results1(26)=results1(26) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fd,bar[Cha],conj[Su] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,6
coup1L = cplcChaFdcSuL(i2,i1,i3)
coup1R = cplcChaFdcSuR(i2,i1,i3)
coup2L = cplcFdChaSuL(i1,i2,i3)
coup2R = cplcFdChaSuR(i1,i2,i3)
dcoup1L = dcplcChaFdcSuL(i2,i1,i3,iv1)
dcoup1R = dcplcChaFdcSuR(i2,i1,i3,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MCha2(i2),MFd2(i1),MSu2(i3),dMCha2(i2,iv1)           & 
& ,dMFd2(i1,iv1),dMSu2(i3,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MCha2(i2),MFd2(i1),MSu2(i3),dMCha2(i2,iv1)           & 
& ,dMFd2(i1,iv1),dMSu2(i3,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 3
results1(27)=results1(27) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fd, bar[Cha], conj[Su]]' 
coeffbar = 1._dp
results1(27)=results1(27) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fe,hh,bar[Fe] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFeFehhL(i3,i1,i2)
coup1R = cplcFeFehhR(i3,i1,i2)
coup2L = cplcFeFehhL(i1,i3,i2)
coup2R = cplcFeFehhR(i1,i3,i2)
dcoup1L = dcplcFeFehhL(i3,i1,i2,iv1)
dcoup1R = dcplcFeFehhR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFe2(i3),MFe2(i1),Mhh2(i2),dMFe2(i3,iv1)             & 
& ,dMFe2(i1,iv1),dMhh2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFe2(i3),MFe2(i1),Mhh2(i2),dMFe2(i3,iv1)             & 
& ,dMFe2(i1,iv1),dMhh2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 1
results1(28)=results1(28) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fe, hh, bar[Fe]]' 
coeffbar = 0.5_dp
results1(28)=results1(28) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fe,bar[Cha],conj[Sv] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChaFecSvL(i2,i1,i3)
coup1R = cplcChaFecSvR(i2,i1,i3)
coup2L = cplcFeChaSvL(i1,i2,i3)
coup2R = cplcFeChaSvR(i1,i2,i3)
dcoup1L = dcplcChaFecSvL(i2,i1,i3,iv1)
dcoup1R = dcplcChaFecSvR(i2,i1,i3,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MCha2(i2),MFe2(i1),MSv2(i3),dMCha2(i2,iv1)           & 
& ,dMFe2(i1,iv1),dMSv2(i3,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MCha2(i2),MFe2(i1),MSv2(i3),dMCha2(i2,iv1)           & 
& ,dMFe2(i1,iv1),dMSv2(i3,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 1
results1(29)=results1(29) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fe, bar[Cha], conj[Sv]]' 
coeffbar = 1._dp
results1(29)=results1(29) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fu,hh,bar[Fu] ----
Do i1=1,3
 Do i2=1,3
    Do i3=1,3
coup1L = cplcFuFuhhL(i3,i1,i2)
coup1R = cplcFuFuhhR(i3,i1,i2)
coup2L = cplcFuFuhhL(i1,i3,i2)
coup2R = cplcFuFuhhR(i1,i3,i2)
dcoup1L = dcplcFuFuhhL(i3,i1,i2,iv1)
dcoup1R = dcplcFuFuhhR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),Mhh2(i2),dMFu2(i3,iv1)             & 
& ,dMFu2(i1,iv1),dMhh2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),Mhh2(i2),dMFu2(i3,iv1)             & 
& ,dMFu2(i1,iv1),dMhh2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 0.5_dp
colorfactor = 3
results1(30)=results1(30) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fu, hh, bar[Fu]]' 
coeffbar = 0.5_dp
results1(30)=results1(30) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fu,Hpm,bar[Fd] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFdFuHpmL(i3,i1,i2)
coup1R = cplcFdFuHpmR(i3,i1,i2)
coup2L = cplcFuFdcHpmL(i1,i3,i2)
coup2R = cplcFuFdcHpmR(i1,i3,i2)
dcoup1L = dcplcFdFuHpmL(i3,i1,i2,iv1)
dcoup1R = dcplcFdFuHpmR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFu2(i1),MHpm2(i2),dMFd2(i3,iv1)            & 
& ,dMFu2(i1,iv1),dMHpm2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFu2(i1),MHpm2(i2),dMFd2(i3,iv1)            & 
& ,dMFu2(i1,iv1),dMHpm2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 3
results1(31)=results1(31) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fu, Hpm, bar[Fd]]' 
coeffbar = 1._dp
results1(31)=results1(31) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Fv,Hpm,bar[Fe] ----
Do i1=1,3
 Do i2=1,2
    Do i3=1,3
coup1L = cplcFeFvHpmL(i3,i1,i2)
coup1R = cplcFeFvHpmR(i3,i1,i2)
coup2L = cplcFvFecHpmL(i1,i3,i2)
coup2R = cplcFvFecHpmR(i1,i3,i2)
dcoup1L = dcplcFeFvHpmL(i3,i1,i2,iv1)
dcoup1R = dcplcFeFvHpmR(i3,i1,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFe2(i3),0._dp,MHpm2(i2),dMFe2(i3,iv1)               & 
& ,ZeroC,dMHpm2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFe2(i3),0._dp,MHpm2(i2),dMFe2(i3,iv1)               & 
& ,ZeroC,dMHpm2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 1
results1(32)=results1(32) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Fv, Hpm, bar[Fe]]' 
coeffbar = 1._dp
results1(32)=results1(32) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Glu,Sd,bar[Fd] ----
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFdGluSdL(i3,i2)
coup1R = cplcFdGluSdR(i3,i2)
coup2L = cplGluFdcSdL(i3,i2)
coup2R = cplGluFdcSdR(i3,i2)
dcoup1L = dcplcFdGluSdL(i3,i2,iv1)
dcoup1R = dcplcFdGluSdR(i3,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MGlu2,MSd2(i2),dMFd2(i3,iv1),dMGlu2(1,iv1)  & 
& ,dMSd2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MGlu2,MSd2(i2),dMFd2(i3,iv1),dMGlu2(1,iv1)  & 
& ,dMSd2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 4
results1(33)=results1(33) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Glu, Sd, bar[Fd]]' 
coeffbar = 1._dp
results1(33)=results1(33) + coeffbar*colorfactor*tempbar
    End Do
  End Do
! ---- Glu,Su,bar[Fu] ----
 Do i2=1,6
    Do i3=1,3
coup1L = cplcFuGluSuL(i3,i2)
coup1R = cplcFuGluSuR(i3,i2)
coup2L = cplGluFucSuL(i3,i2)
coup2R = cplGluFucSuR(i3,i2)
dcoup1L = dcplcFuGluSuL(i3,i2,iv1)
dcoup1R = dcplcFuGluSuR(i3,i2,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MGlu2,MSu2(i2),dMFu2(i3,iv1),dMGlu2(1,iv1)  & 
& ,dMSu2(i2,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MGlu2,MSu2(i2),dMFu2(i3,iv1),dMGlu2(1,iv1)  & 
& ,dMSu2(i2,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 4
results1(34)=results1(34) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Glu, Su, bar[Fu]]' 
coeffbar = 1._dp
results1(34)=results1(34) + coeffbar*colorfactor*tempbar
    End Do
  End Do
! ---- Sd,bar[Cha],bar[Fu] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFuSdL(i2,i3,i1)
coup1R = cplcChacFuSdR(i2,i3,i1)
coup2L = cplChaFucSdL(i2,i3,i1)
coup2R = cplChaFucSdR(i2,i3,i1)
dcoup1L = dcplcChacFuSdL(i2,i3,i1,iv1)
dcoup1R = dcplcChacFuSdR(i2,i3,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MCha2(i2),MSd2(i1),dMFu2(i3,iv1)            & 
& ,dMCha2(i2,iv1),dMSd2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MCha2(i2),MSd2(i1),dMFu2(i3,iv1)            & 
& ,dMCha2(i2,iv1),dMSd2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 3
results1(35)=results1(35) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Sd, bar[Cha], bar[Fu]]' 
coeffbar = 1._dp
results1(35)=results1(35) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ---- Se,bar[Cha],bar[Fv] ----
Do i1=1,6
 Do i2=1,2
    Do i3=1,3
coup1L = cplcChacFvSeL(i2,i3,i1)
coup1R = cplcChacFvSeR(i2,i3,i1)
coup2L = cplChaFvcSeL(i2,i3,i1)
coup2R = cplChaFvcSeR(i2,i3,i1)
dcoup1L = dcplcChacFvSeL(i2,i3,i1,iv1)
dcoup1R = dcplcChacFvSeR(i2,i3,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(0._dp,MCha2(i2),MSe2(i1),ZeroC,dMCha2(i2,iv1)        & 
& ,dMSe2(i1,iv1),coupx,dcoupx,'FFS   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(0._dp,MCha2(i2),MSe2(i1),ZeroC,dMCha2(i2,iv1)        & 
& ,dMSe2(i1,iv1),coupxbar,dcoupxbar,'FFSbar',Q2,tempbar)
coeff = 1._dp
colorfactor = 1
results1(36)=results1(36) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFS C[Se, bar[Cha], bar[Fv]]' 
coeffbar = 1._dp
results1(36)=results1(36) + coeffbar*colorfactor*tempbar
    End Do
  End Do
End Do
! ----- diagrams of type SSV, 2 ------ 
! ---- Sd,VG,conj[Sd] ----
Do i1=1,6
    Do i3=1,6
coup1 = cplSdcSdVG(i1,i3)
coup2 = cplSdcSdVG(i3,i1)
dcoup1 = dcplSdcSdVG(i1,i3,iv1)
coupx=abs(coup1)**2
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MSd2(i3),MSd2(i1),0._dp,dMSd2(i3,iv1),dMSd2(i1,iv1)  & 
& ,ZeroC,coupx,dcoupx,'SSV   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 4
results1(37)=results1(37) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSV C[Sd, VG, conj[Sd]]' 
    End Do
End Do
! ---- Su,VG,conj[Su] ----
Do i1=1,6
    Do i3=1,6
coup1 = cplSucSuVG(i1,i3)
coup2 = cplSucSuVG(i3,i1)
dcoup1 = dcplSucSuVG(i1,i3,iv1)
coupx=abs(coup1)**2
dcoupx=dcoup1*conjg(coup1)+coup1*conjg(dcoup1) 
Call FirstDerivativeVeff_sunrise(MSu2(i3),MSu2(i1),0._dp,dMSu2(i3,iv1),dMSu2(i1,iv1)  & 
& ,ZeroC,coupx,dcoupx,'SSV   ',Q2,temp)
coeff = 0.5_dp
colorfactor = 4
results1(38)=results1(38) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SSV C[Su, VG, conj[Su]]' 
    End Do
End Do
! ----- diagrams of type FFV, 3 ------ 
! ---- Fd,VG,bar[Fd] ----
Do i1=1,3
    Do i3=1,3
coup1L = cplcFdFdVGL(i3,i1)
coup1R = cplcFdFdVGR(i3,i1)
coup2L = cplcFdFdVGL(i1,i3)
coup2R = cplcFdFdVGR(i1,i3)
dcoup1L = dcplcFdFdVGL(i3,i1,iv1)
dcoup1R = dcplcFdFdVGR(i3,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=-2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=-2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),0._dp,dMFd2(i3,iv1),dMFd2(i1,iv1)  & 
& ,ZeroC,coupx,dcoupx,'FFV   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFd2(i3),MFd2(i1),0._dp,dMFd2(i3,iv1),dMFd2(i1,iv1)  & 
& ,ZeroC,coupxbar,dcoupxbar,'FFVbar',Q2,temp)
coeff = 0.5_dp
colorfactor = 4
results1(39)=results1(39) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Fd, VG, bar[Fd]]' 
coeffbar = 0.5_dp
results1(39)=results1(39) + coeffbar*colorfactor*tempbar
    End Do
End Do
! ---- Fu,VG,bar[Fu] ----
Do i1=1,3
    Do i3=1,3
coup1L = cplcFuFuVGL(i3,i1)
coup1R = cplcFuFuVGR(i3,i1)
coup2L = cplcFuFuVGL(i1,i3)
coup2R = cplcFuFuVGR(i1,i3)
dcoup1L = dcplcFuFuVGL(i3,i1,iv1)
dcoup1R = dcplcFuFuVGR(i3,i1,iv1)
coupx=(abs(coup1L)**2+abs(coup1R)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L)+dcoup1R*conjg(coup1R)+coup1R*conjg(dcoup1R) 
coupxbar=-2*Real(coup1L*conjg(coup1R),dp) 
dcoupxbar=-2*Real(dcoup1L*conjg(coup1R)+coup1L*conjg(dcoup1R),dp) 
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),0._dp,dMFu2(i3,iv1),dMFu2(i1,iv1)  & 
& ,ZeroC,coupx,dcoupx,'FFV   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MFu2(i3),MFu2(i1),0._dp,dMFu2(i3,iv1),dMFu2(i1,iv1)  & 
& ,ZeroC,coupxbar,dcoupxbar,'FFVbar',Q2,temp)
coeff = 0.5_dp
colorfactor = 4
results1(40)=results1(40) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Fu, VG, bar[Fu]]' 
coeffbar = 0.5_dp
results1(40)=results1(40) + coeffbar*colorfactor*tempbar
    End Do
End Do
! ---- Glu,Glu,VG ----
coup1L = cplGluGluVGL
coup1R = cplGluGluVGR
coup2L = cplGluGluVGL
coup2R = cplGluGluVGR
dcoup1L = dcplGluGluVGL(iv1)
dcoup1R = dcplGluGluVGR(iv1)
coupx=(abs(coup1L)**2) 
dcoupx=dcoup1L*conjg(coup1L)+coup1L*conjg(dcoup1L) 
coupxbar=Real(coup1L**2,dp) 
dcoupxbar=Real(2*dcoup1L*coup1L,dp) 
Call FirstDerivativeVeff_sunrise(MGlu2,MGlu2,0._dp,dMGlu2(1,iv1),dMGlu2(1,iv1)        & 
& ,ZeroC,coupx,dcoupx,'FFV   ',Q2,temp)
Call FirstDerivativeVeff_sunrise(MGlu2,MGlu2,0._dp,dMGlu2(1,iv1),dMGlu2(1,iv1)        & 
& ,ZeroC,coupxbar,dcoupxbar,'FFVbar',Q2,temp)
coeff = 0.5_dp
colorfactor = 24
results1(41)=results1(41) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at FFV C[Glu, Glu, VG]' 
coeffbar = 0.5_dp
results1(41)=results1(41) + coeffbar*colorfactor*tempbar
! ----- diagrams of type VVV, 1 ------ 
! ---- VG,VG,VG ----
coup1 = cplVGVGVG
coup2 = cplVGVGVG
dcoup1 = dcplVGVGVG(iv1)
coeff = 0.0000
colorfactor = 24
results1(42)=results1(42) + coeff*colorfactor*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at VVV C[VG, VG, VG]' 
! ----- Topology2: diagrams w. 2 Particles and 1 Vertex

! ----- diagrams of type SS, 22 ------ 
! ---- Ah,Ah ----
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhAhAh(i1,i1,i2,i2)
dcoup1 = dcplAhAhAhAh(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),MAh2(i2),dMAh2(i1,iv1),dMAh2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp/8._dp)
results2(1)=results2(1) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Ah, Ah]' 
  End Do
End Do
! ---- Ah,hh ----
Do i1=1,3
 Do i2=1,3
coup1 = cplAhAhhhhh(i1,i1,i2,i2)
dcoup1 = dcplAhAhhhhh(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),Mhh2(i2),dMAh2(i1,iv1),dMhh2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.25_dp)
results2(2)=results2(2) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, hh, hh]' 
  End Do
End Do
! ---- Ah,Hpm ----
Do i1=1,3
 Do i2=1,2
coup1 = cplAhAhHpmcHpm(i1,i1,i2,i2)
dcoup1 = dcplAhAhHpmcHpm(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),MHpm2(i2),dMAh2(i1,iv1),dMHpm2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(3)=results2(3) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Hpm, conj[Hpm]]' 
  End Do
End Do
! ---- Ah,Sd ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSdcSd(i1,i1,i2,i2)
dcoup1 = dcplAhAhSdcSd(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),MSd2(i2),dMAh2(i1,iv1),dMSd2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(4)=results2(4) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Sd, conj[Sd]]' 
  End Do
End Do
! ---- Ah,Se ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSecSe(i1,i1,i2,i2)
dcoup1 = dcplAhAhSecSe(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),MSe2(i2),dMAh2(i1,iv1),dMSe2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(5)=results2(5) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Se, conj[Se]]' 
  End Do
End Do
! ---- Ah,Su ----
Do i1=1,3
 Do i2=1,6
coup1 = cplAhAhSucSu(i1,i1,i2,i2)
dcoup1 = dcplAhAhSucSu(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(MAh2(i1),MSu2(i2),dMAh2(i1,iv1),dMSu2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(6)=results2(6) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Ah, Ah, Su, conj[Su]]' 
  End Do
End Do
! ---- hh,hh ----
Do i1=1,3
 Do i2=1,3
coup1 = cplhhhhhhhh(i1,i1,i2,i2)
dcoup1 = dcplhhhhhhhh(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(Mhh2(i1),Mhh2(i2),dMhh2(i1,iv1),dMhh2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp/8._dp)
results2(7)=results2(7) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, hh, hh]' 
  End Do
End Do
! ---- hh,Hpm ----
Do i1=1,3
 Do i2=1,2
coup1 = cplhhhhHpmcHpm(i1,i1,i2,i2)
dcoup1 = dcplhhhhHpmcHpm(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(Mhh2(i1),MHpm2(i2),dMhh2(i1,iv1),dMHpm2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(8)=results2(8) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Hpm, conj[Hpm]]' 
  End Do
End Do
! ---- hh,Sd ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSdcSd(i1,i1,i2,i2)
dcoup1 = dcplhhhhSdcSd(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(Mhh2(i1),MSd2(i2),dMhh2(i1,iv1),dMSd2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(9)=results2(9) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Sd, conj[Sd]]' 
  End Do
End Do
! ---- hh,Se ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSecSe(i1,i1,i2,i2)
dcoup1 = dcplhhhhSecSe(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(Mhh2(i1),MSe2(i2),dMhh2(i1,iv1),dMSe2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(10)=results2(10) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Se, conj[Se]]' 
  End Do
End Do
! ---- hh,Su ----
Do i1=1,3
 Do i2=1,6
coup1 = cplhhhhSucSu(i1,i1,i2,i2)
dcoup1 = dcplhhhhSucSu(i1,i1,i2,i2,iv1)
Call FirstDerivativeVeff_balls(Mhh2(i1),MSu2(i2),dMhh2(i1,iv1),dMSu2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(11)=results2(11) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[hh, hh, Su, conj[Su]]' 
  End Do
End Do
! ---- Hpm,Hpm ----
Do i1=1,2
 Do i2=1,2
coup1 = cplHpmHpmcHpmcHpm(i1,i2,i1,i2)
dcoup1 = dcplHpmHpmcHpmcHpm(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MHpm2(i1),MHpm2(i2),dMHpm2(i1,iv1),dMHpm2(i2,iv1)      & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(12)=results2(12) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Hpm, conj[Hpm], conj[Hpm]]' 
  End Do
End Do
! ---- Hpm,Sd ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSdcHpmcSd(i1,i2,i1,i2)
dcoup1 = dcplHpmSdcHpmcSd(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MHpm2(i1),MSd2(i2),dMHpm2(i1,iv1),dMSd2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(13)=results2(13) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Sd, conj[Hpm], conj[Sd]]' 
  End Do
End Do
! ---- Hpm,Se ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSecHpmcSe(i1,i2,i1,i2)
dcoup1 = dcplHpmSecHpmcSe(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MHpm2(i1),MSe2(i2),dMHpm2(i1,iv1),dMSe2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(14)=results2(14) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Se, conj[Hpm], conj[Se]]' 
  End Do
End Do
! ---- Hpm,Su ----
Do i1=1,2
 Do i2=1,6
coup1 = cplHpmSucHpmcSu(i1,i2,i1,i2)
dcoup1 = dcplHpmSucHpmcSu(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MHpm2(i1),MSu2(i2),dMHpm2(i1,iv1),dMSu2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(15)=results2(15) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Su, conj[Hpm], conj[Su]]' 
  End Do
End Do
! ---- Hpm,Sv ----
Do i1=1,2
 Do i2=1,3
coup1 = cplHpmSvcHpmcSv(i1,i2,i1,i2)
dcoup1 = dcplHpmSvcHpmcSv(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MHpm2(i1),MSv2(i2),dMHpm2(i1,iv1),dMSv2(i2,iv1)        & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(16)=results2(16) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Hpm, Sv, conj[Hpm], conj[Sv]]' 
  End Do
End Do
! ---- Sd,Sd ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSdcSdcSd(i1,i2,i1,i2)
dcoup1 = dcplSdSdcSdcSd(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSd2(i1),MSd2(i2),dMSd2(i1,iv1),dMSd2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(17)=results2(17) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Sd, conj[Sd], conj[Sd]]' 
  End Do
End Do
! ---- Sd,Se ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSecSdcSe(i1,i2,i1,i2)
dcoup1 = dcplSdSecSdcSe(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSd2(i1),MSe2(i2),dMSd2(i1,iv1),dMSe2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(18)=results2(18) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Se, conj[Sd], conj[Se]]' 
  End Do
End Do
! ---- Sd,Su ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSdSucSdcSu(i1,i2,i1,i2)
dcoup1 = dcplSdSucSdcSu(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSd2(i1),MSu2(i2),dMSd2(i1,iv1),dMSu2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(19)=results2(19) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Sd, Su, conj[Sd], conj[Su]]' 
  End Do
End Do
! ---- Se,Se ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSeSecSecSe(i1,i2,i1,i2)
dcoup1 = dcplSeSecSecSe(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSe2(i1),MSe2(i2),dMSe2(i1,iv1),dMSe2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(20)=results2(20) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Se, Se, conj[Se], conj[Se]]' 
  End Do
End Do
! ---- Se,Sv ----
Do i1=1,6
 Do i2=1,3
coup1 = cplSeSvcSecSv(i1,i2,i1,i2)
dcoup1 = dcplSeSvcSecSv(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSe2(i1),MSv2(i2),dMSe2(i1,iv1),dMSv2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-1._dp)
results2(21)=results2(21) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Se, Sv, conj[Se], conj[Sv]]' 
  End Do
End Do
! ---- Su,Su ----
Do i1=1,6
 Do i2=1,6
coup1 = cplSuSucSucSu(i1,i2,i1,i2)
dcoup1 = dcplSuSucSucSu(i1,i2,i1,i2,iv1)
Call FirstDerivativeVeff_balls(MSu2(i1),MSu2(i2),dMSu2(i1,iv1),dMSu2(i2,iv1)          & 
& ,coup1,dcoup1,'SS',Q2,temp)
coeff = (-0.5_dp)
results2(22)=results2(22) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at SS C[Su, Su, conj[Su], conj[Su]]' 
  End Do
End Do
! ----- diagrams of type VS, 2 ------ 
! ---- Sd,VG ----
Do i1=1,6
coup1 = cplSdcSdVGVG(i1,i1)
dcoup1 = dcplSdcSdVGVG(i1,i1,iv1)
Call FirstDerivativeVeff_balls(0._dp,MSd2(i1),ZeroC,dMSd2(i1,iv1),coup1,dcoup1,'VS',Q2,temp)
coeff = 0._dp
results2(23)=results2(23) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at VS C[Sd, VG, VG, conj[Sd]]' 
End Do
! ---- Su,VG ----
Do i1=1,6
coup1 = cplSucSuVGVG(i1,i1)
dcoup1 = dcplSucSuVGVG(i1,i1,iv1)
Call FirstDerivativeVeff_balls(0._dp,MSu2(i1),ZeroC,dMSu2(i1,iv1),coup1,dcoup1,'VS',Q2,temp)
coeff = 0._dp
results2(24)=results2(24) + coeff*temp
if (.not.(temp.eq.temp))  write(*,*) 'NaN at VS C[Su, VG, VG, conj[Su]]' 
End Do
result = sum(results1)+sum(results2) 


 
ti2L(iv1) = oo16pi2**2 * Real(result,dp) 
End Do 
End Subroutine FirstDerivativeEffPot2Loop 


Subroutine SecondDerivativeMassesCoups(i1,i2,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,             & 
& kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp), Intent(out) :: gout(:) 
Real(dp) :: err, vevs(3) 
Integer :: iout 
Integer, Intent(in) :: i1,i2 
vevs = (/vd,vu,vS/) 
gout = partialDiffXY_RiddersMulDim(AllMassesCouplings,26796,vevs,i1,i2,3,err) 
If (err.gt.err2L) err2L = err 
End Subroutine SecondDerivativeMassesCoups

Subroutine FirstDerivativeMassesCoups(i1,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,             & 
& Yu,Td,Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp), Intent(out) :: gout(:) 
Real(dp) :: err, vevs(3) 
Integer :: iout 
Integer, Intent(in) :: i1 
vevs = (/vd,vu,vS/) 
gout = partialDiff_RiddersMulDim(AllMassesCouplings,26796,vevs,i1,3,err) 
If (err.gt.err2L) err2L = err 
End Subroutine FirstDerivativeMassesCoups

Subroutine AllMassesCouplings(vevs,gout) 
Implicit None 
Real(dp), Intent(out) :: gout(26796) 
Real(dp), Intent(in) :: vevs(3) 
Integer :: kont 
Real(dp) :: vd,vu,vS

Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

Real(dp) :: MAh(3),MAh2(3),MCha(2),MCha2(2),MChi(5),MChi2(5),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(3),Mhh2(3),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(3,3),ZH(3,3),ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(5,5),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

vd=vevs(1) 
vu=vevs(2) 
vS=vevs(3) 
Call WrapperForDerivatives(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,             & 
& Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

End Subroutine 

Subroutine WrapperForDerivatives(vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,               & 
& Te,Tlam,Tk,Tu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,gout)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2,ms2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),lam,kap,Yu(3,3),Td(3,3),Te(3,3),Tlam,Tk,Tu(3,3),mq2(3,3),             & 
& ml2(3,3),md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu,vS

Real(dp), Intent(out) :: gout(:) 
Integer :: kont 
Real(dp) :: MSd(6),MSd2(6),MSv(3),MSv2(3),MSu(6),MSu2(6),MSe(6),MSe2(6),Mhh(3),Mhh2(3),           & 
& MAh(3),MAh2(3),MHpm(2),MHpm2(2),MChi(5),MChi2(5),MCha(2),MCha2(2),MFe(3),              & 
& MFe2(3),MFd(3),MFd2(3),MFu(3),MFu2(3),MGlu,MGlu2,MVZ,MVZ2,MVWm,MVWm2

Complex(dp) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

Call TreeMassesEffPot(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,betaH,vd,vu,vS,g1,g2,g3,Yd,Ye,lam,kap,Yu,Td,Te,Tlam,Tk,Tu,mq2,            & 
& ml2,mHd2,mHu2,md2,mu2,me2,ms2,M1,M2,M3,.True.,kont)

Call CouplingsForEffPot3(lam,Tlam,kap,Tk,vd,vu,vS,ZA,ZH,ZP,Yd,Td,ZD,Ye,               & 
& Te,ZE,Yu,Tu,ZU,ZV,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhAh,cplAhAhhh,          & 
& cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,        & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,    & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,              & 
& cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,              & 
& cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,      & 
& cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,       & 
& cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,         & 
& cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,         & 
& cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,       & 
& cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,          & 
& cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,         & 
& cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,      & 
& cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR)

Call CouplingsForEffPot4(lam,kap,ZA,ZH,ZP,Yd,ZD,Ye,ZE,Yu,ZU,ZV,g3,cplAhAhAhAh,        & 
& cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,         & 
& cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,               & 
& cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,         & 
& cplSdSecSdcSe,cplSdSucSdcSu,cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,    & 
& cplSucSuVGVG)

Call MassesCoupsToG(MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,MAh,MAh2,            & 
& MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,MVZ,            & 
& MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,cplAhSecSe,      & 
& cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,        & 
& cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcChaChaAhL,   & 
& cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,           & 
& cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,cplChiChacHpmR,cplChaFucSdL,        & 
& cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,cplcChaChahhR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,         & 
& cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcChaChiHpmL,       & 
& cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,       & 
& cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,          & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,       & 
& cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,      & 
& cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,            & 
& cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,cplAhAhSdcSd,cplAhAhSecSe,         & 
& cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,        & 
& cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,     & 
& cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,   & 
& cplSdcSdVGVG,cplSucSuVGVG,gout)

End Subroutine WrapperForDerivatives

Subroutine MassesCoupsToG(MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,               & 
& MAh,MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,             & 
& MGlu2,MVZ,MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,       & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,               & 
& cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,           & 
& cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,        & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,        & 
& cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,           & 
& cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,             & 
& cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,cplSucSuVGVG,g)

Implicit None 
Real(dp), Intent(out) :: g(:) 
Integer :: i1,i2,i3,i4, sumI
Real(dp),Intent(in) :: MSd(6),MSd2(6),MSv(3),MSv2(3),MSu(6),MSu2(6),MSe(6),MSe2(6),Mhh(3),Mhh2(3),           & 
& MAh(3),MAh2(3),MHpm(2),MHpm2(2),MChi(5),MChi2(5),MCha(2),MCha2(2),MFe(3),              & 
& MFe2(3),MFd(3),MFd2(3),MFu(3),MFu2(3),MGlu,MGlu2,MVZ,MVZ2,MVWm,MVWm2

Complex(dp),Intent(in) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp),Intent(in) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

g(1:6) = MSd
g(7:12) = MSd2
g(13:15) = MSv
g(16:18) = MSv2
g(19:24) = MSu
g(25:30) = MSu2
g(31:36) = MSe
g(37:42) = MSe2
g(43:45) = Mhh
g(46:48) = Mhh2
g(49:51) = MAh
g(52:54) = MAh2
g(55:56) = MHpm
g(57:58) = MHpm2
g(59:63) = MChi
g(64:68) = MChi2
g(69:70) = MCha
g(71:72) = MCha2
g(73:75) = MFe
g(76:78) = MFe2
g(79:81) = MFd
g(82:84) = MFd2
g(85:87) = MFu
g(88:90) = MFu2
g(91) = MGlu
g(92) = MGlu2
g(93) = MVZ
g(94) = MVZ2
g(95) = MVWm
g(96) = MVWm2
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+97) = Real(cplAhAhAh(i1,i2,i3), dp) 
g(SumI+98) = Aimag(cplAhAhAh(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+151) = Real(cplAhAhhh(i1,i2,i3), dp) 
g(SumI+152) = Aimag(cplAhAhhh(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+205) = Real(cplAhhhhh(i1,i2,i3), dp) 
g(SumI+206) = Aimag(cplAhhhhh(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
g(SumI+259) = Real(cplAhHpmcHpm(i1,i2,i3), dp) 
g(SumI+260) = Aimag(cplAhHpmcHpm(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+283) = Real(cplAhSdcSd(i1,i2,i3), dp) 
g(SumI+284) = Aimag(cplAhSdcSd(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+499) = Real(cplAhSecSe(i1,i2,i3), dp) 
g(SumI+500) = Aimag(cplAhSecSe(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+715) = Real(cplAhSucSu(i1,i2,i3), dp) 
g(SumI+716) = Aimag(cplAhSucSu(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+931) = Real(cplhhhhhh(i1,i2,i3), dp) 
g(SumI+932) = Aimag(cplhhhhhh(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
g(SumI+985) = Real(cplhhHpmcHpm(i1,i2,i3), dp) 
g(SumI+986) = Aimag(cplhhHpmcHpm(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+1009) = Real(cplhhSdcSd(i1,i2,i3), dp) 
g(SumI+1010) = Aimag(cplhhSdcSd(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+1225) = Real(cplhhSecSe(i1,i2,i3), dp) 
g(SumI+1226) = Aimag(cplhhSecSe(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+1441) = Real(cplhhSucSu(i1,i2,i3), dp) 
g(SumI+1442) = Aimag(cplhhSucSu(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
g(SumI+1657) = Real(cplHpmSucSd(i1,i2,i3), dp) 
g(SumI+1658) = Aimag(cplHpmSucSd(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+1801) = Real(cplHpmSvcSe(i1,i2,i3), dp) 
g(SumI+1802) = Aimag(cplHpmSvcSe(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
g(SumI+1873) = Real(cplSdcHpmcSu(i1,i2,i3), dp) 
g(SumI+1874) = Aimag(cplSdcHpmcSu(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+2017) = Real(cplSecHpmcSv(i1,i2,i3), dp) 
g(SumI+2018) = Aimag(cplSecHpmcSv(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+2089) = Real(cplSdcSdVG(i1,i2), dp) 
g(SumI+2090) = Aimag(cplSdcSdVG(i1,i2)) 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+2161) = Real(cplSucSuVG(i1,i2), dp) 
g(SumI+2162) = Aimag(cplSucSuVG(i1,i2)) 
End Do 
End Do 

g(2233) = Real(cplVGVGVG,dp)  
g(2234) = Aimag(cplVGVGVG)  
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+2235) = Real(cplcChaChaAhL(i1,i2,i3), dp) 
g(SumI+2236) = Aimag(cplcChaChaAhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+2259) = Real(cplcChaChaAhR(i1,i2,i3), dp) 
g(SumI+2260) = Aimag(cplcChaChaAhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
g(SumI+2283) = Real(cplChiChiAhL(i1,i2,i3), dp) 
g(SumI+2284) = Aimag(cplChiChiAhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
g(SumI+2433) = Real(cplChiChiAhR(i1,i2,i3), dp) 
g(SumI+2434) = Aimag(cplChiChiAhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2583) = Real(cplcFdFdAhL(i1,i2,i3), dp) 
g(SumI+2584) = Aimag(cplcFdFdAhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2637) = Real(cplcFdFdAhR(i1,i2,i3), dp) 
g(SumI+2638) = Aimag(cplcFdFdAhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2691) = Real(cplcFeFeAhL(i1,i2,i3), dp) 
g(SumI+2692) = Aimag(cplcFeFeAhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2745) = Real(cplcFeFeAhR(i1,i2,i3), dp) 
g(SumI+2746) = Aimag(cplcFeFeAhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2799) = Real(cplcFuFuAhL(i1,i2,i3), dp) 
g(SumI+2800) = Aimag(cplcFuFuAhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+2853) = Real(cplcFuFuAhR(i1,i2,i3), dp) 
g(SumI+2854) = Aimag(cplcFuFuAhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
g(SumI+2907) = Real(cplChiChacHpmL(i1,i2,i3), dp) 
g(SumI+2908) = Aimag(cplChiChacHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
g(SumI+2947) = Real(cplChiChacHpmR(i1,i2,i3), dp) 
g(SumI+2948) = Aimag(cplChiChacHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+2987) = Real(cplChaFucSdL(i1,i2,i3), dp) 
g(SumI+2988) = Aimag(cplChaFucSdL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+3059) = Real(cplChaFucSdR(i1,i2,i3), dp) 
g(SumI+3060) = Aimag(cplChaFucSdR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+3131) = Real(cplChaFvcSeL(i1,i2,i3), dp) 
g(SumI+3132) = Aimag(cplChaFvcSeL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+3203) = Real(cplChaFvcSeR(i1,i2,i3), dp) 
g(SumI+3204) = Aimag(cplChaFvcSeR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+3275) = Real(cplcChaChahhL(i1,i2,i3), dp) 
g(SumI+3276) = Aimag(cplcChaChahhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+3299) = Real(cplcChaChahhR(i1,i2,i3), dp) 
g(SumI+3300) = Aimag(cplcChaChahhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
g(SumI+3323) = Real(cplcFdChaSuL(i1,i2,i3), dp) 
g(SumI+3324) = Aimag(cplcFdChaSuL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
g(SumI+3395) = Real(cplcFdChaSuR(i1,i2,i3), dp) 
g(SumI+3396) = Aimag(cplcFdChaSuR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+3467) = Real(cplcFeChaSvL(i1,i2,i3), dp) 
g(SumI+3468) = Aimag(cplcFeChaSvL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
g(SumI+3503) = Real(cplcFeChaSvR(i1,i2,i3), dp) 
g(SumI+3504) = Aimag(cplcFeChaSvR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
g(SumI+3539) = Real(cplChiChihhL(i1,i2,i3), dp) 
g(SumI+3540) = Aimag(cplChiChihhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
g(SumI+3689) = Real(cplChiChihhR(i1,i2,i3), dp) 
g(SumI+3690) = Aimag(cplChiChihhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+3839) = Real(cplChiFdcSdL(i1,i2,i3), dp) 
g(SumI+3840) = Aimag(cplChiFdcSdL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+4019) = Real(cplChiFdcSdR(i1,i2,i3), dp) 
g(SumI+4020) = Aimag(cplChiFdcSdR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+4199) = Real(cplChiFecSeL(i1,i2,i3), dp) 
g(SumI+4200) = Aimag(cplChiFecSeL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+4379) = Real(cplChiFecSeR(i1,i2,i3), dp) 
g(SumI+4380) = Aimag(cplChiFecSeR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+4559) = Real(cplChiFucSuL(i1,i2,i3), dp) 
g(SumI+4560) = Aimag(cplChiFucSuL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+4739) = Real(cplChiFucSuR(i1,i2,i3), dp) 
g(SumI+4740) = Aimag(cplChiFucSuR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,5
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*10
SumI = SumI*2 
g(SumI+4919) = Real(cplcChaChiHpmL(i1,i2,i3), dp) 
g(SumI+4920) = Aimag(cplcChaChiHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,5
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*10
SumI = SumI*2 
g(SumI+4959) = Real(cplcChaChiHpmR(i1,i2,i3), dp) 
g(SumI+4960) = Aimag(cplcChaChiHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+4999) = Real(cplcFdChiSdL(i1,i2,i3), dp) 
g(SumI+5000) = Aimag(cplcFdChiSdL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+5179) = Real(cplcFdChiSdR(i1,i2,i3), dp) 
g(SumI+5180) = Aimag(cplcFdChiSdR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+5359) = Real(cplcFeChiSeL(i1,i2,i3), dp) 
g(SumI+5360) = Aimag(cplcFeChiSeL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+5539) = Real(cplcFeChiSeR(i1,i2,i3), dp) 
g(SumI+5540) = Aimag(cplcFeChiSeR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+5719) = Real(cplcFuChiSuL(i1,i2,i3), dp) 
g(SumI+5720) = Aimag(cplcFuChiSuL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
g(SumI+5899) = Real(cplcFuChiSuR(i1,i2,i3), dp) 
g(SumI+5900) = Aimag(cplcFuChiSuR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+6079) = Real(cplGluFdcSdL(i1,i2), dp) 
g(SumI+6080) = Aimag(cplGluFdcSdL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+6115) = Real(cplGluFdcSdR(i1,i2), dp) 
g(SumI+6116) = Aimag(cplGluFdcSdR(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6151) = Real(cplcFdFdhhL(i1,i2,i3), dp) 
g(SumI+6152) = Aimag(cplcFdFdhhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6205) = Real(cplcFdFdhhR(i1,i2,i3), dp) 
g(SumI+6206) = Aimag(cplcFdFdhhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+6259) = Real(cplcChaFdcSuL(i1,i2,i3), dp) 
g(SumI+6260) = Aimag(cplcChaFdcSuL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+6331) = Real(cplcChaFdcSuR(i1,i2,i3), dp) 
g(SumI+6332) = Aimag(cplcChaFdcSuR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6403) = Real(cplcFuFdcHpmL(i1,i2,i3), dp) 
g(SumI+6404) = Aimag(cplcFuFdcHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6439) = Real(cplcFuFdcHpmR(i1,i2,i3), dp) 
g(SumI+6440) = Aimag(cplcFuFdcHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6475) = Real(cplcFeFehhL(i1,i2,i3), dp) 
g(SumI+6476) = Aimag(cplcFeFehhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6529) = Real(cplcFeFehhR(i1,i2,i3), dp) 
g(SumI+6530) = Aimag(cplcFeFehhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6583) = Real(cplcChaFecSvL(i1,i2,i3), dp) 
g(SumI+6584) = Aimag(cplcChaFecSvL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6619) = Real(cplcChaFecSvR(i1,i2,i3), dp) 
g(SumI+6620) = Aimag(cplcChaFecSvR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6655) = Real(cplcFvFecHpmL(i1,i2,i3), dp) 
g(SumI+6656) = Aimag(cplcFvFecHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6691) = Real(cplcFvFecHpmR(i1,i2,i3), dp) 
g(SumI+6692) = Aimag(cplcFvFecHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+6727) = Real(cplGluFucSuL(i1,i2), dp) 
g(SumI+6728) = Aimag(cplGluFucSuL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+6763) = Real(cplGluFucSuR(i1,i2), dp) 
g(SumI+6764) = Aimag(cplGluFucSuR(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6799) = Real(cplcFuFuhhL(i1,i2,i3), dp) 
g(SumI+6800) = Aimag(cplcFuFuhhL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
g(SumI+6853) = Real(cplcFuFuhhR(i1,i2,i3), dp) 
g(SumI+6854) = Aimag(cplcFuFuhhR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6907) = Real(cplcFdFuHpmL(i1,i2,i3), dp) 
g(SumI+6908) = Aimag(cplcFdFuHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6943) = Real(cplcFdFuHpmR(i1,i2,i3), dp) 
g(SumI+6944) = Aimag(cplcFdFuHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+6979) = Real(cplcFeFvHpmL(i1,i2,i3), dp) 
g(SumI+6980) = Aimag(cplcFeFvHpmL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
g(SumI+7015) = Real(cplcFeFvHpmR(i1,i2,i3), dp) 
g(SumI+7016) = Aimag(cplcFeFvHpmR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+7051) = Real(cplcFdGluSdL(i1,i2), dp) 
g(SumI+7052) = Aimag(cplcFdGluSdL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+7087) = Real(cplcFdGluSdR(i1,i2), dp) 
g(SumI+7088) = Aimag(cplcFdGluSdR(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+7123) = Real(cplcFuGluSuL(i1,i2), dp) 
g(SumI+7124) = Aimag(cplcFuGluSuL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+7159) = Real(cplcFuGluSuR(i1,i2), dp) 
g(SumI+7160) = Aimag(cplcFuGluSuR(i1,i2)) 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+7195) = Real(cplcChacFuSdL(i1,i2,i3), dp) 
g(SumI+7196) = Aimag(cplcChacFuSdL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+7267) = Real(cplcChacFuSdR(i1,i2,i3), dp) 
g(SumI+7268) = Aimag(cplcChacFuSdR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+7339) = Real(cplcChacFvSeL(i1,i2,i3), dp) 
g(SumI+7340) = Aimag(cplcChacFvSeL(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+7411) = Real(cplcChacFvSeR(i1,i2,i3), dp) 
g(SumI+7412) = Aimag(cplcChacFvSeR(i1,i2,i3)) 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+7483) = Real(cplcFdFdVGL(i1,i2), dp) 
g(SumI+7484) = Aimag(cplcFdFdVGL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+7501) = Real(cplcFdFdVGR(i1,i2), dp) 
g(SumI+7502) = Aimag(cplcFdFdVGR(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+7519) = Real(cplcFuFuVGL(i1,i2), dp) 
g(SumI+7520) = Aimag(cplcFuFuVGL(i1,i2)) 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
g(SumI+7537) = Real(cplcFuFuVGR(i1,i2), dp) 
g(SumI+7538) = Aimag(cplcFuFuVGR(i1,i2)) 
End Do 
End Do 

g(7555) = Real(cplGluGluVGL,dp)  
g(7556) = Aimag(cplGluGluVGL)  
g(7557) = Real(cplGluGluVGR,dp)  
g(7558) = Aimag(cplGluGluVGR)  
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
g(SumI+7559) = Real(cplAhAhAhAh(i1,i2,i3,i4), dp) 
g(SumI+7560) = Aimag(cplAhAhAhAh(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
g(SumI+7721) = Real(cplAhAhhhhh(i1,i2,i3,i4), dp) 
g(SumI+7722) = Aimag(cplAhAhhhhh(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*12
SumI = SumI*2 
g(SumI+7883) = Real(cplAhAhHpmcHpm(i1,i2,i3,i4), dp) 
g(SumI+7884) = Aimag(cplAhAhHpmcHpm(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+7955) = Real(cplAhAhSdcSd(i1,i2,i3,i4), dp) 
g(SumI+7956) = Aimag(cplAhAhSdcSd(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+8603) = Real(cplAhAhSecSe(i1,i2,i3,i4), dp) 
g(SumI+8604) = Aimag(cplAhAhSecSe(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+9251) = Real(cplAhAhSucSu(i1,i2,i3,i4), dp) 
g(SumI+9252) = Aimag(cplAhAhSucSu(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
g(SumI+9899) = Real(cplhhhhhhhh(i1,i2,i3,i4), dp) 
g(SumI+9900) = Aimag(cplhhhhhhhh(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*12
SumI = SumI*2 
g(SumI+10061) = Real(cplhhhhHpmcHpm(i1,i2,i3,i4), dp) 
g(SumI+10062) = Aimag(cplhhhhHpmcHpm(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+10133) = Real(cplhhhhSdcSd(i1,i2,i3,i4), dp) 
g(SumI+10134) = Aimag(cplhhhhSdcSd(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+10781) = Real(cplhhhhSecSe(i1,i2,i3,i4), dp) 
g(SumI+10782) = Aimag(cplhhhhSecSe(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
g(SumI+11429) = Real(cplhhhhSucSu(i1,i2,i3,i4), dp) 
g(SumI+11430) = Aimag(cplhhhhSucSu(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*8
SumI = SumI*2 
g(SumI+12077) = Real(cplHpmHpmcHpmcHpm(i1,i2,i3,i4), dp) 
g(SumI+12078) = Aimag(cplHpmHpmcHpmcHpm(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
g(SumI+12109) = Real(cplHpmSdcHpmcSd(i1,i2,i3,i4), dp) 
g(SumI+12110) = Aimag(cplHpmSdcHpmcSd(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
g(SumI+12397) = Real(cplHpmSecHpmcSe(i1,i2,i3,i4), dp) 
g(SumI+12398) = Aimag(cplHpmSecHpmcSe(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
g(SumI+12685) = Real(cplHpmSucHpmcSu(i1,i2,i3,i4), dp) 
g(SumI+12686) = Aimag(cplHpmSucHpmcSu(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
g(SumI+12973) = Real(cplHpmSvcHpmcSv(i1,i2,i3,i4), dp) 
g(SumI+12974) = Aimag(cplHpmSvcHpmcSv(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
g(SumI+13045) = Real(cplSdSdcSdcSd(i1,i2,i3,i4), dp) 
g(SumI+13046) = Aimag(cplSdSdcSdcSd(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
g(SumI+15637) = Real(cplSdSecSdcSe(i1,i2,i3,i4), dp) 
g(SumI+15638) = Aimag(cplSdSecSdcSe(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
g(SumI+18229) = Real(cplSdSucSdcSu(i1,i2,i3,i4), dp) 
g(SumI+18230) = Aimag(cplSdSucSdcSu(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
g(SumI+20821) = Real(cplSeSecSecSe(i1,i2,i3,i4), dp) 
g(SumI+20822) = Aimag(cplSeSecSecSe(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*18 + (i1-1)*54
SumI = SumI*2 
g(SumI+23413) = Real(cplSeSvcSecSv(i1,i2,i3,i4), dp) 
g(SumI+23414) = Aimag(cplSeSvcSecSv(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
g(SumI+24061) = Real(cplSuSucSucSu(i1,i2,i3,i4), dp) 
g(SumI+24062) = Aimag(cplSuSucSucSu(i1,i2,i3,i4)) 
End Do 
End Do 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+26653) = Real(cplSdcSdVGVG(i1,i2), dp) 
g(SumI+26654) = Aimag(cplSdcSdVGVG(i1,i2)) 
End Do 
End Do 

Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
g(SumI+26725) = Real(cplSucSuVGVG(i1,i2), dp) 
g(SumI+26726) = Aimag(cplSucSuVGVG(i1,i2)) 
End Do 
End Do 

End Subroutine MassesCoupsToG

Subroutine GToMassesCoups(g,MSd,MSd2,MSv,MSv2,MSu,MSu2,MSe,MSe2,Mhh,Mhh2,             & 
& MAh,MAh2,MHpm,MHpm2,MChi,MChi2,MCha,MCha2,MFe,MFe2,MFd,MFd2,MFu,MFu2,MGlu,             & 
& MGlu2,MVZ,MVZ2,MVWm,MVWm2,cplAhAhAh,cplAhAhhh,cplAhhhhh,cplAhHpmcHpm,cplAhSdcSd,       & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplSdcSdVG,cplSucSuVG,               & 
& cplVGVGVG,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,           & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,cplcFdChiSdR,cplcFeChiSeL,     & 
& cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,          & 
& cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,       & 
& cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,      & 
& cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,           & 
& cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,        & 
& cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,         & 
& cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpmcHpm,          & 
& cplAhAhSdcSd,cplAhAhSecSe,cplAhAhSucSu,cplhhhhhhhh,cplhhhhHpmcHpm,cplhhhhSdcSd,        & 
& cplhhhhSecSe,cplhhhhSucSu,cplHpmHpmcHpmcHpm,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,           & 
& cplHpmSucHpmcSu,cplHpmSvcHpmcSv,cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,             & 
& cplSeSecSecSe,cplSeSvcSecSv,cplSuSucSucSu,cplSdcSdVGVG,cplSucSuVGVG)

Implicit None 
Real(dp), Intent(in) :: g(:) 
Integer :: i1,i2,i3,i4, sumI
Real(dp),Intent(inout) :: MSd(6),MSd2(6),MSv(3),MSv2(3),MSu(6),MSu2(6),MSe(6),MSe2(6),Mhh(3),Mhh2(3),           & 
& MAh(3),MAh2(3),MHpm(2),MHpm2(2),MChi(5),MChi2(5),MCha(2),MCha2(2),MFe(3),              & 
& MFe2(3),MFd(3),MFd2(3),MFu(3),MFu2(3),MGlu,MGlu2,MVZ,MVZ2,MVWm,MVWm2

Complex(dp),Intent(inout) :: cplAhAhAh(3,3,3),cplAhAhhh(3,3,3),cplAhhhhh(3,3,3),cplAhHpmcHpm(3,2,2),               & 
& cplAhSdcSd(3,6,6),cplAhSecSe(3,6,6),cplAhSucSu(3,6,6),cplhhhhhh(3,3,3),cplhhHpmcHpm(3,2,2),& 
& cplhhSdcSd(3,6,6),cplhhSecSe(3,6,6),cplhhSucSu(3,6,6),cplHpmSucSd(2,6,6),              & 
& cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),            & 
& cplSucSuVG(6,6),cplVGVGVG,cplcChaChaAhL(2,2,3),cplcChaChaAhR(2,2,3),cplChiChiAhL(5,5,3),& 
& cplChiChiAhR(5,5,3),cplcFdFdAhL(3,3,3),cplcFdFdAhR(3,3,3),cplcFeFeAhL(3,3,3),          & 
& cplcFeFeAhR(3,3,3),cplcFuFuAhL(3,3,3),cplcFuFuAhR(3,3,3),cplChiChacHpmL(5,2,2),        & 
& cplChiChacHpmR(5,2,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplcChaChahhL(2,2,3),cplcChaChahhR(2,2,3),cplcFdChaSuL(3,2,6),     & 
& cplcFdChaSuR(3,2,6),cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiChihhL(5,5,3),       & 
& cplChiChihhR(5,5,3),cplChiFdcSdL(5,3,6),cplChiFdcSdR(5,3,6),cplChiFecSeL(5,3,6),       & 
& cplChiFecSeR(5,3,6),cplChiFucSuL(5,3,6),cplChiFucSuR(5,3,6),cplcChaChiHpmL(2,5,2),     & 
& cplcChaChiHpmR(2,5,2),cplcFdChiSdL(3,5,6),cplcFdChiSdR(3,5,6),cplcFeChiSeL(3,5,6),     & 
& cplcFeChiSeR(3,5,6),cplcFuChiSuL(3,5,6),cplcFuChiSuR(3,5,6),cplGluFdcSdL(3,6),         & 
& cplGluFdcSdR(3,6),cplcFdFdhhL(3,3,3),cplcFdFdhhR(3,3,3),cplcChaFdcSuL(2,3,6),          & 
& cplcChaFdcSuR(2,3,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,3),     & 
& cplcFeFehhR(3,3,3),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),     & 
& cplcFvFecHpmR(3,3,2),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,3),           & 
& cplcFuFuhhR(3,3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),        & 
& cplcFeFvHpmR(3,3,2),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),             & 
& cplcFuGluSuR(3,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),               & 
& cplcFuFuVGR(3,3),cplGluGluVGL,cplGluGluVGR

Complex(dp),Intent(inout) :: cplAhAhAhAh(3,3,3,3),cplAhAhhhhh(3,3,3,3),cplAhAhHpmcHpm(3,3,2,2),cplAhAhSdcSd(3,3,6,6),& 
& cplAhAhSecSe(3,3,6,6),cplAhAhSucSu(3,3,6,6),cplhhhhhhhh(3,3,3,3),cplhhhhHpmcHpm(3,3,2,2),& 
& cplhhhhSdcSd(3,3,6,6),cplhhhhSecSe(3,3,6,6),cplhhhhSucSu(3,3,6,6),cplHpmHpmcHpmcHpm(2,2,2,2),& 
& cplHpmSdcHpmcSd(2,6,2,6),cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),            & 
& cplHpmSvcHpmcSv(2,3,2,3),cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6),cplSdcSdVGVG(6,6),& 
& cplSucSuVGVG(6,6)

MSd=g(1:6) 
MSd2=g(7:12) 
MSv=g(13:15) 
MSv2=g(16:18) 
MSu=g(19:24) 
MSu2=g(25:30) 
MSe=g(31:36) 
MSe2=g(37:42) 
Mhh=g(43:45) 
Mhh2=g(46:48) 
MAh=g(49:51) 
MAh2=g(52:54) 
MHpm=g(55:56) 
MHpm2=g(57:58) 
MChi=g(59:63) 
MChi2=g(64:68) 
MCha=g(69:70) 
MCha2=g(71:72) 
MFe=g(73:75) 
MFe2=g(76:78) 
MFd=g(79:81) 
MFd2=g(82:84) 
MFu=g(85:87) 
MFu2=g(88:90) 
MGlu=g(91) 
MGlu2=g(92) 
MVZ=g(93) 
MVZ2=g(94) 
MVWm=g(95) 
MVWm2=g(96) 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplAhAhAh(i1,i2,i3) = Cmplx( g(SumI+97), g(SumI+98), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplAhAhhh(i1,i2,i3) = Cmplx( g(SumI+151), g(SumI+152), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplAhhhhh(i1,i2,i3) = Cmplx( g(SumI+205), g(SumI+206), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
cplAhHpmcHpm(i1,i2,i3) = Cmplx( g(SumI+259), g(SumI+260), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplAhSdcSd(i1,i2,i3) = Cmplx( g(SumI+283), g(SumI+284), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplAhSecSe(i1,i2,i3) = Cmplx( g(SumI+499), g(SumI+500), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplAhSucSu(i1,i2,i3) = Cmplx( g(SumI+715), g(SumI+716), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplhhhhhh(i1,i2,i3) = Cmplx( g(SumI+931), g(SumI+932), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
cplhhHpmcHpm(i1,i2,i3) = Cmplx( g(SumI+985), g(SumI+986), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplhhSdcSd(i1,i2,i3) = Cmplx( g(SumI+1009), g(SumI+1010), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplhhSecSe(i1,i2,i3) = Cmplx( g(SumI+1225), g(SumI+1226), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplhhSucSu(i1,i2,i3) = Cmplx( g(SumI+1441), g(SumI+1442), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*36
SumI = SumI*2 
cplHpmSucSd(i1,i2,i3) = Cmplx( g(SumI+1657), g(SumI+1658), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplHpmSvcSe(i1,i2,i3) = Cmplx( g(SumI+1801), g(SumI+1802), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
cplSdcHpmcSu(i1,i2,i3) = Cmplx( g(SumI+1873), g(SumI+1874), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplSecHpmcSv(i1,i2,i3) = Cmplx( g(SumI+2017), g(SumI+2018), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplSdcSdVG(i1,i2) = Cmplx( g(SumI+2089), g(SumI+2090), dp) 
End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplSucSuVG(i1,i2) = Cmplx( g(SumI+2161), g(SumI+2162), dp) 
End Do 
 End Do 
 
cplVGVGVG= Cmplx(g(2233),g(2234),dp) 
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcChaChaAhL(i1,i2,i3) = Cmplx( g(SumI+2235), g(SumI+2236), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcChaChaAhR(i1,i2,i3) = Cmplx( g(SumI+2259), g(SumI+2260), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
cplChiChiAhL(i1,i2,i3) = Cmplx( g(SumI+2283), g(SumI+2284), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
cplChiChiAhR(i1,i2,i3) = Cmplx( g(SumI+2433), g(SumI+2434), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFdFdAhL(i1,i2,i3) = Cmplx( g(SumI+2583), g(SumI+2584), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFdFdAhR(i1,i2,i3) = Cmplx( g(SumI+2637), g(SumI+2638), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFeFeAhL(i1,i2,i3) = Cmplx( g(SumI+2691), g(SumI+2692), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFeFeAhR(i1,i2,i3) = Cmplx( g(SumI+2745), g(SumI+2746), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFuFuAhL(i1,i2,i3) = Cmplx( g(SumI+2799), g(SumI+2800), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFuFuAhR(i1,i2,i3) = Cmplx( g(SumI+2853), g(SumI+2854), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
cplChiChacHpmL(i1,i2,i3) = Cmplx( g(SumI+2907), g(SumI+2908), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,2
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*4
SumI = SumI*2 
cplChiChacHpmR(i1,i2,i3) = Cmplx( g(SumI+2947), g(SumI+2948), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChaFucSdL(i1,i2,i3) = Cmplx( g(SumI+2987), g(SumI+2988), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChaFucSdR(i1,i2,i3) = Cmplx( g(SumI+3059), g(SumI+3060), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChaFvcSeL(i1,i2,i3) = Cmplx( g(SumI+3131), g(SumI+3132), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChaFvcSeR(i1,i2,i3) = Cmplx( g(SumI+3203), g(SumI+3204), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcChaChahhL(i1,i2,i3) = Cmplx( g(SumI+3275), g(SumI+3276), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcChaChahhR(i1,i2,i3) = Cmplx( g(SumI+3299), g(SumI+3300), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
cplcFdChaSuL(i1,i2,i3) = Cmplx( g(SumI+3323), g(SumI+3324), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*12
SumI = SumI*2 
cplcFdChaSuR(i1,i2,i3) = Cmplx( g(SumI+3395), g(SumI+3396), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcFeChaSvL(i1,i2,i3) = Cmplx( g(SumI+3467), g(SumI+3468), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,2
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*6
SumI = SumI*2 
cplcFeChaSvR(i1,i2,i3) = Cmplx( g(SumI+3503), g(SumI+3504), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
cplChiChihhL(i1,i2,i3) = Cmplx( g(SumI+3539), g(SumI+3540), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,5
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*15
SumI = SumI*2 
cplChiChihhR(i1,i2,i3) = Cmplx( g(SumI+3689), g(SumI+3690), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFdcSdL(i1,i2,i3) = Cmplx( g(SumI+3839), g(SumI+3840), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFdcSdR(i1,i2,i3) = Cmplx( g(SumI+4019), g(SumI+4020), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFecSeL(i1,i2,i3) = Cmplx( g(SumI+4199), g(SumI+4200), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFecSeR(i1,i2,i3) = Cmplx( g(SumI+4379), g(SumI+4380), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFucSuL(i1,i2,i3) = Cmplx( g(SumI+4559), g(SumI+4560), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,5
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplChiFucSuR(i1,i2,i3) = Cmplx( g(SumI+4739), g(SumI+4740), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,5
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*10
SumI = SumI*2 
cplcChaChiHpmL(i1,i2,i3) = Cmplx( g(SumI+4919), g(SumI+4920), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,5
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*10
SumI = SumI*2 
cplcChaChiHpmR(i1,i2,i3) = Cmplx( g(SumI+4959), g(SumI+4960), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFdChiSdL(i1,i2,i3) = Cmplx( g(SumI+4999), g(SumI+5000), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFdChiSdR(i1,i2,i3) = Cmplx( g(SumI+5179), g(SumI+5180), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFeChiSeL(i1,i2,i3) = Cmplx( g(SumI+5359), g(SumI+5360), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFeChiSeR(i1,i2,i3) = Cmplx( g(SumI+5539), g(SumI+5540), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFuChiSuL(i1,i2,i3) = Cmplx( g(SumI+5719), g(SumI+5720), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,5
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*30
SumI = SumI*2 
cplcFuChiSuR(i1,i2,i3) = Cmplx( g(SumI+5899), g(SumI+5900), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplGluFdcSdL(i1,i2) = Cmplx( g(SumI+6079), g(SumI+6080), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplGluFdcSdR(i1,i2) = Cmplx( g(SumI+6115), g(SumI+6116), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFdFdhhL(i1,i2,i3) = Cmplx( g(SumI+6151), g(SumI+6152), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFdFdhhR(i1,i2,i3) = Cmplx( g(SumI+6205), g(SumI+6206), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChaFdcSuL(i1,i2,i3) = Cmplx( g(SumI+6259), g(SumI+6260), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChaFdcSuR(i1,i2,i3) = Cmplx( g(SumI+6331), g(SumI+6332), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFuFdcHpmL(i1,i2,i3) = Cmplx( g(SumI+6403), g(SumI+6404), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFuFdcHpmR(i1,i2,i3) = Cmplx( g(SumI+6439), g(SumI+6440), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFeFehhL(i1,i2,i3) = Cmplx( g(SumI+6475), g(SumI+6476), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFeFehhR(i1,i2,i3) = Cmplx( g(SumI+6529), g(SumI+6530), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcChaFecSvL(i1,i2,i3) = Cmplx( g(SumI+6583), g(SumI+6584), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcChaFecSvR(i1,i2,i3) = Cmplx( g(SumI+6619), g(SumI+6620), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFvFecHpmL(i1,i2,i3) = Cmplx( g(SumI+6655), g(SumI+6656), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFvFecHpmR(i1,i2,i3) = Cmplx( g(SumI+6691), g(SumI+6692), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplGluFucSuL(i1,i2) = Cmplx( g(SumI+6727), g(SumI+6728), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplGluFucSuR(i1,i2) = Cmplx( g(SumI+6763), g(SumI+6764), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFuFuhhL(i1,i2,i3) = Cmplx( g(SumI+6799), g(SumI+6800), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
SumI = (i3-1) + (i2-1)*3 + (i1-1)*9
SumI = SumI*2 
cplcFuFuhhR(i1,i2,i3) = Cmplx( g(SumI+6853), g(SumI+6854), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFdFuHpmL(i1,i2,i3) = Cmplx( g(SumI+6907), g(SumI+6908), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFdFuHpmR(i1,i2,i3) = Cmplx( g(SumI+6943), g(SumI+6944), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFeFvHpmL(i1,i2,i3) = Cmplx( g(SumI+6979), g(SumI+6980), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
SumI = (i3-1) + (i2-1)*2 + (i1-1)*6
SumI = SumI*2 
cplcFeFvHpmR(i1,i2,i3) = Cmplx( g(SumI+7015), g(SumI+7016), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplcFdGluSdL(i1,i2) = Cmplx( g(SumI+7051), g(SumI+7052), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplcFdGluSdR(i1,i2) = Cmplx( g(SumI+7087), g(SumI+7088), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplcFuGluSuL(i1,i2) = Cmplx( g(SumI+7123), g(SumI+7124), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplcFuGluSuR(i1,i2) = Cmplx( g(SumI+7159), g(SumI+7160), dp) 
End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChacFuSdL(i1,i2,i3) = Cmplx( g(SumI+7195), g(SumI+7196), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChacFuSdR(i1,i2,i3) = Cmplx( g(SumI+7267), g(SumI+7268), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChacFvSeL(i1,i2,i3) = Cmplx( g(SumI+7339), g(SumI+7340), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,6
SumI = (i3-1) + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplcChacFvSeR(i1,i2,i3) = Cmplx( g(SumI+7411), g(SumI+7412), dp) 
End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
cplcFdFdVGL(i1,i2) = Cmplx( g(SumI+7483), g(SumI+7484), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
cplcFdFdVGR(i1,i2) = Cmplx( g(SumI+7501), g(SumI+7502), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
cplcFuFuVGL(i1,i2) = Cmplx( g(SumI+7519), g(SumI+7520), dp) 
End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
SumI = (i2-1) + (i1-1)*3
SumI = SumI*2 
cplcFuFuVGR(i1,i2) = Cmplx( g(SumI+7537), g(SumI+7538), dp) 
End Do 
 End Do 
 
cplGluGluVGL= Cmplx(g(7555),g(7556),dp) 
cplGluGluVGR= Cmplx(g(7557),g(7558),dp) 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
cplAhAhAhAh(i1,i2,i3,i4) = Cmplx( g(SumI+7559), g(SumI+7560), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
cplAhAhhhhh(i1,i2,i3,i4) = Cmplx( g(SumI+7721), g(SumI+7722), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*12
SumI = SumI*2 
cplAhAhHpmcHpm(i1,i2,i3,i4) = Cmplx( g(SumI+7883), g(SumI+7884), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplAhAhSdcSd(i1,i2,i3,i4) = Cmplx( g(SumI+7955), g(SumI+7956), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplAhAhSecSe(i1,i2,i3,i4) = Cmplx( g(SumI+8603), g(SumI+8604), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplAhAhSucSu(i1,i2,i3,i4) = Cmplx( g(SumI+9251), g(SumI+9252), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,3
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*9 + (i1-1)*27
SumI = SumI*2 
cplhhhhhhhh(i1,i2,i3,i4) = Cmplx( g(SumI+9899), g(SumI+9900), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*12
SumI = SumI*2 
cplhhhhHpmcHpm(i1,i2,i3,i4) = Cmplx( g(SumI+10061), g(SumI+10062), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplhhhhSdcSd(i1,i2,i3,i4) = Cmplx( g(SumI+10133), g(SumI+10134), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplhhhhSecSe(i1,i2,i3,i4) = Cmplx( g(SumI+10781), g(SumI+10782), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,3
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*108
SumI = SumI*2 
cplhhhhSucSu(i1,i2,i3,i4) = Cmplx( g(SumI+11429), g(SumI+11430), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,2
Do i3 = 1,2
Do i4 = 1,2
SumI = (i4-1) + (i3-1)*2 + (i2-1)*4 + (i1-1)*8
SumI = SumI*2 
cplHpmHpmcHpmcHpm(i1,i2,i3,i4) = Cmplx( g(SumI+12077), g(SumI+12078), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
cplHpmSdcHpmcSd(i1,i2,i3,i4) = Cmplx( g(SumI+12109), g(SumI+12110), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
cplHpmSecHpmcSe(i1,i2,i3,i4) = Cmplx( g(SumI+12397), g(SumI+12398), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,6
Do i3 = 1,2
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*12 + (i1-1)*72
SumI = SumI*2 
cplHpmSucHpmcSu(i1,i2,i3,i4) = Cmplx( g(SumI+12685), g(SumI+12686), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,2
Do i2 = 1,3
Do i3 = 1,2
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*6 + (i1-1)*18
SumI = SumI*2 
cplHpmSvcHpmcSv(i1,i2,i3,i4) = Cmplx( g(SumI+12973), g(SumI+12974), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
cplSdSdcSdcSd(i1,i2,i3,i4) = Cmplx( g(SumI+13045), g(SumI+13046), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
cplSdSecSdcSe(i1,i2,i3,i4) = Cmplx( g(SumI+15637), g(SumI+15638), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
cplSdSucSdcSu(i1,i2,i3,i4) = Cmplx( g(SumI+18229), g(SumI+18230), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
cplSeSecSecSe(i1,i2,i3,i4) = Cmplx( g(SumI+20821), g(SumI+20822), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,3
Do i3 = 1,6
Do i4 = 1,3
SumI = (i4-1) + (i3-1)*3 + (i2-1)*18 + (i1-1)*54
SumI = SumI*2 
cplSeSvcSecSv(i1,i2,i3,i4) = Cmplx( g(SumI+23413), g(SumI+23414), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
Do i3 = 1,6
Do i4 = 1,6
SumI = (i4-1) + (i3-1)*6 + (i2-1)*36 + (i1-1)*216
SumI = SumI*2 
cplSuSucSucSu(i1,i2,i3,i4) = Cmplx( g(SumI+24061), g(SumI+24062), dp) 
End Do 
 End Do 
 End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplSdcSdVGVG(i1,i2) = Cmplx( g(SumI+26653), g(SumI+26654), dp) 
End Do 
 End Do 
 
Do i1 = 1,6
Do i2 = 1,6
SumI = (i2-1) + (i1-1)*6
SumI = SumI*2 
cplSucSuVGVG(i1,i2) = Cmplx( g(SumI+26725), g(SumI+26726), dp) 
End Do 
 End Do 
 
End Subroutine GToMassesCoups

End Module EffectivePotential_NMSSM 
 
