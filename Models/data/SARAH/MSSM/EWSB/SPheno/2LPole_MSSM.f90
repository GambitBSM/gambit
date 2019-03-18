Module Pole2L_MSSM 
 
Use Control 
Use Couplings_MSSM 
Use LoopFunctions 
Use Mathematics 
Use MathematicsQP 
Use Model_Data_MSSM 
Use StandardModel 
Use SusyMasses_MSSM 
Use Pole2LFunctions
Contains 
 
Subroutine CalculatePi2S(p2,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,              & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,kont,tad2L,Pi2S,Pi2P)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(in) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(in) :: vd,vu

Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Complex(dp) :: cplAhSdcSd(2,6,6),cplAhSecSe(2,6,6),cplAhSucSu(2,6,6),cplhhSdcSd(2,6,6),              & 
& cplhhSecSe(2,6,6),cplhhSucSu(2,6,6),cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),             & 
& cplSdcHpmcSu(6,2,6),cplSecHpmcSv(6,2,3),cplSdcSdVG(6,6),cplSucSuVG(6,6),               & 
& cplVGVGVG,cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2), & 
& cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplChaFucSdL(2,3,6),cplChaFucSdR(2,3,6),         & 
& cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),       & 
& cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),       & 
& cplChiFecSeL(4,3,6),cplChiFecSeR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),       & 
& cplcFdChiSdL(3,4,6),cplcFdChiSdR(3,4,6),cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),       & 
& cplcFuChiSuL(3,4,6),cplcFuChiSuR(3,4,6),cplGluFdcSdL(3,6),cplGluFdcSdR(3,6),           & 
& cplcFdFdhhL(3,3,2),cplcFdFdhhR(3,3,2),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),       & 
& cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),       & 
& cplcChaFecSvL(2,3,3),cplcChaFecSvR(2,3,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),   & 
& cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplcFuFuhhL(3,3,2),cplcFuFuhhR(3,3,2),             & 
& cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),cplcFeFvHpmL(3,3,2),cplcFeFvHpmR(3,3,2),       & 
& cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),               & 
& cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),cplcChacFvSeR(2,3,6),   & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplGluGluVGL,      & 
& cplGluGluVGR

Complex(dp) :: cplAhAhSdcSd(2,2,6,6),cplAhAhSecSe(2,2,6,6),cplAhAhSucSu(2,2,6,6),cplAhHpmSucSd(2,2,6,6),& 
& cplAhHpmSvcSe(2,2,3,6),cplAhSdcHpmcSu(2,6,2,6),cplAhSecHpmcSv(2,6,2,3),cplhhhhSdcSd(2,2,6,6),& 
& cplhhhhSecSe(2,2,6,6),cplhhhhSucSu(2,2,6,6),cplhhHpmSucSd(2,2,6,6),cplhhHpmSvcSe(2,2,3,6),& 
& cplhhSdcHpmcSu(2,6,2,6),cplhhSecHpmcSv(2,6,2,3),cplHpmSdcHpmcSd(2,6,2,6),              & 
& cplHpmSecHpmcSe(2,6,2,6),cplHpmSucHpmcSu(2,6,2,6),cplHpmSvcHpmcSv(2,3,2,3),            & 
& cplSdSdcSdcSd(6,6,6,6),cplSdSecSdcSe(6,6,6,6),cplSdSucSdcSu(6,6,6,6),cplSdSvcSecSu(6,3,6,6),& 
& cplSeSecSecSe(6,6,6,6),cplSeSucSdcSv(6,6,6,3),cplSeSvcSecSv(6,3,6,3),cplSuSucSucSu(6,6,6,6)

Real(dp), Intent(in) :: p2
Integer, Intent(inout):: kont
Integer :: gE1,gE2,i,i1,i2,i3,i4,i5 
Real(dp) :: Qscale,prefactor,funcvalue
complex(dp) :: cplxprefactor
Real(dp)  :: temptad(2)
Real(dp)  :: tempcont(2,2)
Real(dp)  :: runningval(2,2)
Real(dp), Intent(out) :: tad2l(2)
Real(dp), Intent(out) :: Pi2S(2,2)
Real(dp), Intent(out) :: Pi2P(2,2)
complex(dp) :: coup1,coup2,coup3,coup4
complex(dp) :: coup1L,coup1R,coup2l,coup2r,coup3l,coup3r,coup4l,coup4r
real(dp) :: epsFmass
real(dp) :: epscouplings
Real(dp)  :: tempcouplingvector(2)
Real(dp)  :: tempcouplingmatrix(2,2)
logical :: nonzerocoupling


tad2l(:)=0
Pi2S(:,:)=0
Pi2P(:,:)=0
Qscale=getrenormalizationscale()
epsfmass=0._dp
epscouplings=1.0E-6_dp
Call TreeMassesEffPot(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,               & 
& MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,           & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3,.True.,kont)

Call CouplingsFor2LPole3(Mu,Yd,Td,ZD,ZA,Ye,Te,ZE,Yu,Tu,ZU,vd,ZH,vu,ZP,ZV,             & 
& g3,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,UM,UP,ZN,pG,cplAhSdcSd,cplAhSecSe,cplAhSucSu,               & 
& cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,    & 
& cplSdcSdVG,cplSucSuVG,cplVGVGVG,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,       & 
& cplcFuFuAhL,cplcFuFuAhR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,           & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcFdChiSdL,cplcFdChiSdR,         & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,       & 
& cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,           & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,         & 
& cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcFdFdVGL,cplcFdFdVGR,       & 
& cplcFuFuVGL,cplcFuFuVGR,cplGluGluVGL,cplGluGluVGR)

Call CouplingsFor2LPole4(Yd,ZD,ZA,Ye,ZE,Yu,ZU,ZP,ZV,ZH,g3,cplAhAhSdcSd,               & 
& cplAhAhSecSe,cplAhAhSucSu,cplAhHpmSucSd,cplAhHpmSvcSe,cplAhSdcHpmcSu,cplAhSecHpmcSv,   & 
& cplhhhhSdcSd,cplhhhhSecSe,cplhhhhSucSu,cplhhHpmSucSd,cplhhHpmSvcSe,cplhhSdcHpmcSu,     & 
& cplhhSecHpmcSv,cplHpmSdcHpmcSd,cplHpmSecHpmcSe,cplHpmSucHpmcSu,cplHpmSvcHpmcSv,        & 
& cplSdSdcSdcSd,cplSdSecSdcSe,cplSdSucSdcSu,cplSdSvcSecSu,cplSeSecSecSe,cplSeSucSdcSv,   & 
& cplSeSvcSecSv,cplSuSucSucSu)

! ----------------------------
! ----- TADPOLE DIAGRAMS -----
! ----------------------------
temptad(:)=0._dp
tempcouplingvector(:)=0._dp
! ----- SCALAR ONLY DIAGRAMS
! ----- Topology T_SSS

