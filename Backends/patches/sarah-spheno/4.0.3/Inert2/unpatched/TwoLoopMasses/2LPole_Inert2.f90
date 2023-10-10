Module Pole2L_Inert2 
 
Use Control 
Use Settings 
Use Couplings_Inert2 
Use AddLoopFunctions 
Use LoopFunctions 
Use Mathematics 
Use MathematicsQP 
Use Model_Data_Inert2 
Use StandardModel 
Use TreeLevelMasses_Inert2 
Use Pole2LFunctions
Contains 
 
Subroutine CalculatePi2S(p2,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,             & 
& MHD2,MHU2,kont,tad2L,Pi2S,Pi2P)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(in) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(in) :: v

Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Complex(dp) :: cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp(2,2),cplG0G0hh,cplG0H0H0,          & 
& cplH0H0hh,cplH0HpcHp(2,2),cplhhhhhh,cplhhHpcHp(2,2),cplVGVGVG,cplcFdFdG0L(3,3),        & 
& cplcFdFdG0R(3,3),cplcFdFdhhL(3,3),cplcFdFdhhR(3,3),cplcFuFdHpL(3,3,2),cplcFuFdHpR(3,3,2),& 
& cplcFeFeG0L(3,3),cplcFeFeG0R(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),cplcFvFeHpL(3,3,2),& 
& cplcFvFeHpR(3,3,2),cplcFuFuG0L(3,3),cplcFuFuG0R(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),& 
& cplcFdFucHpL(3,3,2),cplcFdFucHpR(3,3,2),cplcFeFvcHpL(3,3,2),cplcFeFvcHpR(3,3,2),       & 
& cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp) :: cplA0A0A0A0,cplA0A0G0G0,cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp(2,2),        & 
& cplA0G0G0H0,cplA0G0H0hh,cplA0G0HpcHp(2,2),cplA0H0hhhh,cplA0hhHpcHp(2,2),               & 
& cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,cplG0G0HpcHp(2,2),cplG0H0H0hh,cplG0H0HpcHp(2,2),   & 
& cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp(2,2),cplH0hhHpcHp(2,2),cplhhhhhhhh,               & 
& cplhhhhHpcHp(2,2),cplHpHpcHpcHp(2,2,2,2)

Real(dp), Intent(in) :: p2
Integer, Intent(inout):: kont
Integer :: gE1,gE2,i,i1,i2,i3,i4,i5 
Real(dp) :: Qscale,prefactor,funcvalue
complex(dp) :: cplxprefactor,A0m
Real(dp)  :: temptad(1)
Real(dp)  :: tempcont(1,1)
Real(dp)  :: tempcontah(1,1)
Real(dp)  :: runningval(1,1)
Real(dp), Intent(out) :: tad2l(1)
Real(dp), Intent(out) :: Pi2S(1,1)
Real(dp), Intent(out) :: Pi2P(1,1)
complex(dp) :: coup1,coup2,coup3,coup4
complex(dp) :: coup1L,coup1R,coup2l,coup2r,coup3l,coup3r,coup4l,coup4r
real(dp) :: epsFmass
real(dp) :: epscouplings
Real(dp)  :: tempcouplingvector(1)
Real(dp)  :: tempcouplingmatrix(1,1)
Real(dp)  :: tempcouplingmatrixah(1,1)
logical :: nonzerocoupling
real(dp) :: delta2Ltadpoles(1)
real(dp)  :: delta2Lmasses(1,1)
real(dp)  :: delta2Lmassesah(1,1)
Real(dp)  :: tad1LG(1)
complex(dp) :: tad1LmatrixHp(2,2)
complex(dp) :: tad1LmatrixG0(1,1)
complex(dp) :: tad1Lmatrixhh(1,1)


tad2l(:)=0
Pi2S(:,:)=0
Pi2P(:,:)=0
Qscale=getrenormalizationscale()
epsfmass=0._dp
epscouplings=1.0E-6_dp
Call TreeMassesEffPot(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,               & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,.True.,kont)

If (Abs(MG02/Qscale).lt.TwoLoopRegulatorMass) MG02=Qscale*TwoLoopRegulatorMass
If (Abs(Mhh2/Qscale).lt.TwoLoopRegulatorMass) Mhh2=Qscale*TwoLoopRegulatorMass
If (Abs(MA02/Qscale).lt.TwoLoopRegulatorMass) MA02=Qscale*TwoLoopRegulatorMass
If (Abs(MH02/Qscale).lt.TwoLoopRegulatorMass) MH02=Qscale*TwoLoopRegulatorMass
Where (Abs(MHp2/Qscale).lt.TwoLoopRegulatorMass )MHp2=Qscale*TwoLoopRegulatorMass
Call CouplingsFor2LPole3(lam5,v,lam3,lam4,ZP,lam1,g3,Yd,ZDL,ZDR,Yu,ZUL,               & 
& ZUR,Ye,ZEL,ZER,cplA0A0G0,cplA0A0hh,cplA0G0H0,cplA0H0hh,cplA0HpcHp,cplG0G0hh,           & 
& cplG0H0H0,cplH0H0hh,cplH0HpcHp,cplhhhhhh,cplhhHpcHp,cplVGVGVG,cplcFdFdG0L,             & 
& cplcFdFdG0R,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,cplcFeFeG0L,               & 
& cplcFeFeG0R,cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuG0L,               & 
& cplcFuFuG0R,cplcFuFuhhL,cplcFuFuhhR,cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,            & 
& cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,cplcFuFuVGL,cplcFuFuVGR)

Call CouplingsFor2LPole4(lam2,lam5,lam3,lam4,ZP,lam1,cplA0A0A0A0,cplA0A0G0G0,         & 
& cplA0A0G0hh,cplA0A0H0H0,cplA0A0hhhh,cplA0A0HpcHp,cplA0G0G0H0,cplA0G0H0hh,              & 
& cplA0G0HpcHp,cplA0H0hhhh,cplA0hhHpcHp,cplG0G0G0G0,cplG0G0H0H0,cplG0G0hhhh,             & 
& cplG0G0HpcHp,cplG0H0H0hh,cplG0H0HpcHp,cplH0H0H0H0,cplH0H0hhhh,cplH0H0HpcHp,            & 
& cplH0hhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp)

! ----------------------------------
! ------- 1L GAUGELESS TADPOLE DIAGRAMS --------
! ----------------------------------
delta2Ltadpoles(:)=0._dp
delta2Lmasses(:,:)=0._dp
delta2LmassesAh(:,:)=0._dp
tad1LG(:)=0._dp
if(include1l2lshift) then
temptad(:) = 0._dp 
A0m = 1._dp/2._dp*(-J0(MA02,qscale)) 
  Do gE1 = 1, 1
coup1 = cplA0A0hh
   temptad(gE1) = temptad(gE1)-real(coup1*A0m,dp) 
  End Do 
  Do i1 = 1, 3
A0m = 3._dp*(-J0(MFd2(i1),qscale)) 
  Do gE1 = 1, 1
coup1L = cplcFdFdhhL(i1,i1)
coup1R = cplcFdFdhhR(i1,i1)
  temptad(gE1)  = temptad(gE1)+ 2._dp*MFd(i1)*real((coup1L+coup1R)*A0m,dp) 
  End Do 
  End do 

  Do i1 = 1, 3
A0m = 1._dp*(-J0(MFe2(i1),qscale)) 
  Do gE1 = 1, 1
coup1L = cplcFeFehhL(i1,i1)
coup1R = cplcFeFehhR(i1,i1)
  temptad(gE1)  = temptad(gE1)+ 2._dp*MFe(i1)*real((coup1L+coup1R)*A0m,dp) 
  End Do 
  End do 

  Do i1 = 1, 3
A0m = 3._dp*(-J0(MFu2(i1),qscale)) 
  Do gE1 = 1, 1
