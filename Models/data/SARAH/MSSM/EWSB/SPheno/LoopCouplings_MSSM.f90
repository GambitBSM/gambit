! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 14:59 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Module LoopCouplings_MSSM 
 
Use Control 
Use Couplings_MSSM 
Use Mathematics 
Use LoopFunctions 
Use StandardModel 
 
 Contains 
 
Real(dp) Function Alpha_MSbar(Q,mW,mt) 
Implicit None 
Real(dp),Intent(in)::Q,mW 
Real(dp),Intent(in),Optional::mt 
Real(dp)::DeltaAlpha 
If (MZ_input) Then 
Alpha_MSbar=Alpha_mZ_MS 
If (Present(mt)) Then 
DeltaAlpha=-8._dp*Log(Q/mt)/(9._dp*Pi) 
Alpha_MSbar=Alpha_MSbar/(1._dp+DeltaAlpha*alpha) 
End If 
Else 
DeltaAlpha=3.5_dp*Log(Q/mW)/Pi+0.5_dp*oo3pi 
If (Present(mt)) DeltaAlpha=DeltaAlpha-8._dp*Log(Q/mt)/(9._dp*Pi) 
Alpha_MSbar=Alpha/(1._dp-Delta_Alpha_Lepton-Delta_Alpha_Hadron& 
&+DeltaAlpha*alpha) 
Alpha_MZ_MS=Alpha_MSbar 
End If 
End Function Alpha_MSbar
 
 
Real(dp) Function AlphaEwDR(Q,MVWm,MSd,MSu,MSe,MHpm,MCha,MFe,MFd,MFu) 
 