! ---- hh,Sd,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhhhSdcSd(gE1,i1,i2,i3)
coup2 = cplhhSdcSd(i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSSS(Mhh2(i1),MSd2(i2),MSd2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- hh,Se,conj[Se] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhhhSecSe(gE1,i1,i2,i3)
coup2 = cplhhSecSe(i1,i3,i2)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSSS(Mhh2(i1),MSe2(i2),MSe2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- hh,Su,conj[Su] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhhhSucSu(gE1,i1,i2,i3)
coup2 = cplhhSucSu(i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSSS(Mhh2(i1),MSu2(i2),MSu2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Hpm,Su,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhHpmSucSd(gE1,i1,i2,i3)
coup2 = cplSdcHpmcSu(i3,i1,i2)
prefactor=Real(2*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSSS(MHpm2(i1),MSu2(i2),MSd2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Hpm,Sv,conj[Se] ----
Do i1=1,2
Do i2=1,3
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhHpmSvcSe(gE1,i1,i2,i3)
coup2 = cplSecHpmcSv(i3,i1,i2)
prefactor=Real(2*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSSS(MHpm2(i1),MSv2(i2),MSe2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ----- Topology T_SS

! ---- Sd,conj[Sd],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplAhAhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),MAh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhhhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),Mhh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplHpmSdcHpmcSd(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),MHpm2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplSdSdcSdcSd(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),MSd2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplSdSecSdcSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),MSe2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplSdSucSdcSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSd2(i1),MSd2(i2),MSu2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplAhAhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),MAh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhhhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),Mhh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplHpmSecHpmcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),MHpm2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplSdSecSdcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),MSd2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplSeSecSecSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),MSe2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplSeSvcSecSv(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSe2(i1),MSe2(i2),MSv2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplAhAhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSu2(i1),MSu2(i2),MAh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhhhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSu2(i1),MSu2(i2),Mhh2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplHpmSucHpmcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSu2(i1),MSu2(i2),MHpm2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplSdSucSdcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSu2(i1),MSu2(i2),MSd2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplSuSucSucSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= TfSS(MSu2(i1),MSu2(i2),MSu2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
! ----- Topology T_SSSS

! ---- Sd,conj[Sd],Ah,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(i3,i4,i1)
coup3 = cplAhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSd2(i1),MSd2(i2),MAh2(i3),MSd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],hh,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(i3,i4,i1)
coup3 = cplhhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSd2(i1),MSd2(i2),Mhh2(i3),MSd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Hpm,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplHpmSucSd(i3,i4,i1)
coup3 = cplSdcHpmcSu(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSd2(i1),MSd2(i2),MHpm2(i3),MSu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Ah,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(i3,i4,i1)
coup3 = cplAhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSe2(i1),MSe2(i2),MAh2(i3),MSe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],hh,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(i3,i4,i1)
coup3 = cplhhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSe2(i1),MSe2(i2),Mhh2(i3),MSe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Hpm,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplHpmSvcSe(i3,i4,i1)
coup3 = cplSecHpmcSv(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSe2(i1),MSe2(i2),MHpm2(i3),MSv2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Ah,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(i3,i4,i1)
coup3 = cplAhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSu2(i1),MSu2(i2),MAh2(i3),MSu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],hh,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(i3,i4,i1)
coup3 = cplhhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSu2(i1),MSu2(i2),Mhh2(i3),MSu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Sd,conj[Hpm] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplSdcHpmcSu(i3,i4,i1)
coup3 = cplHpmSucSd(i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSSSS(MSu2(i1),MSu2(i2),MSd2(i3),MHpm2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
End do
End do
End do
! ----- SCALAR AND VECTOR DIAGRAMS
! ----- Topology T_SV

! ---- Sd,conj[Sd],Sd,VG ----
Do i1=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSV(MSd2(i1),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
! ---- Su,conj[Su],Su,VG ----
Do i1=1,6
tempcouplingvector=0._dp
nonzerocoupling=.false.
Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingvector(gE1)=tempcouplingvector(gE1)+prefactor
nonzerocoupling=.true.
end if
   End Do
if(nonzerocoupling) then 
funcvalue= -1._dp*TfSV(MSu2(i1),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
End do
! ----- FERMION AND SCALAR DIAGRAMS
! ----- Topology T_SSFF

! ---- Sd,conj[Sd],Cha,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MCha(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(-6*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)*MCha(i3)*MFu(i4)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Sd,conj[Sd],Chi,Fd ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MChi(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(-6*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)*MChi(i3)*MFd(i4)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Sd,conj[Sd],Fd,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(-8*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)*MFd(i3)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
! ---- Se,conj[Se],Cha,Fv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MCha(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(-2*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)*MCha(i3)*0.
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Se,conj[Se],Chi,Fe ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MChi(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(-2*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)*MChi(i3)*MFe(i4)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Su,conj[Su],Chi,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MChi(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(-6*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)*MChi(i3)*MFu(i4)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Su,conj[Su],Fd,bar[Cha] ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(-6*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)*MFd(i3)*MCha(i4)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Su,conj[Su],Fu,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(-8*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFbFb(MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)*MFu(i3)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
! ----- Topology T_FFFS

! ---- Fd,bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,i4)
coup2R = cplcFdFdAhR(i1,i3,i4)
coup3L = cplcFdFdAhL(i3,i2,i4)
coup3R = cplcFdFdAhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2(i4),Qscale)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,i4)
coup2R = cplcFdFdAhR(i1,i3,i4)
coup3L = cplcFdFdAhL(i3,i2,i4)
coup3R = cplcFdFdAhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,i4)
coup2R = cplcFdFdAhR(i1,i3,i4)
coup3L = cplcFdFdAhL(i3,i2,i4)
coup3R = cplcFdFdAhR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2(i4),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fd,bar[Fd],Cha,Su ----
Do i1=1,3
Do i2=1,3
Do i3=1,2
Do i4=1,6
if((MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChaSuL(i1,i3,i4)
coup2R = cplcFdChaSuR(i1,i3,i4)
coup3L = cplcChaFdcSuL(i3,i2,i4)
coup3R = cplcChaFdcSuR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MCha2(i3),MSu2(i4),Qscale)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChaSuL(i1,i3,i4)
coup2R = cplcFdChaSuR(i1,i3,i4)
coup3L = cplcChaFdcSuL(i3,i2,i4)
coup3R = cplcChaFdcSuR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MCha2(i3),MSu2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChaSuL(i1,i3,i4)
coup2R = cplcFdChaSuR(i1,i3,i4)
coup3L = cplcChaFdcSuL(i3,i2,i4)
coup3R = cplcChaFdcSuR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MCha2(i3),MSu2(i4),Qscale)*MFd(i1)*MFd(i2)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fd,bar[Fd],Chi,Sd ----
Do i1=1,3
Do i2=1,3
Do i3=1,4
Do i4=1,6
if((MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChiSdL(i1,i3,i4)
coup2R = cplcFdChiSdR(i1,i3,i4)
coup3L = cplChiFdcSdL(i3,i2,i4)
coup3R = cplChiFdcSdR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MChi2(i3),MSd2(i4),Qscale)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChiSdL(i1,i3,i4)
coup2R = cplcFdChiSdR(i1,i3,i4)
coup3L = cplChiFdcSdL(i3,i2,i4)
coup3R = cplChiFdcSdR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MChi2(i3),MSd2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdChiSdL(i1,i3,i4)
coup2R = cplcFdChiSdR(i1,i3,i4)
coup3L = cplChiFdcSdL(i3,i2,i4)
coup3R = cplChiFdcSdR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MChi2(i3),MSd2(i4),Qscale)*MFd(i1)*MFd(i2)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,i4)
coup2R = cplcFdFdhhR(i1,i3,i4)
coup3L = cplcFdFdhhL(i3,i2,i4)
coup3R = cplcFdFdhhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2(i4),Qscale)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,i4)
coup2R = cplcFdFdhhR(i1,i3,i4)
coup3L = cplcFdFdhhL(i3,i2,i4)
coup3R = cplcFdFdhhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,i4)
coup2R = cplcFdFdhhR(i1,i3,i4)
coup3L = cplcFdFdhhL(i3,i2,i4)
coup3R = cplcFdFdhhR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2(i4),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fd,bar[Fd],Fu,Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFuHpmL(i1,i3,i4)
coup2R = cplcFdFuHpmR(i1,i3,i4)
coup3L = cplcFuFdcHpmL(i3,i2,i4)
coup3R = cplcFuFdcHpmR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHpm2(i4),Qscale)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFuHpmL(i1,i3,i4)
coup2R = cplcFdFuHpmR(i1,i3,i4)
coup3L = cplcFuFdcHpmL(i3,i2,i4)
coup3R = cplcFuFdcHpmR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MFu2(i3),MHpm2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFuHpmL(i1,i3,i4)
coup2R = cplcFdFuHpmR(i1,i3,i4)
coup3L = cplcFuFdcHpmL(i3,i2,i4)
coup3R = cplcFuFdcHpmR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHpm2(i4),Qscale)*MFd(i1)*MFd(i2)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fd,bar[Fd],Glu,Sd ----
Do i1=1,3
Do i2=1,3
Do i4=1,6
if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdGluSdL(i1,i4)
coup2R = cplcFdGluSdR(i1,i4)
coup3L = cplGluFdcSdL(i2,i4)
coup3R = cplGluFdcSdR(i2,i4)
prefactor=Real(8*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFd2(i1),MFd2(i2),MGlu2,MSd2(i4),Qscale)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdGluSdL(i1,i4)
coup2R = cplcFdGluSdR(i1,i4)
coup3L = cplGluFdcSdL(i2,i4)
coup3R = cplGluFdcSdR(i2,i4)
prefactor=Real(8*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFd2(i1),MFd2(i2),MGlu2,MSd2(i4),Qscale)*MFd(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdGluSdL(i1,i4)
coup2R = cplcFdGluSdR(i1,i4)
coup3L = cplGluFdcSdL(i2,i4)
coup3R = cplGluFdcSdR(i2,i4)
prefactor=Real(-8*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFd2(i1),MFd2(i2),MGlu2,MSd2(i4),Qscale)*MFd(i1)*MFd(i2)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
! ---- Fe,bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,i4)
coup2R = cplcFeFeAhR(i1,i3,i4)
coup3L = cplcFeFeAhL(i3,i2,i4)
coup3R = cplcFeFeAhR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2(i4),Qscale)*MFe(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,i4)
coup2R = cplcFeFeAhR(i1,i3,i4)
coup3L = cplcFeFeAhL(i3,i2,i4)
coup3R = cplcFeFeAhR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2(i4),Qscale)*MFe(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,i4)
coup2R = cplcFeFeAhR(i1,i3,i4)
coup3L = cplcFeFeAhL(i3,i2,i4)
coup3R = cplcFeFeAhR(i3,i2,i4)
prefactor=Real(-2*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2(i4),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fe,bar[Fe],Cha,Sv ----
Do i1=1,3
Do i2=1,3
Do i3=1,2
Do i4=1,3
if((MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChaSvL(i1,i3,i4)
coup2R = cplcFeChaSvR(i1,i3,i4)
coup3L = cplcChaFecSvL(i3,i2,i4)
coup3R = cplcChaFecSvR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFe2(i1),MFe2(i2),MCha2(i3),MSv2(i4),Qscale)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChaSvL(i1,i3,i4)
coup2R = cplcFeChaSvR(i1,i3,i4)
coup3L = cplcChaFecSvL(i3,i2,i4)
coup3R = cplcChaFecSvR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFe2(i1),MFe2(i2),MCha2(i3),MSv2(i4),Qscale)*MFe(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChaSvL(i1,i3,i4)
coup2R = cplcFeChaSvR(i1,i3,i4)
coup3L = cplcChaFecSvL(i3,i2,i4)
coup3R = cplcChaFecSvR(i3,i2,i4)
prefactor=Real(-2*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFe2(i1),MFe2(i2),MCha2(i3),MSv2(i4),Qscale)*MFe(i1)*MFe(i2)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fe,bar[Fe],Chi,Se ----
Do i1=1,3
Do i2=1,3
Do i3=1,4
Do i4=1,6
if((MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChiSeL(i1,i3,i4)
coup2R = cplcFeChiSeR(i1,i3,i4)
coup3L = cplChiFecSeL(i3,i2,i4)
coup3R = cplChiFecSeR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFe2(i1),MFe2(i2),MChi2(i3),MSe2(i4),Qscale)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChiSeL(i1,i3,i4)
coup2R = cplcFeChiSeR(i1,i3,i4)
coup3L = cplChiFecSeL(i3,i2,i4)
coup3R = cplChiFecSeR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFe2(i1),MFe2(i2),MChi2(i3),MSe2(i4),Qscale)*MFe(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeChiSeL(i1,i3,i4)
coup2R = cplcFeChiSeR(i1,i3,i4)
coup3L = cplChiFecSeL(i3,i2,i4)
coup3R = cplChiFecSeR(i3,i2,i4)
prefactor=Real(-2*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFe2(i1),MFe2(i2),MChi2(i3),MSe2(i4),Qscale)*MFe(i1)*MFe(i2)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,i4)
coup2R = cplcFeFehhR(i1,i3,i4)
coup3L = cplcFeFehhL(i3,i2,i4)
coup3R = cplcFeFehhR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2(i4),Qscale)*MFe(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,i4)
coup2R = cplcFeFehhR(i1,i3,i4)
coup3L = cplcFeFehhL(i3,i2,i4)
coup3R = cplcFeFehhR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2(i4),Qscale)*MFe(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,i4)
coup2R = cplcFeFehhR(i1,i3,i4)
coup3L = cplcFeFehhL(i3,i2,i4)
coup3R = cplcFeFehhR(i3,i2,i4)
prefactor=Real(-2*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2(i4),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fe,bar[Fe],Fv,Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFvHpmL(i1,i3,i4)
coup2R = cplcFeFvHpmR(i1,i3,i4)
coup3L = cplcFvFecHpmL(i3,i2,i4)
coup3R = cplcFvFecHpmR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFe2(i1),MFe2(i2),0._dp,MHpm2(i4),Qscale)*0.
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFvHpmL(i1,i3,i4)
coup2R = cplcFeFvHpmR(i1,i3,i4)
coup3L = cplcFvFecHpmL(i3,i2,i4)
coup3R = cplcFvFecHpmR(i3,i2,i4)
prefactor=Real(2*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFe2(i1),MFe2(i2),0._dp,MHpm2(i4),Qscale)*MFe(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFvHpmL(i1,i3,i4)
coup2R = cplcFeFvHpmR(i1,i3,i4)
coup3L = cplcFvFecHpmL(i3,i2,i4)
coup3R = cplcFvFecHpmR(i3,i2,i4)
prefactor=Real(-2*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFe2(i1),MFe2(i2),0._dp,MHpm2(i4),Qscale)*MFe(i1)*MFe(i2)*0.
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,i4)
coup2R = cplcFuFuAhR(i1,i3,i4)
coup3L = cplcFuFuAhL(i3,i2,i4)
coup3R = cplcFuFuAhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2(i4),Qscale)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,i4)
coup2R = cplcFuFuAhR(i1,i3,i4)
coup3L = cplcFuFuAhL(i3,i2,i4)
coup3R = cplcFuFuAhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,i4)
coup2R = cplcFuFuAhR(i1,i3,i4)
coup3L = cplcFuFuAhL(i3,i2,i4)
coup3R = cplcFuFuAhR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2(i4),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fu,bar[Fu],Chi,Su ----
Do i1=1,3
Do i2=1,3
Do i3=1,4
Do i4=1,6
if((MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuChiSuL(i1,i3,i4)
coup2R = cplcFuChiSuR(i1,i3,i4)
coup3L = cplChiFucSuL(i3,i2,i4)
coup3R = cplChiFucSuR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MChi2(i3),MSu2(i4),Qscale)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuChiSuL(i1,i3,i4)
coup2R = cplcFuChiSuR(i1,i3,i4)
coup3L = cplChiFucSuL(i3,i2,i4)
coup3R = cplChiFucSuR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MChi2(i3),MSu2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MChi(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuChiSuL(i1,i3,i4)
coup2R = cplcFuChiSuR(i1,i3,i4)
coup3L = cplChiFucSuL(i3,i2,i4)
coup3R = cplChiFucSuR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MChi2(i3),MSu2(i4),Qscale)*MFu(i1)*MFu(i2)*MChi(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fu,bar[Fu],Fd,conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFdcHpmL(i1,i3,i4)
coup2R = cplcFuFdcHpmR(i1,i3,i4)
coup3L = cplcFdFuHpmL(i3,i2,i4)
coup3R = cplcFdFuHpmR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHpm2(i4),Qscale)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFdcHpmL(i1,i3,i4)
coup2R = cplcFuFdcHpmR(i1,i3,i4)
coup3L = cplcFdFuHpmL(i3,i2,i4)
coup3R = cplcFdFuHpmR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MFd2(i3),MHpm2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFdcHpmL(i1,i3,i4)
coup2R = cplcFuFdcHpmR(i1,i3,i4)
coup3L = cplcFdFuHpmL(i3,i2,i4)
coup3R = cplcFdFuHpmR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHpm2(i4),Qscale)*MFu(i1)*MFu(i2)*MFd(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,i4)
coup2R = cplcFuFuhhR(i1,i3,i4)
coup3L = cplcFuFuhhL(i3,i2,i4)
coup3R = cplcFuFuhhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2(i4),Qscale)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,i4)
coup2R = cplcFuFuhhR(i1,i3,i4)
coup3L = cplcFuFuhhL(i3,i2,i4)
coup3R = cplcFuFuhhR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,i4)
coup2R = cplcFuFuhhR(i1,i3,i4)
coup3L = cplcFuFuhhL(i3,i2,i4)
coup3R = cplcFuFuhhR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2(i4),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Fu,bar[Fu],Glu,Su ----
Do i1=1,3
Do i2=1,3
Do i4=1,6
if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuGluSuL(i1,i4)
coup2R = cplcFuGluSuR(i1,i4)
coup3L = cplGluFucSuL(i2,i4)
coup3R = cplGluFucSuR(i2,i4)
prefactor=Real(8*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MGlu2,MSu2(i4),Qscale)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuGluSuL(i1,i4)
coup2R = cplcFuGluSuR(i1,i4)
coup3L = cplGluFucSuL(i2,i4)
coup3R = cplGluFucSuR(i2,i4)
prefactor=Real(8*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MGlu2,MSu2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuGluSuL(i1,i4)
coup2R = cplcFuGluSuR(i1,i4)
coup3L = cplGluFucSuL(i2,i4)
coup3R = cplGluFucSuR(i2,i4)
prefactor=Real(-8*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MGlu2,MSu2(i4),Qscale)*MFu(i1)*MFu(i2)*MGlu
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
! ---- Fu,bar[Fu],bar[Cha],Sd ----
Do i1=1,3
Do i2=1,3
Do i3=1,2
Do i4=1,6
if((MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcChacFuSdL(i3,i1,i4)
coup2R = cplcChacFuSdR(i3,i1,i4)
coup3L = cplChaFucSdL(i3,i2,i4)
coup3R = cplChaFucSdR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFFbS(MFu2(i1),MFu2(i2),MCha2(i3),MSd2(i4),Qscale)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcChacFuSdL(i3,i1,i4)
coup2R = cplcChacFuSdR(i3,i1,i4)
coup3L = cplChaFucSdL(i3,i2,i4)
coup3R = cplChaFucSdR(i3,i2,i4)
prefactor=Real(6*(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFFbFS(MFu2(i1),MFu2(i2),MCha2(i3),MSd2(i4),Qscale)*MFu(i2)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MCha(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcChacFuSdL(i3,i1,i4)
coup2R = cplcChacFuSdR(i3,i1,i4)
coup3L = cplChaFucSdL(i3,i2,i4)
coup3R = cplChaFucSdR(i3,i2,i4)
prefactor=Real(-6*(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFbFbFbS(MFu2(i1),MFu2(i2),MCha2(i3),MSd2(i4),Qscale)*MFu(i1)*MFu(i2)*MCha(i3)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
End do
End do
End do
! ----- FERMION AND VECTOR DIAGRAMS
! ----- Topology T_FV

! ---- Fd,bar[Fd],Fd,VG ----
Do i1=1,3
if((MFd(i1).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFdFdhhL(i1,i1,gE1)
coup1R = cplcFdFdhhR(i1,i1,gE1)
coup2=g3
coup3=g3
prefactor=Real(4*(coup1L*coup2*coup3+coup1R*coup2*coup3),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFV(MFd2(i1),Qscale)*MFd(i1)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
! ---- Fu,bar[Fu],Fu,VG ----
Do i1=1,3
if((MFu(i1).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
coup1L = cplcFuFuhhL(i1,i1,gE1)
coup1R = cplcFuFuhhR(i1,i1,gE1)
coup2=g3
coup3=g3
prefactor=Real(4*(coup1L*coup2*coup3+coup1R*coup2*coup3),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfFV(MFu2(i1),Qscale)*MFu(i1)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

End do
! ----------------------------
! ---- Final tadpole result --
temptad=temptad*oo16Pi2*oo16Pi2
tad2L=matmul(temptad,ZH)
! ----------------------------
! ----------------------------
! ------- MASS DIAGRAMS ------
! ----------------------------
tempcont(:,:)=0._dp
tempcouplingmatrix(:,:)=0._dp
! ----- SCALAR ONLY DIAGRAMS
! ----- Topology W_SSSS

! ---- Sd,conj[Sd],Ah,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplAhSdcSd(i3,i4,i1)
coup3 = cplAhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),MAh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],hh,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplhhSdcSd(i3,i4,i1)
coup3 = cplhhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),Mhh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Hpm,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplHpmSucSd(i3,i4,i1)
coup3 = cplSdcHpmcSu(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Ah,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplAhSecSe(i3,i4,i1)
coup3 = cplAhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),MAh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],hh,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplhhSecSe(i3,i4,i1)
coup3 = cplhhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),Mhh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Hpm,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplHpmSvcSe(i3,i4,i1)
coup3 = cplSecHpmcSv(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Ah,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplAhSucSu(i3,i4,i1)
coup3 = cplAhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),MAh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],hh,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplhhSucSu(i3,i4,i1)
coup3 = cplhhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),Mhh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Sd,conj[Hpm] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplSdcHpmcSu(i3,i4,i1)
coup3 = cplHpmSucSd(i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology X_SSS

! ---- Sd,conj[Sd],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplAhAhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplhhhhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplHpmSdcHpmcSd(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSdcSdcSd(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSecSdcSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSucSdcSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplAhAhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplhhhhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplHpmSecHpmcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplSdSecSdcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplSeSecSecSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2 = cplSeSvcSecSv(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSv2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplAhAhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplhhhhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplHpmSucHpmcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplSdSucSdcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2 = cplSuSucSucSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology Y_SSSS

! ---- Sd,conj[Sd],Sd,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplAhAhSdcSd(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplhhhhSdcSd(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplHpmSdcHpmcSd(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplSdSdcSdcSd(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplSdSecSdcSe(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplSdSucSdcSu(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplAhAhSecSe(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplhhhhSecSe(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplHpmSecHpmcSe(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplSdSecSdcSe(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplSeSecSecSe(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplSeSvcSecSv(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplAhAhSucSu(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplhhhhSucSu(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplHpmSucHpmcSu(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplSdSucSdcSu(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplSuSucSucSu(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology Z_SSSS

! ---- Sd,conj[Sd],Sd,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i4)
coup3 = cplSdSdcSdcSd(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Se,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i4)
coup3 = cplSdSecSdcSe(i2,i4,i1,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Su,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i4)
coup3 = cplSdSucSdcSu(i2,i4,i1,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i4)
coup3 = cplSeSecSecSe(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i4)
coup3 = cplSuSucSucSu(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology1 S_SSS

! ---- hh,Sd,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,i1,i2,i3)
coup2 = cplhhhhSdcSd(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,Mhh2(i1),MSd2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- hh,Se,conj[Se] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,i1,i2,i3)
coup2 = cplhhhhSecSe(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,Mhh2(i1),MSe2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- hh,Su,conj[Su] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,i1,i2,i3)
coup2 = cplhhhhSucSu(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,Mhh2(i1),MSu2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Hpm,Su,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhHpmSucSd(gE1,i1,i2,i3)
coup2 = cplhhSdcHpmcSu(gE2,i3,i1,i2)
prefactor=Real(2*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MHpm2(i1),MSu2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Hpm,Sv,conj[Se] ----
Do i1=1,2
Do i2=1,3
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhHpmSvcSe(gE1,i1,i2,i3)
coup2 = cplhhSecHpmcSv(gE2,i3,i1,i2)
prefactor=Real(2*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MHpm2(i1),MSv2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology U_SSSS

! ---- Sd,conj[Sd],hh,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhhhSdcSd(gE2,i3,i4,i1)
coup3 = cplhhSdcSd(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSd2(i1),MSd2(i2),Mhh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Hpm,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhHpmSucSd(gE2,i3,i4,i1)
coup3 = cplSdcHpmcSu(i2,i3,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],hh,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhhhSecSe(gE2,i3,i4,i1)
coup3 = cplhhSecSe(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSe2(i1),MSe2(i2),Mhh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Hpm,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhHpmSvcSe(gE2,i3,i4,i1)
coup3 = cplSecHpmcSv(i2,i3,i4)
prefactor=Real(4*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],hh,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhhhSucSu(gE2,i3,i4,i1)
coup3 = cplhhSucSu(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSu2(i1),MSu2(i2),Mhh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Sd,conj[Hpm] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSdcHpmcSu(gE2,i3,i4,i1)
coup3 = cplHpmSucSd(i4,i2,i3)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology V_SSSSS

! ---- Sd,conj[Sd],Sd,Ah,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplAhSdcSd(i4,i2,i5)
coup4 = cplAhSdcSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MAh2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,hh,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplhhSdcSd(i4,i2,i5)
coup4 = cplhhSdcSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Mhh2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,conj[Hpm],conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3 = cplSdcHpmcSu(i2,i4,i5)
coup4 = cplHpmSucSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MHpm2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Ah,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplAhSecSe(i4,i2,i5)
coup4 = cplAhSecSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MAh2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,hh,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplhhSecSe(i4,i2,i5)
coup4 = cplhhSecSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Mhh2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,conj[Hpm],conj[Sv] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3 = cplSecHpmcSv(i2,i4,i5)
coup4 = cplHpmSvcSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MHpm2(i4),MSv2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Ah,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplAhSucSu(i4,i2,i5)
coup4 = cplAhSucSu(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MAh2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,hh,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplhhSucSu(i4,i2,i5)
coup4 = cplhhSucSu(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Mhh2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Hpm,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3 = cplHpmSucSd(i4,i2,i5)
coup4 = cplSdcHpmcSu(i5,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MHpm2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- Topology M_SSSSS

! ---- Sd,conj[Sd],conj[Sd],Sd,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2 = cplhhSdcSd(gE2,i4,i2)
coup3 = cplAhSdcSd(i5,i2,i1)
coup4 = cplAhSdcSd(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],conj[Sd],Sd,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2 = cplhhSdcSd(gE2,i4,i2)
coup3 = cplhhSdcSd(i5,i2,i1)
coup4 = cplhhSdcSd(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Su],conj[Sd],Su,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2 = cplhhSucSu(gE2,i4,i2)
coup3 = cplHpmSucSd(i5,i2,i1)
coup4 = cplSdcHpmcSu(i3,i5,i4)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSu2(i2),MSd2(i3),MSu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],conj[Se],Se,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i3)
coup2 = cplhhSecSe(gE2,i4,i2)
coup3 = cplAhSecSe(i5,i2,i1)
coup4 = cplAhSecSe(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],conj[Se],Se,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i3)
coup2 = cplhhSecSe(gE2,i4,i2)
coup3 = cplhhSecSe(i5,i2,i1)
coup4 = cplhhSecSe(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],conj[Su],Su,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2 = cplhhSucSu(gE2,i4,i2)
coup3 = cplAhSucSu(i5,i2,i1)
coup4 = cplAhSucSu(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],conj[Su],Su,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2 = cplhhSucSu(gE2,i4,i2)
coup3 = cplhhSucSu(i5,i2,i1)
coup4 = cplhhSucSu(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- SCALAR AND VECTOR DIAGRAMS
! ----- Topology W_SSSV 

! ---- Sd,conj[Sd],Sd,VG ----
Do i1=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSV(p2,MSd2(i1),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
! ---- Su,conj[Su],Su,VG ----
Do i1=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSV(p2,MSu2(i1),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
! ----- Topology V_SSSSV 

! ----- Topology M_SSSSV 

! ---- Sd,conj[Sd],conj[Sd],Sd,VG ----
Do i1=1,6
Do i2=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i2,i1)
coup3 = g3
coup4 = g3
prefactor=Real(1*coup1*coup2*coup3*coup4*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSV(p2,MSd2(i1),MSd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
! ---- Su,conj[Su],conj[Su],Su,VG ----
Do i1=1,6
Do i2=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i2,i1)
coup3 = g3
coup4 = g3
prefactor=Real(1*coup1*coup2*coup3*coup4*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSV(p2,MSu2(i1),MSu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
! ----- FERMION AND SCALAR DIAGRAMS
! ----- Topology W_SSFF 

! ---- Sd,conj[Sd],Cha,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
if((MCha(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)*MCha(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Chi,Fd ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)*MChi(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Fd,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
if((MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSdcSd(gE1,gE2,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Cha,Fv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
if((MCha(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(1*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)*MCha(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Chi,Fe ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(1*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)*MChi(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSecSe(gE1,gE2,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Chi,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)*MChi(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Fd,bar[Cha] ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
Do i4=1,2
if((MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Fu,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
if((MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhhhSucSu(gE1,gE2,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology M_FFFFS 

! ---- Fd,bar[Fd],bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fu],bar[Fd],Fu,Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFu(i2)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i3,i1,gE1)
coup1R = cplcFdFdhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i3,i1,gE1)
coup1R = cplcFeFehhR(i3,i1,gE1)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fd],bar[Fu],Fd,conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFd(i2)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i3,i1,gE1)
coup1R = cplcFuFuhhR(i3,i1,gE1)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- Topology M_SFSFF 

! ---- Sd,bar[Fd],conj[Sd],Fd,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MFd(i2)*MFd(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Sd,bar[Fd],conj[Sd],Fd,Glu ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MFd(i2)*MFd(i4)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(16*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Sd,bar[Fu],conj[Sd],Fu,Cha ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,2
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MFu(i2)*MFu(i4)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Se,bar[Fe],conj[Se],Fe,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i3)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MFe(i2)*MFe(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i3)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(4*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i3)
coup2L = cplcFeFehhL(i2,i4,gE2)
coup2R = cplcFeFehhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fd],conj[Su],Fd,bar[Cha] ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,2
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MFd(i2)*MFd(i4)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFdFdhhL(i2,i4,gE2)
coup2R = cplcFdFdhhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fu],conj[Su],Fu,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MFu(i2)*MFu(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fu],conj[Su],Fu,Glu ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MFu(i2)*MFu(i4)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(16*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i3)
coup2L = cplcFuFuhhL(i2,i4,gE2)
coup2R = cplcFuFuhhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
! ----- Topology V_SSSFF 

! ---- Sd,conj[Sd],Sd,Chi,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcFdChiSdL(i5,i4,i2)
coup3R = cplcFdChiSdR(i5,i4,i2)
coup4L = cplChiFdcSdL(i4,i5,i3)
coup4R = cplChiFdcSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MChi2(i4),MFd2(i5),Qscale)*MChi(i4)*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcFdChiSdL(i5,i4,i2)
coup3R = cplcFdChiSdR(i5,i4,i2)
coup4L = cplChiFdcSdL(i4,i5,i3)
coup4R = cplChiFdcSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MChi2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Glu,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i5=1,3
if((MGlu.gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcFdGluSdL(i5,i2)
coup3R = cplcFdGluSdR(i5,i2)
coup4L = cplGluFdcSdL(i5,i3)
coup4R = cplGluFdcSdR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MGlu2,MFd2(i5),Qscale)*MGlu*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcFdGluSdL(i5,i2)
coup3R = cplcFdGluSdR(i5,i2)
coup4L = cplGluFdcSdL(i5,i3)
coup4R = cplGluFdcSdR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MGlu2,MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,bar[Cha],bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcChacFuSdL(i4,i5,i2)
coup3R = cplcChacFuSdR(i4,i5,i2)
coup4L = cplChaFucSdL(i4,i5,i3)
coup4R = cplChaFucSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MCha2(i4),MFu2(i5),Qscale)*MCha(i4)*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSdcSd(gE1,i1,i2)
coup2 = cplhhSdcSd(gE2,i3,i1)
coup3L = cplcChacFuSdL(i4,i5,i2)
coup3R = cplcChacFuSdR(i4,i5,i2)
coup4L = cplChaFucSdL(i4,i5,i3)
coup4R = cplChaFucSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MCha2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Chi,bar[Fe] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFe(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3L = cplcFeChiSeL(i5,i4,i2)
coup3R = cplcFeChiSeR(i5,i4,i2)
coup4L = cplChiFecSeL(i4,i5,i3)
coup4R = cplChiFecSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSe2(i1),MSe2(i2),MSe2(i3),MChi2(i4),MFe2(i5),Qscale)*MChi(i4)*MFe(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3L = cplcFeChiSeL(i5,i4,i2)
coup3R = cplcFeChiSeR(i5,i4,i2)
coup4L = cplChiFecSeL(i4,i5,i3)
coup4R = cplChiFecSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSe2(i1),MSe2(i2),MSe2(i3),MChi2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,bar[Cha],bar[Fv] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3L = cplcChacFvSeL(i4,i5,i2)
coup3R = cplcChacFvSeR(i4,i5,i2)
coup4L = cplChaFvcSeL(i4,i5,i3)
coup4R = cplChaFvcSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSe2(i1),MSe2(i2),MSe2(i3),MCha2(i4),0._dp,Qscale)*MCha(i4)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSecSe(gE1,i1,i2)
coup2 = cplhhSecSe(gE2,i3,i1)
coup3L = cplcChacFvSeL(i4,i5,i2)
coup3R = cplcChacFvSeR(i4,i5,i2)
coup4L = cplChaFvcSeL(i4,i5,i3)
coup4R = cplChaFvcSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSe2(i1),MSe2(i2),MSe2(i3),MCha2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Cha,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFdChaSuL(i5,i4,i2)
coup3R = cplcFdChaSuR(i5,i4,i2)
coup4L = cplcChaFdcSuL(i4,i5,i3)
coup4R = cplcChaFdcSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MCha2(i4),MFd2(i5),Qscale)*MCha(i4)*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFdChaSuL(i5,i4,i2)
coup3R = cplcFdChaSuR(i5,i4,i2)
coup4L = cplcChaFdcSuL(i4,i5,i3)
coup4R = cplcChaFdcSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MCha2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Chi,bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFuChiSuL(i5,i4,i2)
coup3R = cplcFuChiSuR(i5,i4,i2)
coup4L = cplChiFucSuL(i4,i5,i3)
coup4R = cplChiFucSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MChi2(i4),MFu2(i5),Qscale)*MChi(i4)*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFuChiSuL(i5,i4,i2)
coup3R = cplcFuChiSuR(i5,i4,i2)
coup4L = cplChiFucSuL(i4,i5,i3)
coup4R = cplChiFucSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MChi2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Glu,bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i5=1,3
if((MGlu.gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFuGluSuL(i5,i2)
coup3R = cplcFuGluSuR(i5,i2)
coup4L = cplGluFucSuL(i5,i3)
coup4R = cplGluFucSuR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MGlu2,MFu2(i5),Qscale)*MGlu*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplhhSucSu(gE1,i1,i2)
coup2 = cplhhSucSu(gE2,i3,i1)
coup3L = cplcFuGluSuL(i5,i2)
coup3R = cplcFuGluSuR(i5,i2)
coup4L = cplGluFucSuL(i5,i3)
coup4R = cplGluFucSuR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MGlu2,MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology V_FFFFS 

! ---- Fd,bar[Fd],Fd,bar[Fd],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,Chi,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,Glu,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(16*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(16*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Fd],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Cha],conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Fu],conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i3,gE2)
coup2R = cplcFdFdhhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fe],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,Chi,conj[Se] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fe],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Cha],conj[Sv] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,3
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fv],conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFehhL(i2,i1,gE1)
coup1R = cplcFeFehhR(i2,i1,gE1)
coup2L = cplcFeFehhL(i1,i3,gE2)
coup2R = cplcFeFehhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fu],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Cha,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Chi,conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Glu,conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(16*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(16*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fu],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fd],Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i3,gE2)
coup2R = cplcFuFuhhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- FERMION AND VECTOR DIAGRAMS
! ----- Topology G_FFFFV 

! ---- Fd,bar[Fd],Fd,VG,bar[Fd] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i2,gE2)
coup2R = cplcFdFdhhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFFV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdhhL(i2,i1,gE1)
coup1R = cplcFdFdhhR(i2,i1,gE1)
coup2L = cplcFdFdhhL(i1,i2,gE2)
coup2R = cplcFdFdhhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFbFbV(p2,MFd2(i1),MFd2(i2),Qscale)*MFd(i1)*MFd(i2)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
! ---- Fu,bar[Fu],Fu,VG,bar[Fu] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i2,gE2)
coup2R = cplcFuFuhhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFFV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuhhL(i2,i1,gE1)
coup1R = cplcFuFuhhR(i2,i1,gE1)
coup2L = cplcFuFuhhL(i1,i2,gE2)
coup2R = cplcFuFuhhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFbFbV(p2,MFu2(i1),MFu2(i2),Qscale)*MFu(i1)*MFu(i2)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
! ----- TIDY UP AND SYMMETRISE -----
do gE1=1,2
Pi2S(gE1,gE1)=Pi2S(gE1,gE1)+tempcont(gE1,gE1)*oo16Pi2*oo16Pi2
do gE2=1,gE1-1
Pi2S(gE1,gE2)=Pi2S(gE1,gE2)+0.5_dp*(tempcont(gE1,gE2)+tempcont(gE2,gE1))*oo16Pi2*oo16Pi2
Pi2S(gE2,gE1)=Pi2S(gE1,gE2)
End do
End do
Pi2S = Matmul(Pi2S,ZH)
Pi2S = Matmul(Transpose(ZH),Pi2S)
! ----------------------------
! ------- MASS DIAGRAMS ------
! ----------------------------
tempcont(:,:)=0._dp
tempcouplingmatrix(:,:)=0._dp
! ----- SCALAR ONLY DIAGRAMS
! ----- Topology W_SSSS

! ---- Sd,conj[Sd],Ah,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplAhSdcSd(i3,i4,i1)
coup3 = cplAhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),MAh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],hh,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplhhSdcSd(i3,i4,i1)
coup3 = cplhhSdcSd(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),Mhh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Hpm,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplHpmSucSd(i3,i4,i1)
coup3 = cplSdcHpmcSu(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Ah,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplAhSecSe(i3,i4,i1)
coup3 = cplAhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),MAh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],hh,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplhhSecSe(i3,i4,i1)
coup3 = cplhhSecSe(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),Mhh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Hpm,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplHpmSvcSe(i3,i4,i1)
coup3 = cplSecHpmcSv(i2,i3,i4)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Ah,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplAhSucSu(i3,i4,i1)
coup3 = cplAhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),MAh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],hh,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplhhSucSu(i3,i4,i1)
coup3 = cplhhSucSu(i3,i2,i4)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),Mhh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Sd,conj[Hpm] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplSdcHpmcSu(i3,i4,i1)
coup3 = cplHpmSucSd(i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology X_SSS

! ---- Sd,conj[Sd],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplAhAhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplhhhhSdcSd(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplHpmSdcHpmcSd(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSdcSdcSd(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSecSdcSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Sd,conj[Sd],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2 = cplSdSucSdcSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSd2(i1),MSd2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplAhAhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplhhhhSecSe(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplHpmSecHpmcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplSdSecSdcSe(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplSeSecSecSe(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2 = cplSeSvcSecSv(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSe2(i1),MSe2(i2),MSv2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplAhAhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MAh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplhhhhSucSu(i3,i3,i2,i1)
prefactor=Real(1._dp/2._dp*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),Mhh2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplHpmSucHpmcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MHpm2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplSdSucSdcSu(i3,i2,i3,i1)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Su,conj[Su],Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2 = cplSuSucSucSu(i2,i3,i1,i3)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= XfSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology Y_SSSS

! ---- Sd,conj[Sd],Sd,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplAhAhSdcSd(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplhhhhSdcSd(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplHpmSdcHpmcSd(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplSdSdcSdcSd(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplSdSecSdcSe(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplSdSucSdcSu(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplAhAhSecSe(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplhhhhSecSe(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplHpmSecHpmcSe(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplSdSecSdcSe(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplSeSecSecSe(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplSeSvcSecSv(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplAhAhSucSu(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MAh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplhhhhSucSu(i4,i4,i2,i3)
prefactor=Real(1*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Mhh2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplHpmSucHpmcSu(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplSdSucSdcSu(i4,i2,i4,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplSuSucSucSu(i2,i4,i3,i4)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*YfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology Z_SSSS

! ---- Sd,conj[Sd],Sd,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i4)
coup3 = cplSdSdcSdcSd(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Se,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i4)
coup3 = cplSdSecSdcSe(i2,i4,i1,i3)
prefactor=Real(2*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Su,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i4)
coup3 = cplSdSucSdcSu(i2,i4,i1,i3)
prefactor=Real(2*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSd2(i1),MSd2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Se,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i4)
coup3 = cplSeSecSecSe(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Su,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i4)
coup3 = cplSuSucSucSu(i2,i4,i1,i3)
prefactor=Real(1*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*ZfSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology1 S_SSS

! ---- Ah,Sd,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,i1,i2,i3)
coup2 = cplAhAhSdcSd(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MAh2(i1),MSd2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Ah,Se,conj[Se] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,i1,i2,i3)
coup2 = cplAhAhSecSe(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MAh2(i1),MSe2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Ah,Su,conj[Su] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,i1,i2,i3)
coup2 = cplAhAhSucSu(gE2,i1,i3,i2)
prefactor=Real(1*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MAh2(i1),MSu2(i2),MSu2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Hpm,Su,conj[Sd] ----
Do i1=1,2
Do i2=1,6
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhHpmSucSd(gE1,i1,i2,i3)
coup2 = cplAhSdcHpmcSu(gE2,i3,i1,i2)
prefactor=Real(2*coup1*coup2*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MHpm2(i1),MSu2(i2),MSd2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Hpm,Sv,conj[Se] ----
Do i1=1,2
Do i2=1,3
Do i3=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhHpmSvcSe(gE1,i1,i2,i3)
coup2 = cplAhSecHpmcSv(gE2,i3,i1,i2)
prefactor=Real(2*coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= SfSSS(p2,MHpm2(i1),MSv2(i2),MSe2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology U_SSSS

! ---- Sd,conj[Sd],Ah,Sd ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhAhSdcSd(gE2,i3,i4,i1)
coup3 = cplAhSdcSd(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSd2(i1),MSd2(i2),MAh2(i3),MSd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Hpm,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhHpmSucSd(gE2,i3,i4,i1)
coup3 = cplSdcHpmcSu(i2,i3,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSd2(i1),MSd2(i2),MHpm2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Ah,Se ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhAhSecSe(gE2,i3,i4,i1)
coup3 = cplAhSecSe(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSe2(i1),MSe2(i2),MAh2(i3),MSe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Hpm,Sv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhHpmSvcSe(gE2,i3,i4,i1)
coup3 = cplSecHpmcSv(i2,i3,i4)
prefactor=Real(4*coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSe2(i1),MSe2(i2),MHpm2(i3),MSv2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Ah,Su ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhAhSucSu(gE2,i3,i4,i1)
coup3 = cplAhSucSu(i3,i2,i4)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSu2(i1),MSu2(i2),MAh2(i3),MSu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Sd,conj[Hpm] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSdcHpmcSu(gE2,i3,i4,i1)
coup3 = cplHpmSucSd(i4,i2,i3)
prefactor=Real(4*coup1*coup2*coup3*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*UfSSSS(p2,MSu2(i1),MSu2(i2),MSd2(i3),MHpm2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology V_SSSSS

! ---- Sd,conj[Sd],Sd,Ah,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplAhSdcSd(i4,i2,i5)
coup4 = cplAhSdcSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MAh2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,hh,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplhhSdcSd(i4,i2,i5)
coup4 = cplhhSdcSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),Mhh2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,conj[Hpm],conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3 = cplSdcHpmcSu(i2,i4,i5)
coup4 = cplHpmSucSd(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MHpm2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Ah,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplAhSecSe(i4,i2,i5)
coup4 = cplAhSecSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MAh2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,hh,conj[Se] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplhhSecSe(i4,i2,i5)
coup4 = cplhhSecSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),Mhh2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,conj[Hpm],conj[Sv] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3 = cplSecHpmcSv(i2,i4,i5)
coup4 = cplHpmSvcSe(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MHpm2(i4),MSv2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Ah,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplAhSucSu(i4,i2,i5)
coup4 = cplAhSucSu(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MAh2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,hh,conj[Su] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplhhSucSu(i4,i2,i5)
coup4 = cplhhSucSu(i4,i5,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),Mhh2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Hpm,conj[Sd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3 = cplHpmSucSd(i4,i2,i5)
coup4 = cplSdcHpmcSu(i5,i4,i3)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= VfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MHpm2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- Topology M_SSSSS

! ---- Sd,conj[Sd],conj[Sd],Sd,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2 = cplAhSdcSd(gE2,i4,i2)
coup3 = cplAhSdcSd(i5,i2,i1)
coup4 = cplAhSdcSd(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],conj[Sd],Sd,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2 = cplAhSdcSd(gE2,i4,i2)
coup3 = cplhhSdcSd(i5,i2,i1)
coup4 = cplhhSdcSd(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSd2(i2),MSd2(i3),MSd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Su],conj[Sd],Su,Hpm ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2 = cplAhSucSu(gE2,i4,i2)
coup3 = cplHpmSucSd(i5,i2,i1)
coup4 = cplSdcHpmcSu(i3,i5,i4)
prefactor=Real(2*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSd2(i1),MSu2(i2),MSd2(i3),MSu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],conj[Se],Se,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i3)
coup2 = cplAhSecSe(gE2,i4,i2)
coup3 = cplAhSecSe(i5,i2,i1)
coup4 = cplAhSecSe(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],conj[Se],Se,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i3)
coup2 = cplAhSecSe(gE2,i4,i2)
coup3 = cplhhSecSe(i5,i2,i1)
coup4 = cplhhSecSe(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSe2(i1),MSe2(i2),MSe2(i3),MSe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],conj[Su],Su,Ah ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2 = cplAhSucSu(gE2,i4,i2)
coup3 = cplAhSucSu(i5,i2,i1)
coup4 = cplAhSucSu(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],conj[Su],Su,hh ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,6
Do i5=1,2
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2 = cplAhSucSu(gE2,i4,i2)
coup3 = cplhhSucSu(i5,i2,i1)
coup4 = cplhhSucSu(i5,i3,i4)
prefactor=Real(1*coup1*coup2*coup3*coup4*3,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSS(p2,MSu2(i1),MSu2(i2),MSu2(i3),MSu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- SCALAR AND VECTOR DIAGRAMS
! ----- Topology W_SSSV 

! ---- Sd,conj[Sd],Sd,VG ----
Do i1=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSV(p2,MSd2(i1),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
! ---- Su,conj[Su],Su,VG ----
Do i1=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(1*coup1*coup2*coup3*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= -1._dp*WfSSSV(p2,MSu2(i1),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
! ----- Topology V_SSSSV 

! ----- Topology M_SSSSV 

! ---- Sd,conj[Sd],conj[Sd],Sd,VG ----
Do i1=1,6
Do i2=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i2,i1)
coup3 = g3
coup4 = g3
prefactor=Real(1*coup1*coup2*coup3*coup4*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSV(p2,MSd2(i1),MSd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
! ---- Su,conj[Su],conj[Su],Su,VG ----
Do i1=1,6
Do i2=1,6
tempcouplingmatrix=0._dp
nonzerocoupling=.false.
Do gE1=1,2
  Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i2,i1)
coup3 = g3
coup4 = g3
prefactor=Real(1*coup1*coup2*coup3*coup4*4,dp)
if(abs(prefactor) .gt. epscouplings) then
tempcouplingmatrix(gE1,gE2)=tempcouplingmatrix(gE1,gE2)+prefactor
nonzerocoupling=.true.
end if
   End Do
End do
if(nonzerocoupling) then 
funcvalue= MfSSSSV(p2,MSu2(i1),MSu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
! ----- FERMION AND SCALAR DIAGRAMS
! ----- Topology W_SSFF 

! ---- Sd,conj[Sd],Cha,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
if((MCha(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)*MCha(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChaFucSdL(i3,i4,i1)
coup2R = cplChaFucSdR(i3,i4,i1)
coup3L = cplcChacFuSdL(i3,i4,i2)
coup3R = cplcChacFuSdR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MCha2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Chi,Fd ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)*MChi(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplChiFdcSdL(i3,i4,i1)
coup2R = cplChiFdcSdR(i3,i4,i1)
coup3L = cplcFdChiSdL(i4,i3,i2)
coup3R = cplcFdChiSdR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MChi2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Fd,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
if((MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSdcSd(gE1,gE2,i1,i2)
coup2L = cplGluFdcSdL(i3,i1)
coup2R = cplGluFdcSdR(i3,i1)
coup3L = cplcFdGluSdL(i3,i2)
coup3R = cplcFdGluSdR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSd2(i1),MSd2(i2),MFd2(i3),MGlu2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ---- Se,conj[Se],Cha,Fv ----
Do i1=1,6
Do i2=1,6
Do i3=1,2
Do i4=1,3
if((MCha(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(1*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)*MCha(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2L = cplChaFvcSeL(i3,i4,i1)
coup2R = cplChaFvcSeR(i3,i4,i1)
coup3L = cplcChacFvSeL(i3,i4,i2)
coup3R = cplcChacFvSeR(i3,i4,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSe2(i1),MSe2(i2),MCha2(i3),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Se,conj[Se],Chi,Fe ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(1*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)*MChi(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSecSe(gE1,gE2,i1,i2)
coup2L = cplChiFecSeL(i3,i4,i1)
coup2R = cplChiFecSeR(i3,i4,i1)
coup3L = cplcFeChiSeL(i4,i3,i2)
coup3R = cplcFeChiSeR(i4,i3,i2)
prefactor=Real(1*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSe2(i1),MSe2(i2),MChi2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Chi,Fu ----
Do i1=1,6
Do i2=1,6
Do i3=1,4
Do i4=1,3
if((MChi(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)*MChi(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplChiFucSuL(i3,i4,i1)
coup2R = cplChiFucSuR(i3,i4,i1)
coup3L = cplcFuChiSuL(i4,i3,i2)
coup3R = cplcFuChiSuR(i4,i3,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MChi2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Fd,bar[Cha] ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
Do i4=1,2
if((MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplcChaFdcSuL(i4,i3,i1)
coup2R = cplcChaFdcSuR(i4,i3,i1)
coup3L = cplcFdChaSuL(i3,i4,i2)
coup3R = cplcFdChaSuR(i3,i4,i2)
prefactor=Real(3*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MFd2(i3),MCha2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Su,conj[Su],Fu,Glu ----
Do i1=1,6
Do i2=1,6
Do i3=1,3
if((MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3L+coup1*coup2R*coup3R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFbFb(p2,MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhAhSucSu(gE1,gE2,i1,i2)
coup2L = cplGluFucSuL(i3,i1)
coup2R = cplGluFucSuR(i3,i1)
coup3L = cplcFuGluSuL(i3,i2)
coup3R = cplcFuGluSuR(i3,i2)
prefactor=Real(4*(coup1*coup2L*coup3R+coup1*coup2R*coup3L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MSu2(i1),MSu2(i2),MFu2(i3),MGlu2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
! ----- Topology M_FFFFS 

! ---- Fd,bar[Fd],bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdAhL(i1,i2,i5)
coup3R = cplcFdFdAhR(i1,i2,i5)
coup4L = cplcFdFdAhL(i4,i3,i5)
coup4R = cplcFdFdAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFdFdhhL(i1,i2,i5)
coup3R = cplcFdFdhhR(i1,i2,i5)
coup4L = cplcFdFdhhL(i4,i3,i5)
coup4R = cplcFdFdhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fu],bar[Fd],Fu,Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFu(i2)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i3,i1,gE1)
coup1R = cplcFdFdAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFdFuHpmL(i1,i2,i5)
coup3R = cplcFdFuHpmR(i1,i2,i5)
coup4L = cplcFuFdcHpmL(i4,i3,i5)
coup4R = cplcFuFdcHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFeAhL(i1,i2,i5)
coup3R = cplcFeFeAhR(i1,i2,i5)
coup4L = cplcFeFeAhL(i4,i3,i5)
coup4R = cplcFeFeAhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i3,i1,gE1)
coup1R = cplcFeFeAhR(i3,i1,gE1)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplcFeFehhL(i1,i2,i5)
coup3R = cplcFeFehhR(i1,i2,i5)
coup4L = cplcFeFehhL(i4,i3,i5)
coup4R = cplcFeFehhR(i4,i3,i5)
prefactor=Real(1*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fd],bar[Fu],Fd,conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFd(i2)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcFuFdcHpmL(i1,i2,i5)
coup3R = cplcFuFdcHpmR(i1,i2,i5)
coup4L = cplcFdFuHpmL(i4,i3,i5)
coup4R = cplcFdFuHpmR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuAhL(i1,i2,i5)
coup3R = cplcFuFuAhR(i1,i2,i5)
coup4L = cplcFuFuAhL(i4,i3,i5)
coup4R = cplcFuFuAhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i3,i1,gE1)
coup1R = cplcFuFuAhR(i3,i1,gE1)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplcFuFuhhL(i1,i2,i5)
coup3R = cplcFuFuhhR(i1,i2,i5)
coup4L = cplcFuFuhhL(i4,i3,i5)
coup4R = cplcFuFuhhR(i4,i3,i5)
prefactor=Real(3*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- Topology M_SFSFF 

! ---- Sd,bar[Fd],conj[Sd],Fd,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MFd(i2)*MFd(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplChiFdcSdL(i5,i2,i1)
coup3R = cplChiFdcSdR(i5,i2,i1)
coup4L = cplcFdChiSdL(i4,i5,i3)
coup4R = cplcFdChiSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Sd,bar[Fd],conj[Sd],Fd,Glu ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MFd(i2)*MFd(i4)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(16*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplGluFdcSdL(i2,i1)
coup3R = cplGluFdcSdR(i2,i1)
coup4L = cplcFdGluSdL(i4,i3)
coup4R = cplcFdGluSdR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFd2(i2),MSd2(i3),MFd2(i4),MGlu2,Qscale)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
! ---- Sd,bar[Fu],conj[Sd],Fu,Cha ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,2
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MFu(i2)*MFu(i4)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChaFucSdL(i5,i2,i1)
coup3R = cplChaFucSdR(i5,i2,i1)
coup4L = cplcChacFuSdL(i5,i4,i3)
coup4R = cplcChacFuSdR(i5,i4,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSd2(i1),MFu2(i2),MSd2(i3),MFu2(i4),MCha2(i5),Qscale)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Se,bar[Fe],conj[Se],Fe,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFe(i2).gt. epsfmass).and. (MFe(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i3)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MFe(i2)*MFe(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i3)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(4*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i3)
coup2L = cplcFeFeAhL(i2,i4,gE2)
coup2R = cplcFeFeAhR(i2,i4,gE2)
coup3L = cplChiFecSeL(i5,i2,i1)
coup3R = cplChiFecSeR(i5,i2,i1)
coup4L = cplcFeChiSeL(i4,i5,i3)
coup4R = cplcFeChiSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSe2(i1),MFe2(i2),MSe2(i3),MFe2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fd],conj[Su],Fd,bar[Cha] ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,2
if((MFd(i2).gt. epsfmass).and. (MFd(i4).gt. epsfmass).and. (MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MFd(i2)*MFd(i4)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MCha(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFdFdAhL(i2,i4,gE2)
coup2R = cplcFdFdAhR(i2,i4,gE2)
coup3L = cplcChaFdcSuL(i5,i2,i1)
coup3R = cplcChaFdcSuR(i5,i2,i1)
coup4L = cplcFdChaSuL(i4,i5,i3)
coup4R = cplcFdChaSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFd2(i2),MSu2(i3),MFd2(i4),MCha2(i5),Qscale)*MCha(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fu],conj[Su],Fu,Chi ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
Do i5=1,4
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MFu(i2)*MFu(i4)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(12*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MChi(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplChiFucSuL(i5,i2,i1)
coup3R = cplChiFucSuR(i5,i2,i1)
coup4L = cplcFuChiSuL(i4,i5,i3)
coup4R = cplcFuChiSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MChi2(i5),Qscale)*MChi(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
End do
! ---- Su,bar[Fu],conj[Su],Fu,Glu ----
Do i1=1,6
Do i2=1,3
Do i3=1,6
Do i4=1,3
if((MFu(i2).gt. epsfmass).and. (MFu(i4).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFbSFbFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MFu(i2)*MFu(i4)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(16*(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFbF(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i3)
coup2L = cplcFuFuAhL(i2,i4,gE2)
coup2R = cplcFuFuAhR(i2,i4,gE2)
coup3L = cplGluFucSuL(i2,i1)
coup3R = cplGluFucSuR(i2,i1)
coup4L = cplcFuGluSuL(i4,i3)
coup4R = cplcFuGluSuR(i4,i3)
prefactor=Real(8*(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MfSFSFFb(p2,MSu2(i1),MFu2(i2),MSu2(i3),MFu2(i4),MGlu2,Qscale)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
End do
End do
! ----- Topology V_SSSFF 

! ---- Sd,conj[Sd],Sd,Chi,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcFdChiSdL(i5,i4,i2)
coup3R = cplcFdChiSdR(i5,i4,i2)
coup4L = cplChiFdcSdL(i4,i5,i3)
coup4R = cplChiFdcSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MChi2(i4),MFd2(i5),Qscale)*MChi(i4)*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcFdChiSdL(i5,i4,i2)
coup3R = cplcFdChiSdR(i5,i4,i2)
coup4L = cplChiFdcSdL(i4,i5,i3)
coup4R = cplChiFdcSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MChi2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,Glu,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i5=1,3
if((MGlu.gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcFdGluSdL(i5,i2)
coup3R = cplcFdGluSdR(i5,i2)
coup4L = cplGluFdcSdL(i5,i3)
coup4R = cplGluFdcSdR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MGlu2,MFd2(i5),Qscale)*MGlu*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcFdGluSdL(i5,i2)
coup3R = cplcFdGluSdR(i5,i2)
coup4L = cplGluFdcSdL(i5,i3)
coup4R = cplGluFdcSdR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MGlu2,MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Sd,conj[Sd],Sd,bar[Cha],bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcChacFuSdL(i4,i5,i2)
coup3R = cplcChacFuSdR(i4,i5,i2)
coup4L = cplChaFucSdL(i4,i5,i3)
coup4R = cplChaFucSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSd2(i1),MSd2(i2),MSd2(i3),MCha2(i4),MFu2(i5),Qscale)*MCha(i4)*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSdcSd(gE1,i1,i2)
coup2 = cplAhSdcSd(gE2,i3,i1)
coup3L = cplcChacFuSdL(i4,i5,i2)
coup3R = cplcChacFuSdR(i4,i5,i2)
coup4L = cplChaFucSdL(i4,i5,i3)
coup4R = cplChaFucSdR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSd2(i1),MSd2(i2),MSd2(i3),MCha2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,Chi,bar[Fe] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFe(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3L = cplcFeChiSeL(i5,i4,i2)
coup3R = cplcFeChiSeR(i5,i4,i2)
coup4L = cplChiFecSeL(i4,i5,i3)
coup4R = cplChiFecSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSe2(i1),MSe2(i2),MSe2(i3),MChi2(i4),MFe2(i5),Qscale)*MChi(i4)*MFe(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3L = cplcFeChiSeL(i5,i4,i2)
coup3R = cplcFeChiSeR(i5,i4,i2)
coup4L = cplChiFecSeL(i4,i5,i3)
coup4R = cplChiFecSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSe2(i1),MSe2(i2),MSe2(i3),MChi2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Se,conj[Se],Se,bar[Cha],bar[Fv] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3L = cplcChacFvSeL(i4,i5,i2)
coup3R = cplcChacFvSeR(i4,i5,i2)
coup4L = cplChaFvcSeL(i4,i5,i3)
coup4R = cplChaFvcSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSe2(i1),MSe2(i2),MSe2(i3),MCha2(i4),0._dp,Qscale)*MCha(i4)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSecSe(gE1,i1,i2)
coup2 = cplAhSecSe(gE2,i3,i1)
coup3L = cplcChacFvSeL(i4,i5,i2)
coup3R = cplcChacFvSeR(i4,i5,i2)
coup4L = cplChaFvcSeL(i4,i5,i3)
coup4R = cplChaFvcSeR(i4,i5,i3)
prefactor=Real(2*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSe2(i1),MSe2(i2),MSe2(i3),MCha2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Cha,bar[Fd] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,2
Do i5=1,3
if((MCha(i4).gt. epsfmass).and. (MFd(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFdChaSuL(i5,i4,i2)
coup3R = cplcFdChaSuR(i5,i4,i2)
coup4L = cplcChaFdcSuL(i4,i5,i3)
coup4R = cplcChaFdcSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MCha2(i4),MFd2(i5),Qscale)*MCha(i4)*MFd(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFdChaSuL(i5,i4,i2)
coup3R = cplcFdChaSuR(i5,i4,i2)
coup4L = cplcChaFdcSuL(i4,i5,i3)
coup4R = cplcChaFdcSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MCha2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Chi,bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i4=1,4
Do i5=1,3
if((MChi(i4).gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFuChiSuL(i5,i4,i2)
coup3R = cplcFuChiSuR(i5,i4,i2)
coup4L = cplChiFucSuL(i4,i5,i3)
coup4R = cplChiFucSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MChi2(i4),MFu2(i5),Qscale)*MChi(i4)*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFuChiSuL(i5,i4,i2)
coup3R = cplcFuChiSuR(i5,i4,i2)
coup4L = cplChiFucSuL(i4,i5,i3)
coup4R = cplChiFucSuR(i4,i5,i3)
prefactor=Real(6*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MChi2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Su,conj[Su],Su,Glu,bar[Fu] ----
Do i1=1,6
Do i2=1,6
Do i3=1,6
Do i5=1,3
if((MGlu.gt. epsfmass).and. (MFu(i5).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFuGluSuL(i5,i2)
coup3R = cplcFuGluSuR(i5,i2)
coup4L = cplGluFucSuL(i5,i3)
coup4R = cplGluFucSuR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFbFb(p2,MSu2(i1),MSu2(i2),MSu2(i3),MGlu2,MFu2(i5),Qscale)*MGlu*MFu(i5)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1 = cplAhSucSu(gE1,i1,i2)
coup2 = cplAhSucSu(gE2,i3,i1)
coup3L = cplcFuGluSuL(i5,i2)
coup3R = cplcFuGluSuR(i5,i2)
coup4L = cplGluFucSuL(i5,i3)
coup4R = cplGluFucSuR(i5,i3)
prefactor=Real(8*(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfSSSFF(p2,MSu2(i1),MSu2(i2),MSu2(i3),MGlu2,MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ----- Topology V_FFFFS 

! ---- Fd,bar[Fd],Fd,bar[Fd],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdAhL(i4,i2,i5)
coup3R = cplcFdFdAhR(i4,i2,i5)
coup4L = cplcFdFdAhL(i3,i4,i5)
coup4R = cplcFdFdAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,Chi,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)*MFd(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplChiFdcSdL(i4,i2,i5)
coup3R = cplChiFdcSdR(i4,i2,i5)
coup4L = cplcFdChiSdL(i3,i4,i5)
coup4R = cplcFdChiSdR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MChi2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,Glu,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(16*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i1)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(16*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)*MFd(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplGluFdcSdL(i2,i5)
coup3R = cplGluFdcSdR(i2,i5)
coup4L = cplcFdGluSdL(i3,i5)
coup4R = cplcFdGluSdR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MGlu2,MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Fd],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)*MFd(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFdFdhhL(i4,i2,i5)
coup3R = cplcFdFdhhR(i4,i2,i5)
coup4L = cplcFdFdhhL(i3,i4,i5)
coup4R = cplcFdFdhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Cha],conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,6
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)*MFd(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcChaFdcSuL(i4,i2,i5)
coup3R = cplcChaFdcSuR(i4,i2,i5)
coup4L = cplcFdChaSuL(i3,i4,i5)
coup4R = cplcFdChaSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MCha2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fd,bar[Fd],Fd,bar[Fu],conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFd(i2)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2).gt. epsfmass).and. (MFd(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i2)*MFd(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)*MFd(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i3,gE2)
coup2R = cplcFdFdAhR(i1,i3,gE2)
coup3L = cplcFuFdcHpmL(i4,i2,i5)
coup3R = cplcFuFdcHpmR(i4,i2,i5)
coup4L = cplcFdFuHpmL(i3,i4,i5)
coup4R = cplcFdFuHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fe],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i1)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFeAhL(i4,i2,i5)
coup3R = cplcFeFeAhR(i4,i2,i5)
coup4L = cplcFeFeAhL(i3,i4,i5)
coup4R = cplcFeFeAhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,Chi,conj[Se] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)*MFe(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplChiFecSeL(i4,i2,i5)
coup3R = cplChiFecSeR(i4,i2,i5)
coup4L = cplcFeChiSeL(i3,i4,i5)
coup4R = cplcFeChiSeR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MChi2(i4),MSe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fe],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i1)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MFe(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)*MFe(i3)*MFe(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFeFehhL(i4,i2,i5)
coup3R = cplcFeFehhR(i4,i2,i5)
coup4L = cplcFeFehhL(i3,i4,i5)
coup4R = cplcFeFehhR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Cha],conj[Sv] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,3
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)*MFe(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcChaFecSvL(i4,i2,i5)
coup3R = cplcChaFecSvR(i4,i2,i5)
coup4L = cplcFeChaSvL(i3,i4,i5)
coup4R = cplcFeChaSvR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MCha2(i4),MSv2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fe,bar[Fe],Fe,bar[Fv],conj[Hpm] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFe(i1).gt. epsfmass).and. (MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*MFe(i2)*MFe(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i1)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2).gt. epsfmass).and. (MFe(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i2)*MFe(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3).gt. epsfmass).and. (0..gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(4*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)*MFe(i3)*0.
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFeFeAhL(i2,i1,gE1)
coup1R = cplcFeFeAhR(i2,i1,gE1)
coup2L = cplcFeFeAhL(i1,i3,gE2)
coup2R = cplcFeFeAhR(i1,i3,gE2)
coup3L = cplcFvFecHpmL(i4,i2,i5)
coup3R = cplcFvFecHpmR(i4,i2,i5)
coup4L = cplcFeFvHpmL(i3,i4,i5)
coup4R = cplcFeFvHpmR(i3,i4,i5)
prefactor=Real(2*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fu],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuAhL(i4,i2,i5)
coup3R = cplcFuFuAhR(i4,i2,i5)
coup4L = cplcFuFuAhL(i3,i4,i5)
coup4R = cplcFuFuAhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Cha,conj[Sd] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i1)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MCha(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)*MFu(i3)*MCha(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChaFucSdL(i4,i2,i5)
coup3R = cplChaFucSdR(i4,i2,i5)
coup4L = cplcChacFuSdL(i4,i3,i5)
coup4R = cplcChacFuSdR(i4,i3,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MCha2(i4),MSd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Chi,conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,4
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i1)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MChi(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)*MFu(i3)*MChi(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplChiFucSuL(i4,i2,i5)
coup3R = cplChiFucSuR(i4,i2,i5)
coup4L = cplcFuChiSuL(i3,i4,i5)
coup4R = cplcFuChiSuR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MChi2(i4),MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,Glu,conj[Su] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i5=1,6
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(16*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i1)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MGlu.gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(16*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)*MFu(i3)*MGlu
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplGluFucSuL(i2,i5)
coup3R = cplGluFucSuR(i2,i5)
coup4L = cplcFuGluSuL(i3,i5)
coup4R = cplcFuGluSuR(i3,i5)
prefactor=Real(8*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MGlu2,MSu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fu],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i1)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFu(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)*MFu(i3)*MFu(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFuFuhhL(i4,i2,i5)
coup3R = cplcFuFuhhR(i4,i2,i5)
coup4L = cplcFuFuhhL(i3,i4,i5)
coup4R = cplcFuFuhhR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ---- Fu,bar[Fu],Fu,bar[Fd],Hpm ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFu(i2)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i1)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2).gt. epsfmass).and. (MFu(i3).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i2)*MFu(i3)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3).gt. epsfmass).and. (MFd(i4).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(12*(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)*MFu(i3)*MFd(i4)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i3,gE2)
coup2R = cplcFuFuAhR(i1,i3,gE2)
coup3L = cplcFdFuHpmL(i4,i2,i5)
coup3R = cplcFdFuHpmR(i4,i2,i5)
coup4L = cplcFuFdcHpmL(i3,i4,i5)
coup4R = cplcFuFdcHpmR(i3,i4,i5)
prefactor=Real(6*(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHpm2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
End do
End do
End do
End do
End do
! ----- FERMION AND VECTOR DIAGRAMS
! ----- Topology G_FFFFV 

! ---- Fd,bar[Fd],Fd,VG,bar[Fd] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i2,gE2)
coup2R = cplcFdFdAhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFFV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFd(i1).gt. epsfmass).and. (MFd(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFdFdAhL(i2,i1,gE1)
coup1R = cplcFdFdAhR(i2,i1,gE1)
coup2L = cplcFdFdAhL(i1,i2,gE2)
coup2R = cplcFdFdAhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFbFbV(p2,MFd2(i1),MFd2(i2),Qscale)*MFd(i1)*MFd(i2)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
! ---- Fu,bar[Fu],Fu,VG,bar[Fu] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i2,gE2)
coup2R = cplcFuFuAhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFFV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFu(i1).gt. epsfmass).and. (MFu(i2).gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,2
   Do gE2=1,2
coup1L = cplcFuFuAhL(i2,i1,gE1)
coup1R = cplcFuFuAhR(i2,i1,gE1)
coup2L = cplcFuFuAhL(i1,i2,gE2)
coup2R = cplcFuFuAhR(i1,i2,gE2)
coup3=g3
coup4=g3
prefactor=Real(4*(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4),dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= GfFbFbV(p2,MFu2(i1),MFu2(i2),Qscale)*MFu(i1)*MFu(i2)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

End do
End do
! ----- TIDY UP AND SYMMETRISE -----
do gE1=1,2
Pi2P(gE1,gE1)=Pi2P(gE1,gE1)+tempcont(gE1,gE1)*oo16Pi2*oo16Pi2
do gE2=1,gE1-1
Pi2P(gE1,gE2)=Pi2P(gE1,gE2)+0.5_dp*(tempcont(gE1,gE2)+tempcont(gE2,gE1))*oo16Pi2*oo16Pi2
Pi2P(gE2,gE1)=Pi2P(gE1,gE2)
End do
End do
Pi2P = Matmul(Pi2P,ZA)
Pi2P = Matmul(Transpose(ZA),Pi2P)
End Subroutine CalculatePi2S
End Module Pole2L_MSSM 
 