coup1L = cplcFuFuhhL(i1,i1)
coup1R = cplcFuFuhhR(i1,i1)
  temptad(gE1)  = temptad(gE1)+ 2._dp*MFu(i1)*real((coup1L+coup1R)*A0m,dp) 
  End Do 
  End do 

A0m = 1._dp/2._dp*(-J0(MG02,qscale)) 
  Do gE1 = 1, 1
coup1 = cplG0G0hh
   temptad(gE1) = temptad(gE1)-real(coup1*A0m,dp) 
  End Do 
A0m = 1._dp/2._dp*(-J0(MH02,qscale)) 
  Do gE1 = 1, 1
coup1 = cplH0H0hh
   temptad(gE1) = temptad(gE1)-real(coup1*A0m,dp) 
  End Do 
A0m = 1._dp/2._dp*(-J0(Mhh2,qscale)) 
  Do gE1 = 1, 1
coup1 = cplhhhhhh
   temptad(gE1) = temptad(gE1)-real(coup1*A0m,dp) 
  End Do 
  Do i1 = 1, 2
A0m = 1._dp*(-J0(MHp2(i1),qscale)) 
  Do gE1 = 1, 1
coup1 = cplhhHpcHp(i1,i1)
   temptad(gE1) = temptad(gE1)-real(coup1*A0m,dp) 
  End Do 
  End do 

tad1LG=temptad*oo16Pi2
! ----------------------------
! ----------------------------------
! ------- 1L2L SHIFTS --------
! ----------------------------------
tad1LmatrixHp=0._dp
tad1LmatrixHp(2,2)=tad1LmatrixHp(2,2)+1/v*tad1LG(1)
tad1LmatrixHp=matmul(ZP,matmul(tad1LmatrixHp,transpose(ZP)))
do i1=1,2
do i2=1,2
 funcvalue= tad1LmatrixHp(i2,i1)*BB(MHp2(i1),MHp2(i2),qscale)
do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
delta2Ltadpoles(gE1)=delta2Ltadpoles(gE1)+real(0.5_dp*coup1*2._dp*funcvalue,dp)
end do
do gE1=1,1
do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(0.5_dp*coup1*2._dp*funcvalue,dp)
end do
 end do
end do 
 end do
do i1=1,2
do i2=1,2
do i3=1,2
 funcvalue= tad1LmatrixHp(i2,i3)*CCtilde(MHp2(i1),MHp2(i2),MHp2(i3),qscale)
do gE1=1,1
do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(coup1*coup2*2._dp*funcvalue,dp)
end do
 end do
end do 
 end do
 end do
tad1LmatrixG0=0._dp
tad1LmatrixG0(1,1)=tad1LmatrixG0(1,1)+1/v*tad1LG(1)
do i1=1,1
do i2=1,1
 funcvalue= tad1LmatrixG0(i2,i1)*BB(MG02,MG02,qscale)