Real(dp),Intent(in)::Q,MVWm,MSd(6),MSu(6),MSe(6),MHpm(2),MCha(2),MFe(3),MFd(3),MFu(3)
Integer::i1 
Real(dp)::DeltaAlpha 
If (MZ_input) then 
DeltaAlpha=1._dp-Alpha/Alpha_MZ_MS! MSbar value^=mW+light fermions 
DeltaAlpha=DeltaAlpha+alpha/(6._dp*Pi)! conversion to DRbar 
If (MVWm.gt.Q) Then 
DeltaAlpha=DeltaAlpha-1._dp/3._dp*Log(MVWm/ Q)*Alpha/(2._dp*pi) 
End if 
Do i1=1,6
If (MSd(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-1._dp/9._dp*Log(MSd(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,6
If (MSu(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-4._dp/9._dp*Log(MSu(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,6
If (MSe(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-1._dp/3._dp*Log(MSe(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=2,2
If (MHpm(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-1._dp/3._dp*Log(MHpm(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,2
If (MCha(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-4._dp/3._dp*Log(MCha(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,3
If (MFe(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-4._dp/3._dp*Log(MFe(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,3
If (MFd(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-4._dp/9._dp*Log(MFd(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Do i1=1,3
If (MFu(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha-16._dp/9._dp*Log(MFu(i1)/ Q)*Alpha/(2._dp*pi)  
End if 
End Do 
Else 
DeltaAlpha=7._dp*Log(Q/mW) !+16._dp*Log(mf_u(3)/Q)/9._dp 
If (MVWm.gt.Q) Then 
DeltaAlpha=DeltaAlpha+1._dp/3._dp*Log(MVWm/ Q)
End if 
Do i1=1,6
If (MSd(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+1._dp/9._dp*Log(MSd(i1)/ Q) 
End if 
End Do 
Do i1=1,6
If (MSu(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+4._dp/9._dp*Log(MSu(i1)/ Q) 
End if 
End Do 
Do i1=1,6
If (MSe(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+1._dp/3._dp*Log(MSe(i1)/ Q) 
End if 
End Do 
Do i1=2,2
If (MHpm(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+1._dp/3._dp*Log(MHpm(i1)/ Q) 
End if 
End Do 
Do i1=1,2
If (MCha(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+4._dp/3._dp*Log(MCha(i1)/ Q) 
End if 
End Do 
Do i1=1,3
If (MFe(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+4._dp/3._dp*Log(MFe(i1)/ Q) 
End if 
End Do 
Do i1=1,3
If (MFd(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+4._dp/9._dp*Log(MFd(i1)/ Q) 
End if 
End Do 
Do i1=1,3
If (MFu(i1).gt.Q) Then 
DeltaAlpha=DeltaAlpha+16._dp/9._dp*Log(MFu(i1)/ Q) 
End if 
End Do 
DeltaAlpha=Delta_Alpha_Lepton+Delta_Alpha_Hadron& 
    &-alpha*DeltaAlpha/(2._dp*Pi) 
End If 
 
AlphaEwDR=Alpha/(1._dp-DeltaAlpha) 
 
End Function AlphaEwDR 
 
 
Real(dp) Function AlphaSDR(Q,MSd,MSu,MGlu,MFd,MFu) 
Real(dp),Intent(in)::Q,MSd(6),MSu(6),MGlu,MFd(3),MFu(3) 
Integer::i1 
Real(dp)::DeltaAlpha 
DeltaAlpha = 0.5_dp !- 2._dp*Log(sqrt(mf_u2(3))/Q)/3._dp 
Do i1=1,6
 If (Abs(MSd(i1)/ Q).gt.1._dp) Then 
  DeltaAlpha=DeltaAlpha-1._dp/6._dp*Log(MSd(i1)/ Q) 
 End If 
End Do 
Do i1=1,6
 If (Abs(MSu(i1)/ Q).gt.1._dp) Then 
  DeltaAlpha=DeltaAlpha-1._dp/6._dp*Log(MSu(i1)/ Q) 
 End If 
End Do 
DeltaAlpha=DeltaAlpha-2*Log(MGlu/ Q) 
Do i1=1,3
 If (Abs(MFd(i1)/ Q).gt.1._dp) Then 
  DeltaAlpha=DeltaAlpha-2._dp/3._dp*Log(MFd(i1)/ Q) 
 End If 
End Do 
Do i1=1,3
 If (Abs(MFu(i1)/ Q).gt.1._dp) Then 
  DeltaAlpha=DeltaAlpha-2._dp/3._dp*Log(MFu(i1)/ Q) 
 End If 
End Do 
DeltaAlpha=AlphaS_mZ*DeltaAlpha/(2._dp*Pi) 
   AlphaSDR=AlphaS_mZ/(1._dp-DeltaAlpha)
 
End Function AlphaSDR 
Real(dp) Function AlphaEW_T(AlphaEW_In, Q,MVWm,MSd,MSu,MSe,MHpm,MCha,MFe,MFd,MFu) 
 
Real(dp),Intent(in)::AlphaEW_In, Q,MVWm,MSd(6),MSu(6),MSe(6),MHpm(2),MCha(2),MFe(3),MFd(3),MFu(3)
Integer::i1 
Real(dp)::DeltaAlpha 
DeltaAlpha=1._dp/6._dp 
Do i1=1,6
DeltaAlpha=DeltaAlpha+1._dp/9._dp*Log(MSd(i1)/ Q) 
End Do 
Do i1=1,6
DeltaAlpha=DeltaAlpha+4._dp/9._dp*Log(MSu(i1)/ Q) 
End Do 
Do i1=1,6
DeltaAlpha=DeltaAlpha+1._dp/3._dp*Log(MSe(i1)/ Q) 
End Do 
Do i1=2,2
DeltaAlpha=DeltaAlpha+1._dp/3._dp*Log(MHpm(i1)/ Q) 
End Do 
Do i1=1,2
DeltaAlpha=DeltaAlpha+4._dp/3._dp*Log(MCha(i1)/ Q) 
End Do 
DeltaAlpha=-alpha_in*DeltaAlpha/(2._dp*Pi) 
AlphaEW_T=Alpha_in/(1._dp-DeltaAlpha) 
 
End Function AlphaEW_T 
 
 
Real(dp) Function AlphaS_T(AlphaS_In, Q,MSd,MSu,MGlu,MFd,MFu) 
Real(dp),Intent(in):: AlphaS_In, Q,MSd(6),MSu(6),MGlu,MFd(3),MFu(3) 
Integer::i1 
Real(dp)::DeltaAlpha 
DeltaAlpha = 0.5_dp 
Do i1=1,6
 If (Abs(MSd(i1)/mf_u(3)).gt.1._dp) Then 
DeltaAlpha=DeltaAlpha-1._dp/6._dp*Log(MSd(i1)/ Q) 
 End If 
End Do 
Do i1=1,6
 If (Abs(MSu(i1)/mf_u(3)).gt.1._dp) Then 
DeltaAlpha=DeltaAlpha-1._dp/6._dp*Log(MSu(i1)/ Q) 
 End If 
End Do 
DeltaAlpha=DeltaAlpha-2*Log(MGlu/ Q) 
Do i1=1,3
 If (Abs(MFd(i1)/mf_u(3)).gt.1._dp) Then 
DeltaAlpha=DeltaAlpha-2._dp/3._dp*Log(MFd(i1)/ Q) 
 End If 
End Do 
Do i1=1,3
 If (Abs(MFu(i1)/mf_u(3)).gt.1._dp) Then 
DeltaAlpha=DeltaAlpha-2._dp/3._dp*Log(MFu(i1)/ Q) 
 End If 
End Do 
DeltaAlpha=AlphaS_In*DeltaAlpha/(2._dp*Pi) 
   AlphaS_T=AlphaS_In/(1._dp-DeltaAlpha)
 
End Function AlphaS_T



Subroutine DeltaVB(sinW2,sinW2_dr,rho,MAh,MCha,MChi,MFe,Mhh,MHpm,MSe,MSv,             & 
& MVWm,g1,g2,UM,UP,vd,vu,Ye,ZA,ZE,ZEL,ZER,ZH,ZN,ZP,ZV,res)

Implicit None 
Real(dp),Intent(in) :: MAh(2),MCha(2),MChi(4),MFe(3),Mhh(2),MHpm(2),MSe(6),MSv(3),MVWm,g1,g2,vd,             & 
& vu,ZA(2,2),ZH(2,2),ZP(2,2)

Complex(dp),Intent(in) :: UM(2,2),UP(2,2),Ye(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),ZN(4,4),ZV(3,3)

Real(dp) :: MAh2(2),MCha2(2),MChi2(4),MFe2(3),Mhh2(2),MHpm2(2),MSe2(6),MSv2(3),MVWm2

Complex(dp) :: cplAhcHpmVWm(2,2),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),cplcChaChiVWmL(2,4),      & 
& cplcChaChiVWmR(2,4),cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFeChaSvL(3,2,3),     & 
& cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),cplcFeFeAhL(3,3,2),        & 
& cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),cplcFeFvHpmL(3,3,2),          & 
& cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFvChiSvL(3,4,3),           & 
& cplcFvChiSvR(3,4,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplChaFvcSeL(2,3,6),     & 
& cplChaFvcSeR(2,3,6),cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),cplChiFvcSvL(4,3,3),       & 
& cplChiFvcSvR(4,3,3),cplhhcHpmVWm(2,2),cplhhcVWmVWm(2),cplSvcSeVWm(3,6)

Integer :: i1,i2,i3,i4,gt1,gt2,gt3,gt4 
Real(dp), Intent(in) :: sinW2,sinW2_Dr, rho 
Real(dp), Intent(out) :: res 
 
Complex(dp) :: sumI, coup1L,coup1R,coup2L,coup2R,coup3L,coup3R,coup3, coup4L,coup4R, teil 
Complex(dp) :: D27m2, D0m2, vertex, phase 
Real(dp) :: cosW2, cosW2_Dr, chargefactor 
Iname = Iname+1
NameOfUnit(Iname) = "DeltaVB" 
MAh2 = MAh**2 
MCha2 = MCha**2 
MChi2 = MChi**2 
MFe2 = MFe**2 
Mhh2 = Mhh**2 
MHpm2 = MHpm**2 
MSe2 = MSe**2 
MSv2 = MSv**2 
MVWm2 = MVWm**2 

 
 ! Fix neutrino phases 
 
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


cplAhcHpmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplingAhcHpmVWmT(gt1,gt2,g2,ZA,ZP,cplAhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplChaFvcSeL = 0._dp 
cplChaFvcSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChaFvcSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplChaFvcSeL(gt1,gt2,gt3)              & 
& ,cplChaFvcSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChaSvL = 0._dp 
cplcFeChaSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 2
  Do gt3 = 1, 3
Call CouplingcFeChaSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcFeChaSvL(gt1,gt2,gt3)   & 
& ,cplcFeChaSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFecSeL = 0._dp 
cplChiFecSeR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingChiFecSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplChiFecSeL(gt1,gt2,gt3)   & 
& ,cplChiFecSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplChiFvcSvL = 0._dp 
cplChiFvcSvR = 0._dp 
Do gt1 = 1, 4
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingChiFvcSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplChiFvcSvL(gt1,gt2,gt3)              & 
& ,cplChiFvcSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFeChiSeL = 0._dp 
cplcFeChiSeR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 6
Call CouplingcFeChiSeT(gt1,gt2,gt3,g1,g2,Ye,ZE,ZN,ZEL,ZER,cplcFeChiSeL(gt1,gt2,gt3)   & 
& ,cplcFeChiSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcFvChiSvL = 0._dp 
cplcFvChiSvR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 4
  Do gt3 = 1, 3
Call CouplingcFvChiSvT(gt1,gt2,gt3,g1,g2,ZV,ZN,cplcFvChiSvL(gt1,gt2,gt3)              & 
& ,cplcFvChiSvR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplcChaChiVWmL = 0._dp 
cplcChaChiVWmR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 4
Call CouplingcChaChiVWmT(gt1,gt2,g2,ZN,UM,UP,cplcChaChiVWmL(gt1,gt2),cplcChaChiVWmR(gt1,gt2))

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


cplcChaFecSvL = 0._dp 
cplcChaFecSvR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 3
Call CouplingcChaFecSvT(gt1,gt2,gt3,g2,Ye,ZV,UM,UP,ZEL,ZER,cplcChaFecSvL(gt1,gt2,gt3) & 
& ,cplcChaFecSvR(gt1,gt2,gt3))

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


cplcFeFvVWmL = 0._dp 
cplcFeFvVWmR = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 3
Call CouplingcFeFvVWmT(gt1,gt2,g2,ZEL,cplcFeFvVWmL(gt1,gt2),cplcFeFvVWmR(gt1,gt2))

 End Do 
End Do 


cplhhcHpmVWm = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 2
Call CouplinghhcHpmVWmT(gt1,gt2,g2,ZH,ZP,cplhhcHpmVWm(gt1,gt2))

 End Do 
End Do 


cplhhcVWmVWm = 0._dp 
Do gt1 = 1, 2
Call CouplinghhcVWmVWmT(gt1,g2,vd,vu,ZH,cplhhcVWmVWm(gt1))

End Do 


cplcChacFvSeL = 0._dp 
cplcChacFvSeR = 0._dp 
Do gt1 = 1, 2
 Do gt2 = 1, 3
  Do gt3 = 1, 6
Call CouplingcChacFvSeT(gt1,gt2,gt3,g2,Ye,ZE,UM,cplcChacFvSeL(gt1,gt2,gt3)            & 
& ,cplcChacFvSeR(gt1,gt2,gt3))

  End Do 
 End Do 
End Do 


cplSvcSeVWm = 0._dp 
Do gt1 = 1, 3
 Do gt2 = 1, 6
Call CouplingSvcSeVWmT(gt1,gt2,g2,ZV,ZE,cplSvcSeVWm(gt1,gt2))

 End Do 
End Do 


!-------------------------- 
!SM Contributions 
!-------------------------- 
cosW2 = 1._dp - sinW2 
cosW2_DR = 1._dp - sinW2_DR 
sumI = 6._dp & 
  & + Log(cosW2)*(3.5_dp - 2.5_dp *sinW2   & 
  & - sinW2_DR*(5._dp - 1.5_dp*cosW2/cosW2_DR))/sinW2   
res = sumI*g2**2*rho 
 
 
If (IncludeBSMdeltaVB) Then 
!-------------------------- 
!BSM  Contributions 
!-------------------------- 
teil = 0._dp 
 
Do gt1=1,3 
 Do gt2=1,3 
sumI = 0._dp 
 
chargefactor = 1 
Do i1=1,2
  Do i2=1,6
If ((MCha2(i1).gt.mf_l2(2)).Or.(MSe2(i2).gt.mf_l2(2))) Then
coup1L = cplChaFvcSeL(i1,gt1,i2)
coup1R = cplChaFvcSeR(i1,gt1,i2)
coup2R = Conjg(cplChaFvcSeL(i1,gt2,i2))
coup2L = Conjg(cplChaFvcSeR(i1,gt2,i2))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MCha2(i1),MSe2(i2))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,4
  Do i2=1,3
If ((MChi2(i1).gt.mf_l2(2)).Or.(MSv2(i2).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i1,gt1,i2)
coup1R = cplChiFvcSvR(i1,gt1,i2)
coup2R = Conjg(cplChiFvcSvL(i1,gt2,i2))
coup2L = Conjg(cplChiFvcSvR(i1,gt2,i2))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MChi2(i1),MSv2(i2))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,2
  Do i2=1,3
If ((MHpm2(i1).gt.mf_l2(2)).Or.(MFe2(i2).gt.mf_l2(2))) Then
coup1L = cplcFeFvHpmL(i2,gt1,i1)
coup1R = cplcFeFvHpmR(i2,gt1,i1)
coup2R = Conjg(cplcFeFvHpmL(i2,gt2,i1))
coup2L = Conjg(cplcFeFvHpmR(i2,gt2,i1))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MFe2(i2),MHpm2(i1))  
End if 
   End Do
  End Do




res = res + sumI*(Kronecker(gt2,1)+Kronecker(gt2,2)) 
End Do 
 
End Do 
 
Do gt1=1,2 
Do  gt2=1,3 
sumI = 0._dp 
 
chargefactor = 1 
Do i1=1,2
  Do i2=1,3
If ((MAh2(i1).gt.mf_l2(2)).Or.(MFe2(i2).gt.mf_l2(2))) Then
coup1L = cplcFeFeAhL(i2,gt1,i1)
coup1R = cplcFeFeAhR(i2,gt1,i1)
coup2R = Conjg(cplcFeFeAhL(i2,gt2,i1))
coup2L = Conjg(cplcFeFeAhR(i2,gt2,i1))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MFe2(i2),MAh2(i1))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,4
  Do i2=1,6
If ((MChi2(i1).gt.mf_l2(2)).Or.(MSe2(i2).gt.mf_l2(2))) Then
coup1L = cplChiFecSeL(i1,gt1,i2)
coup1R = cplChiFecSeR(i1,gt1,i2)
coup2R = Conjg(cplChiFecSeL(i1,gt2,i2))
coup2L = Conjg(cplChiFecSeR(i1,gt2,i2))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MChi2(i1),MSe2(i2))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,2
  Do i2=1,3
If ((Mhh2(i1).gt.mf_l2(2)).Or.(MFe2(i2).gt.mf_l2(2))) Then
coup1L = cplcFeFehhL(i2,gt1,i1)
coup1R = cplcFeFehhR(i2,gt1,i1)
coup2R = Conjg(cplcFeFehhL(i2,gt2,i1))
coup2L = Conjg(cplcFeFehhR(i2,gt2,i1))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MFe2(i2),Mhh2(i1))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,2
  Do i2=1,3
If ((MCha2(i1).gt.mf_l2(2)).Or.(MSv2(i2).gt.mf_l2(2))) Then
coup1L = cplcChaFecSvL(i1,gt1,i2)
coup1R = cplcChaFecSvR(i1,gt1,i2)
coup2R = Conjg(cplcChaFecSvL(i1,gt2,i2))
coup2L = Conjg(cplcChaFecSvR(i1,gt2,i2))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,MCha2(i1),MSv2(i2))  
End if 
   End Do
  End Do




chargefactor = 1 
Do i1=1,3
  Do i2=1,2
If ((0._dp.gt.mf_l2(2)).Or.(MHpm2(i2).gt.mf_l2(2))) Then
coup1L = cplcFvFecHpmL(i1,gt1,i2)
coup1R = cplcFvFecHpmR(i1,gt1,i2)
coup2R = Conjg(cplcFvFecHpmL(i1,gt2,i2))
coup2L = Conjg(cplcFvFecHpmR(i1,gt2,i2))
sumI = sumI + chargefactor*0.5_dp*coup1L*coup2R*B1(0._dp,0._dp,MHpm2(i2))  
End if 
   End Do
  End Do




res = res + sumI 
End Do 
 
End Do 
 
vertex = 0._dp 
 
Do gt1=1,3 
 Do gt2=1,2 
chargefactor = 1 
Do i1= 1,4
  Do i2= 1,3
   Do i3= 1,6
  If ((MChi2(i1).gt.mf_l2(2)).Or.(MSv2(i2).gt.mf_l2(2)).Or.(MSe2(i3).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i1,gt1,i2)
coup1R = cplChiFvcSvR(i1,gt1,i2)
coup2L = cplcFeChiSeL(gt2,i1,i3)
coup2R = cplcFeChiSeR(gt2,i1,i3)
coup3 = cplSvcSeVWm(i2,i3)
vertex = vertex + chargefactor*(0.5_dp*sqrt2*coup1L*coup2R*coup3*(MChi2(i1)*C0_3m(MChi2(i1),MSv2(i2),MSe2(i3)) + B0(0._dp,MSv2(i2),MSe2(i3)) +0.5_dp)) 
End if 
   End Do
  End Do
End Do


chargefactor = 1 
Do i1= 1,3
  Do i2= 1,2
   Do i3= 1,2
  If ((MFe2(i1).gt.mf_l2(2)).Or.(MHpm2(i2).gt.mf_l2(2)).Or.(MAh2(i3).gt.mf_l2(2))) Then
coup1L = cplcFeFvHpmL(i1,gt1,i2)
coup1R = cplcFeFvHpmR(i1,gt1,i2)
coup2L = cplcFeFeAhL(gt2,i1,i3)
coup2R = cplcFeFeAhR(gt2,i1,i3)
coup3 = -cplAhcHpmVWm(i3,i2)
vertex = vertex + chargefactor*(0.5_dp*sqrt2*coup1L*coup2R*coup3*(MFe2(i1)*C0_3m(MFe2(i1),MHpm2(i2),MAh2(i3)) + B0(0._dp,MHpm2(i2),MAh2(i3)) +0.5_dp)) 
End if 
   End Do
  End Do
End Do


chargefactor = 1 
Do i1= 1,3
  Do i2= 1,2
   Do i3= 1,2
  If ((MFe2(i1).gt.mf_l2(2)).Or.(MHpm2(i2).gt.mf_l2(2)).Or.(Mhh2(i3).gt.mf_l2(2))) Then
coup1L = cplcFeFvHpmL(i1,gt1,i2)
coup1R = cplcFeFvHpmR(i1,gt1,i2)
coup2L = cplcFeFehhL(gt2,i1,i3)
coup2R = cplcFeFehhR(gt2,i1,i3)
coup3 = -cplhhcHpmVWm(i3,i2)
vertex = vertex + chargefactor*(0.5_dp*sqrt2*coup1L*coup2R*coup3*(MFe2(i1)*C0_3m(MFe2(i1),MHpm2(i2),Mhh2(i3)) + B0(0._dp,MHpm2(i2),Mhh2(i3)) +0.5_dp)) 
End if 
   End Do
  End Do
End Do


chargefactor = 1 
Do i1= 1,3
   Do i3= 1,2
  If ((MFe2(i1).gt.mf_l2(2)).Or.(MVWm2.gt.mf_l2(2)).Or.(Mhh2(i3).gt.mf_l2(2))) Then
coup1L = cplcFeFvVWmL(i1,gt1)
coup1R = cplcFeFvVWmR(i1,gt1)
coup2L = cplcFeFehhL(gt2,i1,i3)
coup2R = cplcFeFehhR(gt2,i1,i3)
coup3 = cplhhcVWmVWm(i3)
End if 
   End Do
End Do


chargefactor = 1 
Do i1= 1,6
  Do i2= 1,2
   Do i3= 1,4
  If ((MSe2(i1).gt.mf_l2(2)).Or.(MCha2(i2).gt.mf_l2(2)).Or.(MChi2(i3).gt.mf_l2(2))) Then
coup1L = cplChaFvcSeL(i2,gt1,i1)
coup1R = cplChaFvcSeR(i2,gt1,i1)
coup2L = cplcFeChiSeL(gt2,i3,i1)
coup2R = cplcFeChiSeR(gt2,i3,i1)
coup3L = cplcChaChiVWmL(i2,i3)
coup3R = cplcChaChiVWmR(i2,i3)
vertex = vertex + chargefactor*(coup1L*coup2R*(-sqrt2*coup3R*MCha(i2)*MChi(i3)& 
& *C0_3m(MSe2(i1),MCha2(i2),MChi2(i3)) + oosqrt2*coup3L* & 
& (B0(0._dp,MCha2(i2),MChi2(i3))-0.5_dp +MSe2(i1)*C0_3m(MSe2(i1),MCha2(i2),MChi2(i3))))) 
End if 
   End Do
  End Do
End Do


chargefactor = 1 
Do i1= 1,3
  Do i2= 1,4
   Do i3= 1,2
  If ((MSv2(i1).gt.mf_l2(2)).Or.(MChi2(i2).gt.mf_l2(2)).Or.(MCha2(i3).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i2,gt1,i1)
coup1R = cplChiFvcSvR(i2,gt1,i1)
coup2L = cplcFeChaSvL(gt2,i3,i1)
coup2R = cplcFeChaSvR(gt2,i3,i1)
coup3L = -cplcChaChiVWmR(i3,i2)
coup3R = -cplcChaChiVWmL(i3,i2)
vertex = vertex + chargefactor*(coup1L*coup2R*(-sqrt2*coup3R*MChi(i2)*MCha(i3)& 
& *C0_3m(MSv2(i1),MChi2(i2),MCha2(i3)) + oosqrt2*coup3L* & 
& (B0(0._dp,MChi2(i2),MCha2(i3))-0.5_dp +MSv2(i1)*C0_3m(MSv2(i1),MChi2(i2),MCha2(i3))))) 
End if 
   End Do
  End Do
End Do


 End Do 
 
End Do 
 
res = res + vertex/g2 
Do gt1=1,3 
 Do gt2=1,3 
gt3 = 2 
gt4 = 1 
! Cha,Se,Chi,Se
chargefactor = 1 
Do i1=1,2
  Do i2=1,6
    Do i3=1,4
      Do i4=1,6
If ((MCha2(i1).gt.mf_l2(2)).Or.(MSe2(i2).gt.mf_l2(2)).Or.(MChi2(i3).gt.mf_l2(2)).Or.(MSe2(i4).gt.mf_l2(2))) Then
coup1L = cplChaFvcSeL(i1,gt1,i4)
coup1R = cplChaFvcSeR(i1,gt1,i4)
coup2L = cplcChacFvSeL(i1,gt2,i2)
coup2R = cplcChacFvSeR(i1,gt2,i2)
coup3L = cplChiFecSeL(i3,gt3,i2)
coup3R = cplChiFecSeR(i3,gt3,i2)
coup4L = cplcFeChiSeL(gt4,i3,i4)
coup4R = cplcFeChiSeR(gt4,i3,i4)
D27m2 = D27_Bagger(MSe2(i2),MSe2(i4),MCha2(i1),MChi2(i3))
If(Real(D27m2,dp).eq.Real(D27m2,dp)) Then 
teil = teil + D27m2*chargefactor*coup1L*coup2R*coup3L*coup4R 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


 ! Chi,Sv,bar[Cha],Sv
chargefactor = 1 
Do i1=1,4
  Do i2=1,3
    Do i3=1,2
      Do i4=1,3
If ((MChi2(i1).gt.mf_l2(2)).Or.(MSv2(i2).gt.mf_l2(2)).Or.(MCha2(i3).gt.mf_l2(2)).Or.(MSv2(i4).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i1,gt1,i4)
coup1R = cplChiFvcSvR(i1,gt1,i4)
coup2L = cplcFvChiSvL(gt2,i1,i2)
coup2R = cplcFvChiSvR(gt2,i1,i2)
coup3L = cplcChaFecSvL(i3,gt3,i2)
coup3R = cplcChaFecSvR(i3,gt3,i2)
coup4L = cplcFeChaSvL(gt4,i3,i4)
coup4R = cplcFeChaSvR(gt4,i3,i4)
D27m2 = D27_Bagger(MSv2(i2),MSv2(i4),MChi2(i1),MCha2(i3))
If(Real(D27m2,dp).eq.Real(D27m2,dp)) Then 
teil = teil + D27m2*chargefactor*coup1L*coup2R*coup3L*coup4R 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


 ! conj[Se],bar[Cha],Sv,bar[Cha]
chargefactor = 1 
Do i1=1,6
  Do i2=1,2
    Do i3=1,3
      Do i4=1,2
If ((MSe2(i1).gt.mf_l2(2)).Or.(MCha2(i2).gt.mf_l2(2)).Or.(MSv2(i3).gt.mf_l2(2)).Or.(MCha2(i4).gt.mf_l2(2))) Then
coup1L = cplChaFvcSeL(i4,gt1,i1)
coup1R = cplChaFvcSeR(i4,gt1,i1)
coup2L = cplcChacFvSeL(i2,gt2,i1)
coup2R = cplcChacFvSeR(i2,gt2,i1)
coup3L = cplcFeChaSvL(gt4,i2,i3)
coup3R = cplcFeChaSvR(gt4,i2,i3)
coup4L = cplcChaFecSvL(i4,gt3,i3)
coup4R = cplcChaFecSvR(i4,gt3,i3)
D0m2 = D0_Bagger(MSe2(i1),MSv2(i3),MCha2(i2),MCha2(i4))*MCha(i2)*MCha(i4) 
D27m2 = D27_Bagger(MSe2(i1),MSv2(i3),MCha2(i2),MCha2(i4))
If ((Real(D27m2,dp).eq.Real(D27m2,dp)).And.(Real(D0m2,dp).eq.Real(D0m2,dp))) Then 
teil = teil + 0.5_dp*chargefactor*D27m2*coup1L*coup2R*coup3L*coup4R+D0m2*coup1L*coup2L*coup3R*coup4R 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


 ! conj[Sv],Chi,Se,Chi
chargefactor = 1 
Do i1=1,3
  Do i2=1,4
    Do i3=1,6
      Do i4=1,4
If ((MSv2(i1).gt.mf_l2(2)).Or.(MChi2(i2).gt.mf_l2(2)).Or.(MSe2(i3).gt.mf_l2(2)).Or.(MChi2(i4).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i4,gt1,i1)
coup1R = cplChiFvcSvR(i4,gt1,i1)
coup2L = cplcFvChiSvL(gt2,i2,i1)
coup2R = cplcFvChiSvR(gt2,i2,i1)
coup3L = cplcFeChiSeL(gt4,i2,i3)
coup3R = cplcFeChiSeR(gt4,i2,i3)
coup4L = cplChiFecSeL(i4,gt3,i3)
coup4R = cplChiFecSeR(i4,gt3,i3)
D0m2 = D0_Bagger(MSv2(i1),MSe2(i3),MChi2(i2),MChi2(i4))*MChi(i2)*MChi(i4) 
D27m2 = D27_Bagger(MSv2(i1),MSe2(i3),MChi2(i2),MChi2(i4))
If ((Real(D27m2,dp).eq.Real(D27m2,dp)).And.(Real(D0m2,dp).eq.Real(D0m2,dp))) Then 
teil = teil + 0.5_dp*chargefactor*D27m2*coup1L*coup2R*coup3L*coup4R+D0m2*coup1L*coup2L*coup3R*coup4R 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


 ! conj[Se],Chi,Sv,bar[Cha]
chargefactor = 1 
Do i1=1,6
  Do i2=1,4
    Do i3=1,3
      Do i4=1,2
If ((MSe2(i1).gt.mf_l2(2)).Or.(MChi2(i2).gt.mf_l2(2)).Or.(MSv2(i3).gt.mf_l2(2)).Or.(MCha2(i4).gt.mf_l2(2))) Then
coup1L = cplChaFvcSeL(i4,gt1,i1)
coup1R = cplChaFvcSeR(i4,gt1,i1)
coup2L = cplcFeChiSeL(gt4,i2,i1)
coup2R = cplcFeChiSeR(gt4,i2,i1)
coup3L = cplcFvChiSvL(gt2,i2,i3)
coup3R = cplcFvChiSvR(gt2,i2,i3)
coup4L = cplcChaFecSvL(i4,gt3,i3)
coup4R = cplcChaFecSvR(i4,gt3,i3)
D0m2 = D0_Bagger(MSe2(i1),MSv2(i3),MChi2(i2),MCha2(i4))*MChi(i2)*MCha(i4) 
If (Real(D0m2,dp).eq.Real(D0m2,dp)) Then 
teil = teil + 0.5_dp*chargefactor*D0m2*coup1L*coup2R*coup3R*coup4L 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


 ! conj[Sv],Cha,Se,Chi
chargefactor = 1 
Do i1=1,3
  Do i2=1,2
    Do i3=1,6
      Do i4=1,4
If ((MSv2(i1).gt.mf_l2(2)).Or.(MCha2(i2).gt.mf_l2(2)).Or.(MSe2(i3).gt.mf_l2(2)).Or.(MChi2(i4).gt.mf_l2(2))) Then
coup1L = cplChiFvcSvL(i4,gt1,i1)
coup1R = cplChiFvcSvR(i4,gt1,i1)
coup2L = cplcFeChaSvL(gt4,i2,i1)
coup2R = cplcFeChaSvR(gt4,i2,i1)
coup3L = cplcChacFvSeL(i2,gt2,i3)
coup3R = cplcChacFvSeR(i2,gt2,i3)
coup4L = cplChiFecSeL(i4,gt3,i3)
coup4R = cplChiFecSeR(i4,gt3,i3)
D0m2 = D0_Bagger(MSv2(i1),MSe2(i3),MCha2(i2),MChi2(i4))*MCha(i2)*MChi(i4) 
If (Real(D0m2,dp).eq.Real(D0m2,dp)) Then 
teil = teil + 0.5_dp*chargefactor*D0m2*coup1L*coup2R*coup3R*coup4L 
End if
End if 
    End Do 
   End Do 
  End Do 
End Do 


  End Do 
 
End Do 
 

 
sumI = -2._dp*cosW2_DR*mz2*Real(teil,dp)/g2**2 
res = res + SumI 
End if ! BSM part 
res = res*oo16pi2 
Iname = Iname-1
End subroutine DeltaVB 
 
 
Subroutine CoupHiggsToPhoton(mHiggs,inG,ratCha,ratFd,ratFe,ratFu,ratHpm,              & 
& ratSd,ratSe,ratSu,ratVWm,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,MSu,gNLO,coup)

Implicit None 
Complex(dp),Intent(in) :: ratCha(2),ratFd(3),ratFe(3),ratFu(3),ratHpm(2),ratSd(6),ratSe(6),ratSu(6),ratVWm

Real(dp),Intent(in) :: MCha(2),MFd(3),MFe(3),MFu(3),MHpm(2),MVWm,MSd(6),MSe(6),MSu(6)

Integer, Intent(in) :: inG 
Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
coup = coup + 1*(-1)**2*ratVWm*A_one(mH2p/MVWm**2)
HPPloopVWm(inG) = HPPloopVWm(inG)+1*(-1)**2*ratVWm*A_one(mH2p/MVWm**2)
Do i1 = 1 , 6
coup = coup + cNLO_zero(mHiggs,MSd(i1),gNLO)*3*(-1._dp/3._dp)**2*ratSd(i1)*A_zero(mH2p/MSd(i1)**2)
HPPloopSd(i1,inG) = HPPloopSd(i1,inG) + cNLO_zero(mHiggs,MSd(i1),gNLO)*3*(-1._dp/3._dp)**2*ratSd(i1)*A_zero(mH2p/MSd(i1)**2)
End Do 
Do i1 = 1 , 6
coup = coup + cNLO_zero(mHiggs,MSu(i1),gNLO)*3*(2._dp/3._dp)**2*ratSu(i1)*A_zero(mH2p/MSu(i1)**2)
HPPloopSu(i1,inG) = HPPloopSu(i1,inG) + cNLO_zero(mHiggs,MSu(i1),gNLO)*3*(2._dp/3._dp)**2*ratSu(i1)*A_zero(mH2p/MSu(i1)**2)
End Do 
Do i1 = 1 , 6
coup = coup + 1*(-1)**2*ratSe(i1)*A_zero(mH2p/MSe(i1)**2)
HPPloopSe(i1,inG) = HPPloopSe(i1,inG)+1*(-1)**2*ratSe(i1)*A_zero(mH2p/MSe(i1)**2)
End Do 
Do i1 = 2 , 2
coup = coup + 1*(-1)**2*ratHpm(i1)*A_zero(mH2p/MHpm(i1)**2)
HPPloopHpm(i1,inG) = HPPloopHpm(i1,inG)+1*(-1)**2*ratHpm(i1)*A_zero(mH2p/MHpm(i1)**2)
End Do 
Do i1 = 1 , 2
coup = coup + 1*(-1)**2*ratCha(i1)*A_onehalf(mH2p/MCha(i1)**2)
HPPloopCha(i1,inG) = HPPloopCha(i1,inG)+1*(-1)**2*ratCha(i1)*A_onehalf(mH2p/MCha(i1)**2)
End Do 
Do i1 = 1 , 3
coup = coup + 1*(-1)**2*ratFe(i1)*A_onehalf(mH2p/MFe(i1)**2)
HPPloopFe(i1,inG) = HPPloopFe(i1,inG)+1*(-1)**2*ratFe(i1)*A_onehalf(mH2p/MFe(i1)**2)
End Do 
Do i1 = 1 , 3
coup = coup + cNLO_onehalf(mHiggs,MFd(i1),gNLO)*3*(-1._dp/3._dp)**2*ratFd(i1)*A_onehalf(mH2p/MFd(i1)**2)
HPPloopFd(i1,inG) = HPPloopFd(i1,inG) + cNLO_onehalf(mHiggs,MFd(i1),gNLO)*3*(-1._dp/3._dp)**2*ratFd(i1)*A_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 = 1 , 3
coup = coup + cNLO_onehalf(mHiggs,MFu(i1),gNLO)*3*(2._dp/3._dp)**2*ratFu(i1)*A_onehalf(mH2p/MFu(i1)**2)
HPPloopFu(i1,inG) = HPPloopFu(i1,inG) + cNLO_onehalf(mHiggs,MFu(i1),gNLO)*3*(2._dp/3._dp)**2*ratFu(i1)*A_onehalf(mH2p/MFu(i1)**2)
End Do 
End Subroutine CoupHiggsToPhoton

Subroutine CoupHiggsToGluon(mHiggs,inG,ratFd,ratFu,ratSd,ratSu,MFd,MFu,               & 
& MSd,MSu,gNLO,coup)

Implicit None 
Complex(dp),Intent(in) :: ratFd(3),ratFu(3),ratSd(6),ratSu(6)

Real(dp),Intent(in) :: MFd(3),MFu(3),MSd(6),MSu(6)

Integer, Intent(in) :: inG 
Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 = 1 , 6
coup = coup + 1*ratSd(i1)*A_zero(mH2p/MSd(i1)**2)
End Do 
Do i1 = 1 , 6
coup = coup + 1*ratSu(i1)*A_zero(mH2p/MSu(i1)**2)
End Do 
Do i1 = 1 , 3
coup = coup + 1*ratFd(i1)*A_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 = 1 , 3
coup = coup + 1*ratFu(i1)*A_onehalf(mH2p/MFu(i1)**2)
End Do 
coup = 0.75_dp*coup 
End Subroutine CoupHiggsToGluon

Subroutine CoupHiggsToPhotonSM(mHiggs,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,             & 
& MSu,gNLO,coup)

Implicit None 
Real(dp),Intent(in) :: MCha(2),MFd(3),MFe(3),MFu(3),MHpm(2),MVWm,MSd(6),MSe(6),MSu(6)

Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
coup = coup + 1*(-1)**2*A_one(mH2p/MVWm**2)
Do i1 =1, 3 
coup = coup + 1*(-1)**2*A_onehalf(mH2p/MFe(i1)**2)
End Do 
Do i1 =1, 3 
coup = coup + cNLO_onehalf(mHiggs,MFd(i1),gNLO)*3*(-1._dp/3._dp)**2*A_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3 
coup = coup + cNLO_onehalf(mHiggs,MFu(i1),gNLO)*3*(2._dp/3._dp)**2*A_onehalf(mH2p/MFu(i1)**2)
End Do 
End Subroutine CoupHiggsToPhotonSM 

Subroutine CoupHiggsToGluonSM(mHiggs,MFd,MFu,MSd,MSu,gNLO,coup)

Implicit None 
Real(dp),Intent(in) :: MFd(3),MFu(3),MSd(6),MSu(6)

Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 =1, 3 
coup = coup + 1*A_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3 
coup = coup + 1*A_onehalf(mH2p/MFu(i1)**2)
End Do 
coup = 0.75_dp*coup 
End Subroutine CoupHiggsToGluonSM 

Subroutine CoupPseudoHiggsToPhoton(mHiggs,inG,ratCha,ratFd,ratFe,ratFu,               & 
& ratHpm,ratSd,ratSe,ratSu,ratVWm,MCha,MFd,MFe,MFu,MHpm,MVWm,MSd,MSe,MSu,gNLO,coup)

Implicit None 
Complex(dp),Intent(in) :: ratCha(2),ratFd(3),ratFe(3),ratFu(3),ratHpm(2),ratSd(6),ratSe(6),ratSu(6),ratVWm

Real(dp),Intent(in) :: MCha(2),MFd(3),MFe(3),MFu(3),MHpm(2),MVWm,MSd(6),MSe(6),MSu(6)

Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Integer, Intent(in) :: inG 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 =1, 2
coup = coup + cANLO_onehalf(mHiggs,MCha(i1),gNLO)*1*(-1)**2*ratCha(i1)*AP_onehalf(mH2p/MCha(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFe(i1),gNLO)*1*(-1)**2*ratFe(i1)*AP_onehalf(mH2p/MFe(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFd(i1),gNLO)*3*(-1._dp/3._dp)**2*ratFd(i1)*AP_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFu(i1),gNLO)*3*(2._dp/3._dp)**2*ratFu(i1)*AP_onehalf(mH2p/MFu(i1)**2)
End Do 
End Subroutine CoupPseudoHiggsToPhoton

Subroutine CoupPseudoHiggsToGluon(mHiggs,inG,ratFd,ratFu,ratSd,ratSu,MFd,             & 
& MFu,MSd,MSu,gNLO,coup)

Implicit None 
Complex(dp),Intent(in) :: ratFd(3),ratFu(3),ratSd(6),ratSu(6)

Real(dp),Intent(in) :: MFd(3),MFu(3),MSd(6),MSu(6)

Real(dp), Intent(in) :: mHiggs, gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Integer, Intent(in) :: inG 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 =1, 3
coup = coup + 1*ratFd(i1)*AP_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + 1*ratFu(i1)*AP_onehalf(mH2p/MFu(i1)**2)
End Do 
coup = 0.75_dp*coup 
End Subroutine CoupPseudoHiggsToGluon

Subroutine CoupPseudoHiggsToPhotonSM(mHiggs,MCha,MFd,MFe,MFu,MHpm,MVWm,               & 
& MSd,MSe,MSu,gNLO,coup)

Implicit None 
Real(dp),Intent(in) :: MCha(2),MFd(3),MFe(3),MFu(3),MHpm(2),MVWm,MSd(6),MSe(6),MSu(6)

Real(dp), Intent(in) :: mHiggs,gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 =1, 2
coup = coup + cANLO_onehalf(mHiggs,MCha(i1),gNLO)*1*(-1)**2**AP_onehalf(mH2p/MCha(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFe(i1),gNLO)*1*(-1)**2**AP_onehalf(mH2p/MFe(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFd(i1),gNLO)*3*(-1._dp/3._dp)**2**AP_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + cANLO_onehalf(mHiggs,MFu(i1),gNLO)*3*(2._dp/3._dp)**2**AP_onehalf(mH2p/MFu(i1)**2)
End Do 
End Subroutine CoupPseudoHiggsToPhotonSM 

Subroutine CoupPseudoHiggsToGluonSM(mHiggs,MFd,MFu,MSd,MSu,gNLO,coup)

Implicit None 
Real(dp),Intent(in) :: MFd(3),MFu(3),MSd(6),MSu(6)

Real(dp), Intent(in) :: mHiggs,gNLO 
Complex(dp), Intent(out) :: coup 
Integer :: i1 
Real(dp) :: Mh2p 
mH2p = 0.25_dp*mHiggs**2 
coup = 0._dp 
 
Do i1 =1, 3
coup = coup + 1*AP_onehalf(mH2p/MFd(i1)**2)
End Do 
Do i1 =1, 3
coup = coup + 1*AP_onehalf(mH2p/MFu(i1)**2)
End Do 
coup = 0.75_dp*coup 
End Subroutine CoupPseudoHiggsToGluonSM 

Complex(dp) Function cNLO_onehalf(mH,mQ,g) 
Real(dp), Intent(in) :: mH, mQ, g
Real(dp)::tau 
tau=mH**2/(4._dp*mQ**2) 
If (g.lt.0._dp) Then 
  cNLO_onehalf = 1._dp 
Else 
  If (mH.lt.mQ) Then 
    cNLO_onehalf = 1._dp - oo4pi2*g**2  
  Else if (mH.gt.(2._dp*mQ)) Then 
   If (tau.lt.100._dp) Then 
    If (tau.lt.1.1_dp) Then 
      cNLO_onehalf=1._dp+(g**2/(4*Pi**2))*(&
       & (-1.033208159703536+7.10655096733206*tau-88.20900604676405*tau**2+598.6773733788388*tau**3-1967.3257953814561*tau**4+& 
       & 3247.6715405319346*tau**5-2330.127086890616*tau**6+677.9294006001846*tau**8-142.7923161120851*tau**10)& 
       &+(0._dp,1._dp)*(8.29739339711994-7.888861883558018/tau**3+10.437838040782095/tau**2-8.42394029242545/tau+0.2842283337270764*tau-&
       & 0.054995208547411904*tau*Log(tau)-1.6113597681662795*Log(4*tau)+0.000021811438531828155*tau**2*Log(tau**2))) 
    Else 
      cNLO_onehalf=1._dp+(g**2/(4*Pi**2))*(&
       & (-1.6170280814404576+0.40530581525102677/tau**3-0.33530992103515084/tau**2+3.9718559902660684/tau-0.000111953515865919*tau+& 
       & 9.129881821626589e-6*tau*Log(tau)+0.1338033886479311*Log(4*tau)-1.121902907800696e-12*tau**2*Log(tau**2))& 
       &+(0._dp,1._dp)*(8.29739339711994-7.888861883558018/tau**3+10.437838040782095/tau**2-8.42394029242545/tau+0.2842283337270764*tau-& 
       & 0.054995208547411904*tau*Log(tau)-1.6113597681662795*Log(4*tau)+0.000021811438531828155*tau**2*Log(tau**2))) 
    End if 
   Else ! mQ->0 
     cNLO_onehalf=1._dp+(g**2/(4*Pi**2))*&
      & (-(2._dp*Log(mH**2/mQ**2))/3._dp+(Pi**2-(Log(mH**2/mQ**2))**2)/18._dp+2*log(mH**2/4/mQ**2)&
      &+(0._dp,1._dp)*Pi/3*((Log(mH**2/mQ**2))/3+2._dp))
    End if 
  Else ! mQ~mH 
    cNLO_onehalf = 1._dp 
  End if 
End if 
End Function cNLO_onehalf 
 
Complex(dp) Function cANLO_onehalf(mH,mQ,g) 
Real(dp), Intent(in) :: mH, mQ, g
Real(dp)::tau 
tau=mH**2/(4._dp*mQ**2) 
If (g.lt.0._dp) Then 
  cANLO_onehalf = 1._dp 
Else 
  If (mH.lt.mQ) Then 
    cANLO_onehalf = 1._dp  
  Else if (mH.gt.(2._dp*mQ)) Then 
   If (tau.lt.100._dp) Then 
    If (tau.lt.1.1_dp) Then 
      cANLO_onehalf=1._dp+(g**2/(4*Pi**2))*(&
       & (-1.033208159703536+7.10655096733206*tau-88.20900604676405*tau**2+598.6773733788388*tau**3-1967.3257953814561*tau**4+& 
       & 3247.6715405319346*tau**5-2330.127086890616*tau**6+677.9294006001846*tau**8-142.7923161120851*tau**10)& 
       &+(0._dp,1._dp)*(8.29739339711994-7.888861883558018/tau**3+10.437838040782095/tau**2-8.42394029242545/tau+0.2842283337270764*tau-&
       & 0.054995208547411904*tau*Log(tau)-1.6113597681662795*Log(4*tau)+0.000021811438531828155*tau**2*Log(tau**2))) 
    Else 
      cANLO_onehalf=1._dp+(g**2/(4*Pi**2))*(&
       & (-1.6170280814404576+0.40530581525102677/tau**3-0.33530992103515084/tau**2+3.9718559902660684/tau-0.000111953515865919*tau+& 
       & 9.129881821626589e-6*tau*Log(tau)+0.1338033886479311*Log(4*tau)-1.121902907800696e-12*tau**2*Log(tau**2))& 
       &+(0._dp,1._dp)*(8.29739339711994-7.888861883558018/tau**3+10.437838040782095/tau**2-8.42394029242545/tau+0.2842283337270764*tau-& 
       & 0.054995208547411904*tau*Log(tau)-1.6113597681662795*Log(4*tau)+0.000021811438531828155*tau**2*Log(tau**2))) 
    End if 
   Else ! mQ->0 
     cANLO_onehalf=1._dp+(g**2/(4*Pi**2))*&
      & (-(2._dp*Log(mH**2/mQ**2))/3._dp+(Pi**2-(Log(mH**2/mQ**2))**2)/18._dp+2*log(mH**2/4/mQ**2)&
      &+(0._dp,1._dp)*Pi/3*((Log(mH**2/mQ**2))/3+2._dp))
    End if 
  Else ! mQ~mH 
    cANLO_onehalf = 1._dp 
  End if 
End if 
End Function cANLO_onehalf 
 
Real(dp) Function cNLO_zero(mH,mQ,g) 
Real(dp), Intent(in) :: mH, mQ, g
If (g.lt.0._dp) Then 
   cNLO_zero= 1._dp 
Else 
  If (mH.lt.mQ) Then 
    cNLO_zero = 1._dp + 2._dp*oo3pi2*g**2  
  Else  
    cNLO_zero = 1._dp 
  End if 
End if 
End Function cNLO_zero 
End Module LoopCouplings_MSSM 
 