do gE1=1,1
coup1 = cplG0G0hh
delta2Ltadpoles(gE1)=delta2Ltadpoles(gE1)+real(0.5_dp*coup1*1._dp*funcvalue,dp)
end do
do gE1=1,1
do gE2=1,1
coup1 = cplG0G0hhhh
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(0.5_dp*coup1*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
do i1=1,1
do i2=1,1
do i3=1,1
 funcvalue= tad1LmatrixG0(i2,i3)*CCtilde(MG02,MG02,MG02,qscale)
do gE1=1,1
do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(coup1*coup2*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
 end do
do i1=1,1
do i2=1,1
do i3=1,1
 funcvalue= tad1LmatrixG0(i2,i3)*CCtilde(Mhh2,MG02,MG02,Qscale)
do gE1=1,1
do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
delta2LmassesAh(gE1,gE2)=delta2LmassesAh(gE1,gE2)+real(coup1*coup2*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
 end do
tad1Lmatrixhh=0._dp
tad1Lmatrixhh(1,1)=tad1Lmatrixhh(1,1)+1/v*tad1LG(1)
do i1=1,1
do i2=1,1
 funcvalue= tad1Lmatrixhh(i2,i1)*BB(Mhh2,Mhh2,qscale)
do gE1=1,1
coup1 = cplhhhhhh
delta2Ltadpoles(gE1)=delta2Ltadpoles(gE1)+real(0.5_dp*coup1*1._dp*funcvalue,dp)
end do
do gE1=1,1
do gE2=1,1
coup1 = cplhhhhhhhh
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(0.5_dp*coup1*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
do i1=1,1
do i2=1,1
do i3=1,1
 funcvalue= tad1Lmatrixhh(i2,i3)*CCtilde(Mhh2,Mhh2,Mhh2,qscale)
do gE1=1,1
do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
delta2Lmasses(gE1,gE2)=delta2Lmasses(gE1,gE2)+real(coup1*coup2*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
 end do
do i1=1,1
do i2=1,1
do i3=1,1
 funcvalue= tad1Lmatrixhh(i2,i3)*CCtilde(MG02,Mhh2,Mhh2,Qscale)
do gE1=1,1
do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
delta2LmassesAh(gE1,gE2)=delta2LmassesAh(gE1,gE2)+real(coup1*coup2*1._dp*funcvalue,dp)
end do
 end do
end do 
 end do
 end do
delta2Ltadpoles=delta2Ltadpoles*oo16Pi2
delta2Lmasses=delta2Lmasses*oo16Pi2
delta2LmassesAh=delta2LmassesAh*oo16Pi2
! ----------------------------
end if ! include1l2lshift
! ----------------------------------
! ------- TADPOLE DIAGRAMS --------
! ----------------------------------
temptad(:)=0._dp
tempcouplingvector(:)=0._dp
! ---- Topology ToSSS
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0G0hh
coup2 = cplA0A0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MA02,MA02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MA02,MA02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0G0H0hh
coup2 = cplA0G0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(MA02,MG02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(MA02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0hhHpcHp(i2,i3)
coup2 = cplA0HpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(MA02,MHp2(i2),MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MG02,MG02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0H0H0hh
coup2 = cplG0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MG02,MH02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MH02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0hhHpcHp(i2,i3)
coup2 = cplH0HpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(MH02,MHp2(i2),MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/6._dp*TfSSS(Mhh2,Mhh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhHpcHp(i2,i3)
coup2 = cplhhHpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(Mhh2,MHp2(i2),MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Topology ToSS
! ---- A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0A0A0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MA02,MA02,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MA02,MA02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MA02,MA02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MA02,MA02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MA02,MA02,MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
! ---- A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0G0G0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MA02,MH02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MA02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MG02,MG02,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MG02,MG02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MG02,MG02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MG02,MG02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MG02,MG02,MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
! ---- H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MH02,MH02,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MH02,MH02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MH02,MH02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MH02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MH02,MH02,MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
! ---- hh,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(Mhh2,Mhh2,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(Mhh2,Mhh2,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(Mhh2,Mhh2,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(Mhh2,Mhh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhHpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(Mhh2,Mhh2,MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
! ---- Hp,conj[Hp],A0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0A0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2(i1),MHp2(i2),MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],G0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplG0G0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2(i1),MHp2(i2),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],H0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0H0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2(i1),MHp2(i2),MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],hh ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhhhHpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2(i1),MHp2(i2),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplHpHpcHpcHp(i2,i3,i1,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSS(MHp2(i1),MHp2(i2),MHp2(i3),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
end do
! ---- Topology ToSSSS
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MA02,MA02,MA02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MA02,MA02,MA02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MA02,MA02,MG02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MA02,MA02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0A0hh
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0A0G0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MA02,MH02,MA02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MA02,MH02,MA02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0G0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MA02,MH02,MG02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MA02,MH02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- A0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplA0H0hh
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MA02,MH02,MHp2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(MG02,MG02,MA02,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MG02,MG02,MA02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MG02,MG02,MG02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(MG02,MG02,MH02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MH02,MH02,MA02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MH02,MH02,MA02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MH02,MH02,MG02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MH02,MH02,MH02,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplH0H0hh
coup2 = cplH0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(Mhh2,Mhh2,MA02,MA02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(Mhh2,Mhh2,MA02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(Mhh2,Mhh2,MG02,MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(Mhh2,Mhh2,MH02,MH02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(Mhh2,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],A0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i4,i1)
coup3 = cplA0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MHp2(i1),MHp2(i2),MA02,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],H0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i4,i1)
coup3 = cplH0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MHp2(i1),MHp2(i2),MH02,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],hh,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i4,i1)
coup3 = cplhhHpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MHp2(i1),MHp2(i2),Mhh2,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
end do
! ---- Topology ToSSFF
! ---- G0,G0,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i3)*MFd(i4)*TfSSFbFb(MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- G0,G0,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSFF(MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= MFe(i3)*MFe(i4)*TfSSFbFb(MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- G0,G0,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i3)*MFu(i4)*TfSSFbFb(MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- hh,hh,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i3)*MFd(i4)*TfSSFbFb(Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- hh,hh,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSFF(Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= MFe(i3)*MFe(i4)*TfSSFbFb(Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- hh,hh,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i3)*MFu(i4)*TfSSFbFb(Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- Hp,conj[Hp],Fu,bar[Fd] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp*TfSSFF(MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFd(i4)*TfSSFbFb(MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((0._dp .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 2._dp*0._dp*MFe(i4)*TfSSFbFb(MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
end do
! ---- Topology ToFFFS
! ---- Fd,bar[Fd],Fd,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i3,i2)
coup3R = cplcFdFdG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i3)*TfFFFbS(MFd2(i1),MFd2(i2),MFd2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i3,i2)
coup3R = cplcFdFdG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i2)*TfFFbFS(MFd2(i1),MFd2(i2),MFd2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i3,i2)
coup3R = cplcFdFdG0R(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*TfFbFbFbS(MFd2(i1),MFd2(i2),MFd2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fd,bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i3)*TfFFFbS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i2)*TfFFbFS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i3,i2)
coup3R = cplcFdFdhhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*TfFbFbFbS(MFd2(i1),MFd2(i2),MFd2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fd,bar[Fd],Fu,conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3,i4)
coup2R = cplcFdFucHpR(i1,i3,i4)
coup3L = cplcFuFdHpL(i3,i2,i4)
coup3R = cplcFuFdHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i3)*TfFFFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3,i4)
coup2R = cplcFdFucHpR(i1,i3,i4)
coup3L = cplcFuFdHpL(i3,i2,i4)
coup3R = cplcFuFdHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i2)*TfFFbFS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3,i4)
coup2R = cplcFdFucHpR(i1,i3,i4)
coup3L = cplcFuFdHpL(i3,i2,i4)
coup3R = cplcFuFdHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFu(i3)*MFd(i2)*TfFbFbFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i3,i2)
coup3R = cplcFeFeG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i3)*TfFFFbS(MFe2(i1),MFe2(i2),MFe2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i3,i2)
coup3R = cplcFeFeG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i2)*TfFFbFS(MFe2(i1),MFe2(i2),MFe2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i3,i2)
coup3R = cplcFeFeG0R(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*TfFbFbFbS(MFe2(i1),MFe2(i2),MFe2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fe,bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i3)*TfFFFbS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i2)*TfFFbFS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i3,i2)
coup3R = cplcFeFehhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*TfFbFbFbS(MFe2(i1),MFe2(i2),MFe2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fe,bar[Fe],Fv,conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((0._dp .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,i3,i4)
coup2R = cplcFeFvcHpR(i1,i3,i4)
coup3L = cplcFvFeHpL(i3,i2,i4)
coup3R = cplcFvFeHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*0._dp*TfFFFbS(MFe2(i1),MFe2(i2),0._dp,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,i3,i4)
coup2R = cplcFeFvcHpR(i1,i3,i4)
coup3L = cplcFvFeHpL(i3,i2,i4)
coup3R = cplcFvFeHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i2)*TfFFbFS(MFe2(i1),MFe2(i2),0._dp,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((0._dp .gt. epsfmass) .and. (MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,i3,i4)
coup2R = cplcFeFvcHpR(i1,i3,i4)
coup3L = cplcFvFeHpL(i3,i2,i4)
coup3R = cplcFvFeHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*0._dp*MFe(i2)*TfFbFbFbS(MFe2(i1),MFe2(i2),0._dp,MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
end do
! ---- Fu,bar[Fu],Fd,Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,2
if((MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3,i4)
coup2R = cplcFuFdHpR(i1,i3,i4)
coup3L = cplcFdFucHpL(i3,i2,i4)
coup3R = cplcFdFucHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i3)*TfFFFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3,i4)
coup2R = cplcFuFdHpR(i1,i3,i4)
coup3L = cplcFdFucHpL(i3,i2,i4)
coup3R = cplcFdFucHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i2)*TfFFbFS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3,i4)
coup2R = cplcFuFdHpR(i1,i3,i4)
coup3L = cplcFdFucHpL(i3,i2,i4)
coup3R = cplcFdFucHpR(i3,i2,i4)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFu(i1)*MFu(i2)*TfFbFbFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i3,i2)
coup3R = cplcFuFuG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i3)*TfFFFbS(MFu2(i1),MFu2(i2),MFu2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i3,i2)
coup3R = cplcFuFuG0R(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i2)*TfFFbFS(MFu2(i1),MFu2(i2),MFu2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i3,i2)
coup3R = cplcFuFuG0R(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*TfFbFbFbS(MFu2(i1),MFu2(i2),MFu2(i3),MG02,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fu,bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i3,i2)
coup3R = cplcFuFuhhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i3)*TfFFFbS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i3,i2)
coup3R = cplcFuFuhhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i2)*TfFFbFS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i3,i2)
coup3R = cplcFuFuhhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*TfFbFbFbS(MFu2(i1),MFu2(i2),MFu2(i3),Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Topology ToFV
! ---- Fd ----
Do i1=1,3
if((MFd(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i1,i1)
coup1R = cplcFdFdhhR(i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(coup1L*coup2*coup3+coup1R*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -4._dp*MFd(i1)*TfFV(MFd2(i1),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
! ---- Fu ----
Do i1=1,3
if((MFu(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i1,i1)
coup1R = cplcFuFuhhR(i1,i1)
coup2 = g3
coup3 = g3
prefactor=Real(coup1L*coup2*coup3+coup1R*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -4._dp*MFu(i1)*TfFV(MFu2(i1),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
! ----------------------------
! ---- Final tadpole result --
temptad=(temptad*oo16Pi2*oo16Pi2)+delta2ltadpoles
tad2L=temptad
! ----------------------------

! ------------------------------------
! ------- CP EVEN MASS DIAGRAMS ------
! ------------------------------------
tempcont(:,:)=0._dp
tempcouplingmatrix(:,:)=0._dp
! ---- Topology WoSSSS
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0A0G0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0G0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,MG02,MG02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MG02,MG02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MG02,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,MG02,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],A0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplA0HpcHp(i4,i1)
coup3 = cplA0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),MA02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],H0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplH0HpcHp(i4,i1)
coup3 = cplH0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),MH02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],hh,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i4,i1)
coup3 = cplhhHpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),Mhh2,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Topology XoSSS
! ---- A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0A0A0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MA02,MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0G0G0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MG02,MG02,MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MH02,MH02,MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- hh,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhHpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,Mhh2,Mhh2,MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- Hp,conj[Hp],A0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplA0A0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],G0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplG0G0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],H0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplH0H0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],hh ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplhhhhHpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2 = cplHpHpcHpcHp(i2,i3,i1,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Topology YoSSSS
! ---- A0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MA02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- A0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MH02,MH02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- G0,G0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,MG02,MG02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,MG02,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,MG02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MG02,MG02,MG02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- H0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MA02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- H0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MH02,MH02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- hh,hh,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhHpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
! ---- Hp,conj[Hp],Hp,A0 ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplA0A0HpcHp(i2,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],Hp,G0 ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplG0G0HpcHp(i2,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],Hp,H0 ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplH0H0HpcHp(i2,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],Hp,hh ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplhhhhHpcHp(i2,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],Hp,Hp ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplHpHpcHpcHp(i2,i4,i3,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*YfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology ZoSSSS
! ---- A0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MA02,MA02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MA02,MA02,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplH0H0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MA02,MA02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplhhhhhh
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MA02,MA02,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplA0A0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- A0,H0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MH02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplG0G0hh
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MH02,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplhhhhhh
coup3 = cplA0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MH02,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MG02,MG02,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0H0hh
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MG02,MG02,MH02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplH0H0hh
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MG02,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplhhhhhh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MG02,MG02,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplG0G0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MG02,MG02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- H0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MH02,MH02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplhhhhhh
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MH02,MH02,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplH0H0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplhhhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,Mhh2,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp,conj[Hp] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplHpHpcHpcHp(i2,i4,i1,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology SoSSS
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0hh
coup2 = cplA0A0G0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hhhh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0hh
coup2 = cplA0G0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hhhh
coup2 = cplA0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0hhHpcHp(i2,i3)
coup2 = cplA0hhHpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MHp2(i2),MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0hh
coup2 = cplG0H0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hhhh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0hhHpcHp(i2,i3)
coup2 = cplH0hhHpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MH02,MHp2(i2),MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/6._dp*SfSSS(p2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i2,i3)
coup2 = cplhhhhHpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,Mhh2,MHp2(i2),MHp2(i3),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Topology UoSSSS
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0G0hh
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hhhh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0G0H0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hhhh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0hhHpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0A0G0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0A0hhhh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0G0H0hh
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hhhh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0hhHpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0A0G0hh
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,MG02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0G0H0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MG02,MG02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hhhh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MG02,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0hh
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0G0H0hh
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hhhh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplG0H0H0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hhhh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0hhHpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplA0G0H0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplA0H0hhhh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplG0H0H0hh
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hhhh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0hhHpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplA0A0hhhh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,Mhh2,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplA0H0hhhh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,Mhh2,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplG0G0hhhh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplH0H0hhhh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,Mhh2,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhhhh
coup3 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhHpcHp(i3,i4)
coup3 = cplhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],A0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplA0hhHpcHp(i4,i1)
coup3 = cplA0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -4._dp*UfSSSS(p2,MHp2(i1),MHp2(i2),MA02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],H0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplH0hhHpcHp(i4,i1)
coup3 = cplH0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -4._dp*UfSSSS(p2,MHp2(i1),MHp2(i2),MH02,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],hh,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhhhHpcHp(i4,i1)
coup3 = cplhhHpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -4._dp*UfSSSS(p2,MHp2(i1),MHp2(i2),Mhh2,MHp2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Topology VoSSSSS
! ---- A0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplA0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- A0,A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- A0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplH0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,MG02,MG02,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MG02,MG02,MG02,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MG02,MG02,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,MG02,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,A0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplA0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- H0,A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,A0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- H0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MA02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MA02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
coup4 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhHpcHp(i4,i5)
coup4 = cplhhHpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp,A0,conj[Hp] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplA0HpcHp(i2,i5)
coup4 = cplA0HpcHp(i5,i3)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MA02,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],Hp,H0,conj[Hp] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplH0HpcHp(i2,i5)
coup4 = cplH0HpcHp(i5,i3)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MH02,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],Hp,hh,conj[Hp] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3 = cplhhHpcHp(i2,i5)
coup4 = cplhhHpcHp(i5,i3)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),Mhh2,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology MoSSSSS
! ---- A0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MA02,MA02,MA02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MA02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MA02,MA02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,G0,A0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MG02,MA02,MG02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,G0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MG02,MA02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MA02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MA02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,hh,A0,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplhhhhhh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,Mhh2,MA02,Mhh2,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,hh,A0,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplhhhhhh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,Mhh2,MA02,Mhh2,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,Hp,A0,conj[Hp],Hp ----
Do i2=1,2
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0hh
coup2 = cplhhHpcHp(i2,i4)
coup3 = cplA0HpcHp(i5,i2)
coup4 = cplA0HpcHp(i4,i5)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MHp2(i2),MA02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- A0,A0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0G0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MA02,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0A0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,G0,H0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MH02,MG02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,G0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MH02,MG02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MH02,MA02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MH02,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplH0H0hh
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,hh,H0,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplhhhhhh
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,Mhh2,MH02,Mhh2,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,hh,H0,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplhhhhhh
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,Mhh2,MH02,Mhh2,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- A0,Hp,H0,conj[Hp],Hp ----
Do i2=1,2
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0H0hh
coup2 = cplhhHpcHp(i2,i4)
coup3 = cplA0HpcHp(i5,i2)
coup4 = cplH0HpcHp(i4,i5)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MfSSSSS(p2,MA02,MHp2(i2),MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- G0,G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MG02,MG02,MG02,MG02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,H0,G0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplH0H0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MG02,MH02,MG02,MH02,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,H0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplH0H0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MG02,MH02,MG02,MH02,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- G0,hh,G0,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplhhhhhh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MG02,Mhh2,MG02,Mhh2,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MH02,MH02,MH02,MH02,MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MH02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,hh,H0,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplhhhhhh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MH02,Mhh2,MH02,Mhh2,MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,hh,H0,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplhhhhhh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MH02,Mhh2,MH02,Mhh2,MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- H0,Hp,H0,conj[Hp],Hp ----
Do i2=1,2
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplH0H0hh
coup2 = cplhhHpcHp(i2,i4)
coup3 = cplH0HpcHp(i5,i2)
coup4 = cplH0HpcHp(i4,i5)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MH02,MHp2(i2),MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- hh,hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
coup4 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Hp,hh,conj[Hp],Hp ----
Do i2=1,2
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp(i2,i4)
coup3 = cplhhHpcHp(i5,i2)
coup4 = cplhhHpcHp(i4,i5)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,Mhh2,MHp2(i2),Mhh2,MHp2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],conj[Hp],Hp,A0 ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2 = cplhhHpcHp(i4,i2)
coup3 = cplA0HpcHp(i2,i1)
coup4 = cplA0HpcHp(i3,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MHp2(i4),MA02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],conj[Hp],Hp,H0 ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2 = cplhhHpcHp(i4,i2)
coup3 = cplH0HpcHp(i2,i1)
coup4 = cplH0HpcHp(i3,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MHp2(i4),MH02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],conj[Hp],Hp,hh ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2 = cplhhHpcHp(i4,i2)
coup3 = cplhhHpcHp(i2,i1)
coup4 = cplhhHpcHp(i3,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),MHp2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology WoSSFF
! ---- G0,G0,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSFF(p2,MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Fu,bar[Fd] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp*MFu(i3)*MFd(i4)*WfSSFbFb(p2,MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp*WfSSFF(p2,MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
if((0._dp .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*0._dp*MFe(i4)*WfSSFbFb(p2,MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology MoFFFFS
! ---- Fd,bar[Fd],bar[Fd],Fd,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fu],bar[Fd],Fu,conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFu(i4)*MFd(i3)*MFu(i2)*MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFu(i2)*MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fd],bar[Fu],Fd,Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFu(i1)*MFd(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Topology MoSFSFF
! ---- G0,Fd,G0,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,MG02,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MG02,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MG02,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- G0,Fe,G0,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,MG02,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MG02,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,MG02,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- G0,Fu,G0,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,MG02,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MG02,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MG02,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fd,hh,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,Mhh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,Mhh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,Mhh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fe,hh,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,Mhh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,Mhh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,Mhh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fu,hh,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,Mhh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,Mhh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,Mhh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Hp,Fd,conj[Hp],bar[Fd],Fu ----
Do i1=1,2
Do i2=1,3
Do i3=1,2
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5,i1)
coup3R = cplcFdFucHpR(i2,i5,i1)
coup4L = cplcFuFdHpL(i5,i4,i3)
coup4R = cplcFuFdHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFu(i5)*MFd(i4)*MfSFbSFbFb(p2,MHp2(i1),MFd2(i2),MHp2(i3),MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5,i1)
coup3R = cplcFdFucHpR(i2,i5,i1)
coup4L = cplcFuFdHpL(i5,i4,i3)
coup4R = cplcFuFdHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MHp2(i1),MFd2(i2),MHp2(i3),MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5,i1)
coup3R = cplcFdFucHpR(i2,i5,i1)
coup4L = cplcFuFdHpL(i5,i4,i3)
coup4R = cplcFuFdHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MHp2(i1),MFd2(i2),MHp2(i3),MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
end do
end do
! ---- Hp,Fe,conj[Hp],bar[Fe],Fv ----
Do i1=1,2
Do i2=1,3
Do i3=1,2
Do i4=1,3
Do i5=1,3
if((0._dp .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFvcHpL(i2,i5,i1)
coup3R = cplcFeFvcHpR(i2,i5,i1)
coup4L = cplcFvFeHpL(i5,i4,i3)
coup4R = cplcFvFeHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*0._dp*MFe(i4)*MfSFbSFbFb(p2,MHp2(i1),MFe2(i2),MHp2(i3),MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFvcHpL(i2,i5,i1)
coup3R = cplcFeFvcHpR(i2,i5,i1)
coup4L = cplcFvFeHpL(i5,i4,i3)
coup4R = cplcFvFeHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MHp2(i1),MFe2(i2),MHp2(i3),MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((0._dp .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFvcHpL(i2,i5,i1)
coup3R = cplcFeFvcHpR(i2,i5,i1)
coup4L = cplcFvFeHpL(i5,i4,i3)
coup4R = cplcFvFeHpR(i5,i4,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*0._dp*MfSFSFFb(p2,MHp2(i1),MFe2(i2),MHp2(i3),MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
end do
end do
! ---- Hp,bar[Fu],conj[Hp],Fu,bar[Fd] ----
Do i1=1,2
Do i2=1,3
Do i3=1,2
Do i4=1,3
Do i5=1,3
if((MFd(i5) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2,i1)
coup3R = cplcFdFucHpR(i5,i2,i1)
coup4L = cplcFuFdHpL(i4,i5,i3)
coup4R = cplcFuFdHpR(i4,i5,i3)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFd(i5)*MFu(i2)*MfSFbSFbFb(p2,MHp2(i1),MFu2(i2),MHp2(i3),MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2,i1)
coup3R = cplcFdFucHpR(i5,i2,i1)
coup4L = cplcFuFdHpL(i4,i5,i3)
coup4R = cplcFuFdHpR(i4,i5,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MHp2(i1),MFu2(i2),MHp2(i3),MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i3)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2,i1)
coup3R = cplcFdFucHpR(i5,i2,i1)
coup4L = cplcFuFdHpL(i4,i5,i3)
coup4R = cplcFuFdHpR(i4,i5,i3)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MHp2(i1),MFu2(i2),MHp2(i3),MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
end do
end do
! ---- Topology VoSSSFF
! ---- G0,G0,G0,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdG0L(i5,i4)
coup3R = cplcFdFdG0R(i5,i4)
coup4L = cplcFdFdG0L(i4,i5)
coup4R = cplcFdFdG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,MG02,MG02,MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdG0L(i5,i4)
coup3R = cplcFdFdG0R(i5,i4)
coup4L = cplcFdFdG0L(i4,i5)
coup4R = cplcFdFdG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,MG02,MG02,MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,G0,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFeG0L(i5,i4)
coup3R = cplcFeFeG0R(i5,i4)
coup4L = cplcFeFeG0L(i4,i5)
coup4R = cplcFeFeG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,MG02,MG02,MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFeG0L(i5,i4)
coup3R = cplcFeFeG0R(i5,i4)
coup4L = cplcFeFeG0L(i4,i5)
coup4R = cplcFeFeG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSFF(p2,MG02,MG02,MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- G0,G0,G0,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuG0L(i5,i4)
coup3R = cplcFuFuG0R(i5,i4)
coup4L = cplcFuFuG0L(i4,i5)
coup4R = cplcFuFuG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,MG02,MG02,MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuG0L(i5,i4)
coup3R = cplcFuFuG0R(i5,i4)
coup4L = cplcFuFuG0L(i4,i5)
coup4R = cplcFuFuG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,MG02,MG02,MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFdFdhhL(i5,i4)
coup3R = cplcFdFdhhR(i5,i4)
coup4L = cplcFdFdhhL(i4,i5)
coup4R = cplcFdFdhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,Mhh2,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFdFdhhL(i5,i4)
coup3R = cplcFdFdhhR(i5,i4)
coup4L = cplcFdFdhhL(i4,i5)
coup4R = cplcFdFdhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFeFehhL(i5,i4)
coup3R = cplcFeFehhR(i5,i4)
coup4L = cplcFeFehhL(i4,i5)
coup4R = cplcFeFehhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,Mhh2,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFeFehhL(i5,i4)
coup3R = cplcFeFehhR(i5,i4)
coup4L = cplcFeFehhL(i4,i5)
coup4R = cplcFeFehhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSFF(p2,Mhh2,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,hh,hh,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFuFuhhL(i5,i4)
coup3R = cplcFuFuhhR(i5,i4)
coup4L = cplcFuFuhhL(i4,i5)
coup4R = cplcFuFuhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,Mhh2,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3L = cplcFuFuhhL(i5,i4)
coup3R = cplcFuFuhhR(i5,i4)
coup4L = cplcFuFuhhL(i4,i5)
coup4R = cplcFuFuhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp,Fd,bar[Fu] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3L = cplcFuFdHpL(i5,i4,i2)
coup3R = cplcFuFdHpR(i5,i4,i2)
coup4L = cplcFdFucHpL(i4,i5,i3)
coup4R = cplcFdFucHpR(i4,i5,i3)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFu(i5)*VfSSSFbFb(p2,MHp2(i1),MHp2(i2),MHp2(i3),MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3L = cplcFuFdHpL(i5,i4,i2)
coup3R = cplcFuFdHpR(i5,i4,i2)
coup4L = cplcFdFucHpL(i4,i5,i3)
coup4R = cplcFdFucHpR(i4,i5,i3)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfSSSFF(p2,MHp2(i1),MHp2(i2),MHp2(i3),MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Hp,conj[Hp],Hp,Fe,bar[Fv] ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
Do i4=1,3
Do i5=1,3
if((0._dp .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3L = cplcFvFeHpL(i5,i4,i2)
coup3R = cplcFvFeHpR(i5,i4,i2)
coup4L = cplcFeFvcHpL(i4,i5,i3)
coup4R = cplcFeFvcHpR(i4,i5,i3)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*0._dp*VfSSSFbFb(p2,MHp2(i1),MHp2(i2),MHp2(i3),MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp(i1,i2)
coup2 = cplhhHpcHp(i3,i1)
coup3L = cplcFvFeHpL(i5,i4,i2)
coup3R = cplcFvFeHpR(i5,i4,i2)
coup4L = cplcFeFvcHpL(i4,i5,i3)
coup4R = cplcFeFvcHpR(i4,i5,i3)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSFF(p2,MHp2(i1),MHp2(i2),MHp2(i3),MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Topology VoFFFFS
! ---- Fd,bar[Fd],Fd,bar[Fd],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],Fd,bar[Fd],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],Fd,bar[Fu],Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFu(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFu(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fv],Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((0._dp .gt. epsfmass) .and. (MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*0._dp*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((0._dp .gt. epsfmass) .and. (MFe(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*0._dp*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((0._dp .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*0._dp*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fd],conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFd(i4)*MFu(i2)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFd(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFd(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Topology GoFFFFV
! ---- Fd,bar[Fd] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i2)
coup2R = cplcFdFdhhR(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*GfFFV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i2)
coup2R = cplcFdFdhhR(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFd(i1)*MFd(i2)*GfFbFbV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
! ---- Fu,bar[Fu] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i2)
coup2R = cplcFuFuhhR(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*GfFFV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i2)
coup2R = cplcFuFuhhR(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrix(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrix(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFu(i1)*MFu(i2)*GfFbFbV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
Pi2S(1,1)=tempcont(1,1)*oo16Pi2*oo16Pi2+delta2lmasses(1,1)

! -----------------------------------
! ------- CP ODD MASS DIAGRAMS ------
! -----------------------------------
tempcontah(:,:)=0._dp
tempcouplingmatrixah(:,:)=0._dp
! ---- Topology WoSSSS
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0A0G0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0A0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0G0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MA02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,MG02,MG02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MG02,MG02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MG02,MG02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,MG02,MG02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplG0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplH0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0A0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplH0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplhhhhhh
coup3 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplhhHpcHp(i3,i4)
coup3 = cplhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],A0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplA0HpcHp(i4,i1)
coup3 = cplA0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),MA02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],H0,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplH0HpcHp(i4,i1)
coup3 = cplH0HpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),MH02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
! ---- Hp,conj[Hp],hh,Hp ----
Do i1=1,2
Do i2=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplhhHpcHp(i4,i1)
coup3 = cplhhHpcHp(i2,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSSS(p2,MHp2(i1),MHp2(i2),Mhh2,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
! ---- Topology XoSSS
! ---- A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0A0A0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MA02,MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0G0G0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MG02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MG02,MG02,MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplA0A0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplH0H0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplH0H0HpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MH02,MH02,MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- hh,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplA0A0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplH0H0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplhhhhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,hh,Hp ----
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplhhhhHpcHp(i3,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,Mhh2,Mhh2,MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- Hp,conj[Hp],A0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplA0A0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],G0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplG0G0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],H0 ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplH0H0HpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],hh ----
Do i1=1,2
Do i2=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplhhhhHpcHp(i2,i1)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2(i1),MHp2(i2),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp ----
Do i1=1,2
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2 = cplHpHpcHpcHp(i2,i3,i1,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*XfSSS(p2,MHp2(i1),MHp2(i2),MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
! ---- Topology YoSSSS
! ---- A0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MA02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- A0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplH0H0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MA02,MH02,MH02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- G0,hh,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,Mhh2,Mhh2,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,Mhh2,Mhh2,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,Mhh2,Mhh2,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplhhhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MG02,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplhhhhHpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MG02,Mhh2,Mhh2,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- H0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MA02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- H0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0G0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,MH02,MH02,MH02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- hh,G0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,MG02,MG02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0G0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,MG02,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,MG02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,MG02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,Hp ----
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0HpcHp(i4,i4)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*YfSSSS(p2,Mhh2,MG02,MG02,MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
! ---- Topology ZoSSSS
! ---- A0,A0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0A0A0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MA02,MA02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0A0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MA02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0H0H0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MA02,MA02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MA02,MH02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0G0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*ZfSSSS(p2,MA02,MH02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MG02,Mhh2,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0G0H0
coup3 = cplA0G0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*ZfSSSS(p2,MG02,Mhh2,MH02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MG02,Mhh2,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MH02,MH02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,hh,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0G0hh
coup3 = cplG0H0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*ZfSSSS(p2,MH02,MH02,Mhh2,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- Topology SoSSS
! ---- A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0G0
coup2 = cplA0A0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0hh
coup2 = cplA0A0G0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0G0H0
coup2 = cplA0G0G0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0hh
coup2 = cplA0G0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0HpcHp(i2,i3)
coup2 = cplA0G0HpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MA02,MHp2(i2),MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2 = cplG0G0G0G0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/6._dp*SfSSS(p2,MG02,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0H0H0
coup2 = cplG0G0H0H0
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MG02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2 = cplG0G0hhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MG02,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i2,i3)
coup2 = cplG0G0HpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MG02,MHp2(i2),MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0hh
coup2 = cplG0H0H0hh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*SfSSS(p2,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,Hp,conj[Hp] ----
Do i2=1,2
Do i3=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0HpcHp(i2,i3)
coup2 = cplG0H0HpcHp(i3,i2)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*SfSSS(p2,MH02,MHp2(i2),MHp2(i3),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Topology UoSSSS
! ---- A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0G0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0HpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0A0G0G0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0A0G0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0G0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MA02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0A0G0G0
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,Mhh2,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0G0G0H0
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MG02,Mhh2,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0G0G0
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,Mhh2,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0H0H0
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,Mhh2,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hhhh
coup3 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,MG02,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0HpcHp(i3,i4)
coup3 = cplhhHpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MG02,Mhh2,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0G0H0
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0hh
coup3 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0H0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0HpcHp(i3,i4)
coup3 = cplA0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MA02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplA0G0G0H0
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplA0G0H0hh
coup3 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0G0H0H0
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0hh
coup3 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,Hp,conj[Hp] ----
Do i3=1,2
Do i4=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0HpcHp(i3,i4)
coup3 = cplH0HpcHp(i4,i3)
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,MH02,MH02,MHp2(i3),MHp2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0A0G0hh
coup3 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,MG02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplA0G0H0hh
coup3 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,MG02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hhhh
coup3 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,MG02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0hh
coup3 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,MG02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- Topology VoSSSSS
! ---- A0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplA0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MA02,MA02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- A0,A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MA02,MA02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- A0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplH0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MA02,MH02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,hh,hh,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplhhhhhh
coup4 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplhhHpcHp(i4,i5)
coup4 = cplhhHpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MG02,Mhh2,Mhh2,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,A0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplA0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MA02,MA02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,A0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,A0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfSSSSS(p2,MH02,MA02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- H0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,Hp,conj[Hp] ----
Do i4=1,2
Do i5=1,2
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0HpcHp(i4,i5)
coup4 = cplH0HpcHp(i5,i4)
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,MH02,MH02,MH02,MHp2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,G0,G0,A0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,MG02,MG02,MA02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,A0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,Mhh2,MG02,MG02,MA02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,G0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSSS(p2,Mhh2,MG02,MG02,MG02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- hh,G0,G0,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,MG02,MG02,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- Topology MoSSSSS
! ---- A0,A0,A0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0G0
coup4 = cplA0A0G0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MA02,MA02,MA02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0A0G0
coup3 = cplA0A0hh
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MA02,MA02,MA02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MA02,MA02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplA0G0H0
coup3 = cplA0A0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MA02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,G0,A0,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0A0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MA02,Mhh2,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,G0,A0,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MA02,Mhh2,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,A0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MA02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,A0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0A0G0
coup2 = cplG0H0H0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MA02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0G0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MA02,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,A0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0A0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MA02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,G0,H0,hh,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0A0G0
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MH02,Mhh2,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,G0,H0,hh,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0G0H0
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MG02,MH02,Mhh2,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,A0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0G0H0
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MH02,MA02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,A0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplA0G0H0
coup3 = cplA0H0hh
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MA02,MH02,MH02,MA02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0G0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MH02,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0H0H0
coup3 = cplA0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,hh,H0,G0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0A0hh
coup4 = cplA0G0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,Mhh2,MH02,MG02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- A0,hh,H0,G0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplA0G0H0
coup2 = cplG0G0hh
coup3 = cplA0H0hh
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MA02,Mhh2,MH02,MG02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,G0,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplhhhhhh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MG02,MG02,Mhh2,Mhh2,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,H0,hh,H0,A0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplA0G0H0
coup4 = cplA0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MG02,MH02,Mhh2,MH02,MA02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,H0,hh,H0,H0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0H0H0
coup3 = cplG0H0H0
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MfSSSSS(p2,MG02,MH02,Mhh2,MH02,MH02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- G0,hh,hh,G0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3 = cplG0G0hh
coup4 = cplG0G0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfSSSSS(p2,MG02,Mhh2,Mhh2,MG02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,H0,G0 ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplG0H0H0
coup4 = cplG0H0H0
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MH02,MH02,MH02,MH02,MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- H0,H0,H0,H0,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0H0H0
coup2 = cplG0H0H0
coup3 = cplH0H0hh
coup4 = cplH0H0hh
prefactor=Real(coup1*coup2*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MH02,MH02,MH02,MH02,Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
! ---- Topology WoSSFF
! ---- G0,G0,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFdFdG0L(i4,i3)
coup2R = cplcFdFdG0R(i4,i3)
coup3L = cplcFdFdG0L(i3,i4)
coup3R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MG02,MG02,MFd2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,G0,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFeFeG0L(i4,i3)
coup2R = cplcFeFeG0R(i4,i3)
coup3L = cplcFeFeG0L(i3,i4)
coup3R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSFF(p2,MG02,MG02,MFe2(i3),MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,G0,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0G0G0
coup2L = cplcFuFuG0L(i4,i3)
coup2R = cplcFuFuG0R(i4,i3)
coup3L = cplcFuFuG0L(i3,i4)
coup3R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MG02,MG02,MFu2(i3),MFu2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,hh,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFdFdhhL(i4,i3)
coup2R = cplcFdFdhhR(i4,i3)
coup3L = cplcFdFdhhL(i3,i4)
coup3R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFd2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,hh,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFeFehhL(i4,i3)
coup2R = cplcFeFehhR(i4,i3)
coup3L = cplcFeFehhL(i3,i4)
coup3R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFe2(i3),MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,hh,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hhhh
coup2L = cplcFuFuhhL(i4,i3)
coup2R = cplcFuFuhhR(i4,i3)
coup3L = cplcFuFuhhL(i3,i4)
coup3R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*WfSSFF(p2,Mhh2,Mhh2,MFu2(i3),MFu2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Fu,bar[Fd] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp*MFu(i3)*MFd(i4)*WfSSFbFb(p2,MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2L = cplcFdFucHpL(i4,i3,i1)
coup2R = cplcFdFucHpR(i4,i3,i1)
coup3L = cplcFuFdHpL(i3,i4,i2)
coup3R = cplcFuFdHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -3._dp*WfSSFF(p2,MHp2(i1),MHp2(i2),MFu2(i3),MFd2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i1=1,2
Do i2=1,2
Do i3=1,3
Do i4=1,3
if((0._dp .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*0._dp*MFe(i4)*WfSSFbFb(p2,MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0HpcHp(i1,i2)
coup2L = cplcFeFvcHpL(i4,i3,i1)
coup2R = cplcFeFvcHpR(i4,i3,i1)
coup3L = cplcFvFeHpL(i3,i4,i2)
coup3R = cplcFvFeHpR(i3,i4,i2)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= -1._dp*WfSSFF(p2,MHp2(i1),MHp2(i2),0._dp,MFe2(i4),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Topology MoFFFFS
! ---- Fd,bar[Fd],bar[Fd],Fd,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdG0L(i1,i2)
coup3R = cplcFdFdG0R(i1,i2)
coup4L = cplcFdFdG0L(i4,i3)
coup4R = cplcFdFdG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],bar[Fd],Fd,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFdFdhhL(i1,i2)
coup3R = cplcFdFdhhR(i1,i2)
coup4L = cplcFdFdhhL(i4,i3)
coup4R = cplcFdFdhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fu],bar[Fd],Fu,conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i1)*MFu(i4)*MFd(i3)*MFu(i2)*MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFu(i2)*MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i3,i1)
coup1R = cplcFdFdG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFdFucHpL(i1,i2,i5)
coup3R = cplcFdFucHpR(i1,i2,i5)
coup4L = cplcFuFdHpL(i4,i3,i5)
coup4R = cplcFuFdHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFeG0L(i1,i2)
coup3R = cplcFeFeG0R(i1,i2)
coup4L = cplcFeFeG0L(i4,i3)
coup4R = cplcFeFeG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i3,i1)
coup1R = cplcFeFeG0R(i3,i1)
coup2L = cplcFeFeG0L(i2,i4)
coup2R = cplcFeFeG0R(i2,i4)
coup3L = cplcFeFehhL(i1,i2)
coup3R = cplcFeFehhR(i1,i2)
coup4L = cplcFeFehhL(i4,i3)
coup4R = cplcFeFehhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fd],bar[Fu],Fd,Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFu(i1)*MFd(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFdFdG0L(i2,i4)
coup2R = cplcFdFdG0R(i2,i4)
coup3L = cplcFuFdHpL(i1,i2,i5)
coup3R = cplcFuFdHpR(i1,i2,i5)
coup4L = cplcFdFucHpL(i4,i3,i5)
coup4R = cplcFdFucHpR(i4,i3,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuG0L(i1,i2)
coup3R = cplcFuFuG0R(i1,i2)
coup4L = cplcFuFuG0L(i4,i3)
coup4R = cplcFuFuG0R(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i3,i1)
coup1R = cplcFuFuG0R(i3,i1)
coup2L = cplcFuFuG0L(i2,i4)
coup2R = cplcFuFuG0R(i2,i4)
coup3L = cplcFuFuhhL(i1,i2)
coup3R = cplcFuFuhhR(i1,i2)
coup4L = cplcFuFuhhL(i4,i3)
coup4R = cplcFuFuhhR(i4,i3)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Topology MoSFSFF
! ---- G0,Fd,hh,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,MG02,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MG02,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdG0L(i2,i5)
coup3R = cplcFdFdG0R(i2,i5)
coup4L = cplcFdFdhhL(i5,i4)
coup4R = cplcFdFdhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MG02,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- G0,Fe,hh,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,MG02,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MG02,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFeG0L(i2,i5)
coup3R = cplcFeFeG0R(i2,i5)
coup4L = cplcFeFehhL(i5,i4)
coup4R = cplcFeFehhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,MG02,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- G0,Fu,hh,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,MG02,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MG02,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuG0L(i2,i5)
coup3R = cplcFuFuG0R(i2,i5)
coup4L = cplcFuFuhhL(i5,i4)
coup4R = cplcFuFuhhR(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MG02,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fd,G0,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,Mhh2,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,Mhh2,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFdFdG0L(i4,i2)
coup2R = cplcFdFdG0R(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdG0L(i5,i4)
coup4R = cplcFdFdG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,Mhh2,MFd2(i2),MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fe,G0,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,Mhh2,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,Mhh2,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFeFeG0L(i4,i2)
coup2R = cplcFeFeG0R(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeG0L(i5,i4)
coup4R = cplcFeFeG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,Mhh2,MFe2(i2),MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fu,G0,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3L*coup4L+coup1*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,Mhh2,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4L+coup1*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,Mhh2,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2L = cplcFuFuG0L(i4,i2)
coup2R = cplcFuFuG0R(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuG0L(i5,i4)
coup4R = cplcFuFuG0R(i5,i4)
prefactor=Real(coup1*coup2L*coup3R*coup4R+coup1*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,Mhh2,MFu2(i2),MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
end do
! ---- Topology VoSSSFF
! ---- G0,hh,hh,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdhhL(i5,i4)
coup3R = cplcFdFdhhR(i5,i4)
coup4L = cplcFdFdhhL(i4,i5)
coup4R = cplcFdFdhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,MG02,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdhhL(i5,i4)
coup3R = cplcFdFdhhR(i5,i4)
coup4L = cplcFdFdhhL(i4,i5)
coup4R = cplcFdFdhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,MG02,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,hh,hh,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFehhL(i5,i4)
coup3R = cplcFeFehhR(i5,i4)
coup4L = cplcFeFehhL(i4,i5)
coup4R = cplcFeFehhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,MG02,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFehhL(i5,i4)
coup3R = cplcFeFehhR(i5,i4)
coup4L = cplcFeFehhL(i4,i5)
coup4R = cplcFeFehhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSFF(p2,MG02,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- G0,hh,hh,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuhhL(i5,i4)
coup3R = cplcFuFuhhR(i5,i4)
coup4L = cplcFuFuhhL(i4,i5)
coup4R = cplcFuFuhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,MG02,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuhhL(i5,i4)
coup3R = cplcFuFuhhR(i5,i4)
coup4L = cplcFuFuhhL(i4,i5)
coup4R = cplcFuFuhhR(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,MG02,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,G0,G0,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdG0L(i5,i4)
coup3R = cplcFdFdG0R(i5,i4)
coup4L = cplcFdFdG0L(i4,i5)
coup4R = cplcFdFdG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,Mhh2,MG02,MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFdFdG0L(i5,i4)
coup3R = cplcFdFdG0R(i5,i4)
coup4L = cplcFdFdG0L(i4,i5)
coup4R = cplcFdFdG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,MG02,MG02,MFd2(i4),MFd2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,G0,G0,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFeG0L(i5,i4)
coup3R = cplcFeFeG0R(i5,i4)
coup4L = cplcFeFeG0L(i4,i5)
coup4R = cplcFeFeG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,Mhh2,MG02,MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFeFeG0L(i5,i4)
coup3R = cplcFeFeG0R(i5,i4)
coup4L = cplcFeFeG0L(i4,i5)
coup4R = cplcFeFeG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 1._dp*VfSSSFF(p2,Mhh2,MG02,MG02,MFe2(i4),MFe2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- hh,G0,G0,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuG0L(i5,i4)
coup3R = cplcFuFuG0R(i5,i4)
coup4L = cplcFuFuG0L(i4,i5)
coup4R = cplcFuFuG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4L+coup1*coup2*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,Mhh2,MG02,MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplG0G0hh
coup2 = cplG0G0hh
coup3L = cplcFuFuG0L(i5,i4)
coup3R = cplcFuFuG0R(i5,i4)
coup4L = cplcFuFuG0L(i4,i5)
coup4R = cplcFuFuG0R(i4,i5)
prefactor=Real(coup1*coup2*coup3L*coup4R+coup1*coup2*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,MG02,MG02,MFu2(i4),MFu2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
! ---- Topology VoFFFFS
! ---- Fd,bar[Fd],Fd,bar[Fd],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdG0L(i4,i2)
coup3R = cplcFdFdG0R(i4,i2)
coup4L = cplcFdFdG0L(i3,i4)
coup4R = cplcFdFdG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],Fd,bar[Fd],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFdFdhhL(i4,i2)
coup3R = cplcFdFdhhR(i4,i2)
coup4L = cplcFdFdhhL(i3,i4)
coup4R = cplcFdFdhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fd,bar[Fd],Fd,bar[Fu],Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFu(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFd(i3)*MFu(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i3)
coup2R = cplcFdFdG0R(i1,i3)
coup3L = cplcFuFdHpL(i4,i2,i5)
coup3R = cplcFuFdHpR(i4,i2,i5)
coup4L = cplcFdFucHpL(i3,i4,i5)
coup4R = cplcFdFucHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFeG0L(i4,i2)
coup3R = cplcFeFeG0R(i4,i2)
coup4L = cplcFeFeG0L(i3,i4)
coup4R = cplcFeFeG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFeFehhL(i4,i2)
coup3R = cplcFeFehhR(i4,i2)
coup4L = cplcFeFehhL(i3,i4)
coup4R = cplcFeFehhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fv],Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((0._dp .gt. epsfmass) .and. (MFe(i1) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*0._dp*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((0._dp .gt. epsfmass) .and. (MFe(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*0._dp*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((0._dp .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFe(i3)*0._dp*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeG0L(i2,i1)
coup1R = cplcFeFeG0R(i2,i1)
coup2L = cplcFeFeG0L(i1,i3)
coup2R = cplcFeFeG0R(i1,i3)
coup3L = cplcFvFeHpL(i4,i2,i5)
coup3R = cplcFvFeHpR(i4,i2,i5)
coup4L = cplcFeFvcHpL(i3,i4,i5)
coup4R = cplcFeFvcHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],G0 ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuG0L(i4,i2)
coup3R = cplcFuFuG0R(i4,i2)
coup4L = cplcFuFuG0L(i3,i4)
coup4R = cplcFuFuG0R(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MG02,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],hh ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFuFuhhL(i4,i2)
coup3R = cplcFuFuhhR(i4,i2)
coup4L = cplcFuFuhhL(i3,i4)
coup4R = cplcFuFuhhR(i3,i4)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),Mhh2,Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fd],conj[Hp] ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
Do i5=1,2
if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3L*coup4L+coup1R*coup2R*coup3R*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFd(i4)*MFu(i2)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4L+coup1R*coup2R*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2L*coup3R*coup4R+coup1R*coup2R*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFd(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3L*coup4R+coup1R*coup2L*coup3R*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4R+coup1R*coup2L*coup3L*coup4L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 12._dp*MFu(i3)*MFd(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i3)
coup2R = cplcFuFuG0R(i1,i3)
coup3L = cplcFdFucHpL(i4,i2,i5)
coup3R = cplcFdFucHpR(i4,i2,i5)
coup4L = cplcFuFdHpL(i3,i4,i5)
coup4R = cplcFuFdHpR(i3,i4,i5)
prefactor=Real(coup1L*coup2R*coup3R*coup4L+coup1R*coup2L*coup3L*coup4R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2(i5),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end do
end do
end do
end do
end do
! ---- Topology GoFFFFV
! ---- Fd,bar[Fd] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i2)
coup2R = cplcFdFdG0R(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*GfFFV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
if((MFd(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdG0L(i2,i1)
coup1R = cplcFdFdG0R(i2,i1)
coup2L = cplcFdFdG0L(i1,i2)
coup2R = cplcFdFdG0R(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFd(i1)*MFd(i2)*GfFbFbV(p2,MFd2(i1),MFd2(i2),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
! ---- Fu,bar[Fu] ----
Do i1=1,3
Do i2=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i2)
coup2R = cplcFuFuG0R(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2R*coup3*coup4+coup1R*coup2L*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*GfFFV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
if((MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuG0L(i2,i1)
coup1R = cplcFuFuG0R(i2,i1)
coup2L = cplcFuFuG0L(i1,i2)
coup2R = cplcFuFuG0R(i1,i2)
coup3 = g3
coup4 = g3
prefactor=Real(coup1L*coup2L*coup3*coup4+coup1R*coup2R*coup3*coup4,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingmatrixah(gE1,gE2)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingmatrixah(gE1,gE2)= 0._dp
 end if
   End Do
  End do
if(nonzerocoupling) then 
 funcvalue= 4._dp*MFu(i1)*MFu(i2)*GfFbFbV(p2,MFu2(i1),MFu2(i2),Qscale)
 tempcontah=tempcontah+tempcouplingmatrixah*funcvalue
end if
end if

end do
end do
Pi2P(1,1)=tempcontah(1,1)*oo16Pi2*oo16Pi2+delta2lmassesah(1,1)
End Subroutine CalculatePi2S
End Module Pole2L_Inert2 
 
