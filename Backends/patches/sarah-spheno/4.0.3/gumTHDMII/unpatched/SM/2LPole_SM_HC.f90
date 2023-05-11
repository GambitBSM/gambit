Module Pole2L_SM_HC
 
Use Control 
Use Settings 
Use Couplings_SM_HC
Use LoopFunctions 
Use Mathematics 
Use MathematicsQP 
! Use Model_Data_SM 
Use StandardModel 
Use TreeLevelMasses_SM_HC 
Use Pole2LFunctions
Contains 
 
Subroutine CalculatePi2S_SM(p2,v,g1,g2,g3,Lam,Yu,Yd,Ye,Mu,kont,tad2L,Pi2S,Pi2P)

Implicit None 
Real(dp),Intent(in) :: g1,g2,g3

Complex(dp),Intent(in) :: Lam,Yu(3,3),Yd(3,3),Ye(3,3),Mu

Real(dp),Intent(in) :: v

Real(dp) :: MAh,MAh2,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),Mhh,Mhh2,MHp,MHp2,              & 
& MVWp,MVWp2,MVZ,MVZ2,TW,ZZ(2,2)

Complex(dp) :: ZDR(3,3),ZER(3,3),ZUR(3,3),ZDL(3,3),ZEL(3,3),ZUL(3,3),ZW(2,2)

Complex(dp) :: cplAhAhhh,cplhhhhhh,cplhhHpcHp,cplVGVGVG,cplcFdFdAhL(3,3),cplcFdFdAhR(3,3),           & 
& cplcFeFeAhL(3,3),cplcFeFeAhR(3,3),cplcFuFuAhL(3,3),cplcFuFuAhR(3,3),cplcFdFdhhL(3,3),  & 
& cplcFdFdhhR(3,3),cplcFuFdHpL(3,3),cplcFuFdHpR(3,3),cplcFeFehhL(3,3),cplcFeFehhR(3,3),  & 
& cplcFvFeHpL(3,3),cplcFvFeHpR(3,3),cplcFuFuhhL(3,3),cplcFuFuhhR(3,3),cplcFdFucHpL(3,3), & 
& cplcFdFucHpR(3,3),cplcFeFvcHpL(3,3),cplcFeFvcHpR(3,3),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),& 
& cplcFuFuVGL(3,3),cplcFuFuVGR(3,3)

Complex(dp) :: cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpcHp,cplhhhhhhhh,cplhhhhHpcHp,cplHpHpcHpcHp

Real(dp), Intent(in) :: p2
Integer, Intent(inout):: kont
Integer :: gE1,gE2,i,i1,i2,i3,i4,i5 
Real(dp) :: Qscale,prefactor,funcvalue
complex(dp) :: cplxprefactor
Real(dp)  :: temptad(1)
Real(dp)  :: tempcont(1,1)
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
logical :: nonzerocoupling



tad2l(:)=0
Pi2S(:,:)=0
Pi2P(:,:)=0
Qscale=getrenormalizationscale()
epsfmass=0._dp
epscouplings=1.0E-6_dp
Call TreeMassesEffPot_SM(MAh,MAh2,MFd,MFd2,MFe,MFe2,MFu,MFu2,Mhh,Mhh2,MHp,               & 
& MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDR,ZER,ZUR,ZDL,ZEL,ZUL,ZW,ZZ,v,g1,g2,g3,Lam,              & 
& Yu,Yd,Ye,Mu,.True.,kont)


Call CouplingsFor2LPole3_SM(Lam,v,g3,Yd,ZDL,ZDR,Ye,ZEL,ZER,Yu,ZUL,ZUR,cplAhAhhh,         & 
& cplhhhhhh,cplhhHpcHp,cplVGVGVG,cplcFdFdAhL,cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,        & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFuFdHpL,cplcFuFdHpR,               & 
& cplcFeFehhL,cplcFeFehhR,cplcFvFeHpL,cplcFvFeHpR,cplcFuFuhhL,cplcFuFuhhR,               & 
& cplcFdFucHpL,cplcFdFucHpR,cplcFeFvcHpL,cplcFeFvcHpR,cplcFdFdVGL,cplcFdFdVGR,           & 
& cplcFuFuVGL,cplcFuFuVGR)

Call CouplingsFor2LPole4_SM(Lam,cplAhAhAhAh,cplAhAhhhhh,cplAhAhHpcHp,cplhhhhhhhh,        & 
& cplhhhhHpcHp,cplHpHpcHpcHp)


cplAhAhAhAh=0._dp
cplAhAhhhhh=0._dp
cplAhAhHpcHp=0._dp
cplhhhhhhhh=0._dp
cplhhhhHpcHp=0._dp
cplHpHpcHpcHp=0._dp
cplAhAhhh=0._dp
cplhhhhhh=0._dp
cplhhHpcHp=0._dp

! ----------------------------------
! ------- TADPOLE DIAGRAMS --------
! ----------------------------------
temptad(:)=0._dp
tempcouplingvector(:)=0._dp
! ---- Topology ToSSS
! ---- Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSSS(MAh2,MAh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
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
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhHpcHp
coup2 = cplhhHpcHp
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSSS(Mhh2,MHp2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Topology ToSS
! ---- Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhAhAh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MAh2,MAh2,MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(MAh2,MAh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Ah,Ah,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhHpcHp
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MAh2,MAh2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplAhAhhhhh
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/4._dp*TfSS(Mhh2,Mhh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhHpcHp
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(Mhh2,Mhh2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Hp,conj[Hp],Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2 = cplAhAhHpcHp
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2,MHp2,MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Hp,conj[Hp],hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2 = cplhhhhHpcHp
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp/2._dp*TfSS(MHp2,MHp2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Hp,conj[Hp],Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2 = cplHpHpcHpcHp!(i2,i3,i1,i3)
prefactor=Real(coup1*coup2,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 1._dp*TfSS(MHp2,MHp2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Topology ToSSSS
! ---- Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(MAh2,MAh2,MAh2,Mhh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/4._dp*TfSSSS(Mhh2,Mhh2,MAh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSSS(Mhh2,Mhh2,MHp2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Hp,conj[Hp],hh,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
prefactor=Real(coup1*coup2*coup3,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSSS(MHp2,MHp2,Mhh2,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
! ---- Topology ToSSFF
! ---- Ah,Ah,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFd(i3)*MFd(i4)*TfSSFbFb(MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- Ah,Ah,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp/2._dp*TfSSFF(MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= MFe(i3)*MFe(i4)*TfSSFbFb(MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- Ah,Ah,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp/2._dp*TfSSFF(MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 3._dp*MFu(i3)*MFu(i4)*TfSSFbFb(MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
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
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -3._dp*TfSSFF(MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
if((MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
prefactor=Real(coup1*coup2L*coup3L+coup1*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i3)*MFd(i4)*TfSSFbFb(MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
coup1 = cplhhHpcHp
coup2L = cplcFeFvcHpL(i4,i3)
coup2R = cplcFeFvcHpR(i4,i3)
coup3L = cplcFvFeHpL(i3,i4)
coup3R = cplcFvFeHpR(i3,i4)
prefactor=Real(coup1*coup2L*coup3R+coup1*coup2R*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -1._dp*TfSSFF(MHp2,MHp2,0._dp,MFe2(i4),Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end do
end do
! ---- Topology ToFFFS
! ---- Fd,bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i3,i2)
coup3R = cplcFdFdAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i3)*TfFFFbS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i3,i2)
coup3R = cplcFdFdAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i2)*TfFFbFS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i3,i2)
coup3R = cplcFdFdAhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*TfFbFbFbS(MFd2(i1),MFd2(i2),MFd2(i3),MAh2,Qscale)
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

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
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
if((MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3)
coup2R = cplcFdFucHpR(i1,i3)
coup3L = cplcFuFdHpL(i3,i2)
coup3R = cplcFuFdHpR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i3)*TfFFFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3)
coup2R = cplcFdFucHpR(i1,i3)
coup3L = cplcFuFdHpL(i3,i2)
coup3R = cplcFuFdHpR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i2)*TfFFbFS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFucHpL(i1,i3)
coup2R = cplcFdFucHpR(i1,i3)
coup3L = cplcFuFdHpL(i3,i2)
coup3R = cplcFuFdHpR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i1)*MFu(i3)*MFd(i2)*TfFbFbFbS(MFd2(i1),MFd2(i2),MFu2(i3),MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fe,bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i3,i2)
coup3R = cplcFeFeAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i3)*TfFFFbS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i3,i2)
coup3R = cplcFeFeAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i2)*TfFFbFS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i3,i2)
coup3R = cplcFeFeAhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*TfFbFbFbS(MFe2(i1),MFe2(i2),MFe2(i3),MAh2,Qscale)
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

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
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
if((MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFvcHpL(i1,i3)
coup2R = cplcFeFvcHpR(i1,i3)
coup3L = cplcFvFeHpL(i3,i2)
coup3R = cplcFvFeHpR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -2._dp*MFe(i2)*TfFFbFS(MFe2(i1),MFe2(i2),0._dp,MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fu,bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i3,i2)
coup3R = cplcFuFuAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i3)*TfFFFbS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i3,i2)
coup3R = cplcFuFuAhR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i2)*TfFFbFS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i3,i2)
coup3R = cplcFuFuAhR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*TfFbFbFbS(MFu2(i1),MFu2(i2),MFu2(i3),MAh2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

end do
end do
end do
! ---- Fu,bar[Fu],Fd,Hp ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
if((MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3)
coup2R = cplcFuFdHpR(i1,i3)
coup3L = cplcFdFucHpL(i3,i2)
coup3R = cplcFdFucHpR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3R+coup1R*coup2L*coup3L,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFd(i3)*TfFFFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3)
coup2R = cplcFuFdHpR(i1,i3)
coup3L = cplcFdFucHpL(i3,i2)
coup3R = cplcFdFucHpR(i3,i2)
prefactor=Real(coup1L*coup2R*coup3L+coup1R*coup2L*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= -6._dp*MFu(i2)*TfFFbFS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2,Qscale)
 temptad=temptad+tempcouplingvector*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFdHpL(i1,i3)
coup2R = cplcFuFdHpR(i1,i3)
coup3L = cplcFdFucHpL(i3,i2)
coup3R = cplcFdFucHpR(i3,i2)
prefactor=Real(coup1L*coup2L*coup3L+coup1R*coup2R*coup3R,dp)
if(abs(prefactor) .gt. epscouplings) then
 tempcouplingvector(gE1)=prefactor
 nonzerocoupling=.true.
 else
 tempcouplingvector(gE1)= 0._dp
 end if
   End Do
if(nonzerocoupling) then 
 funcvalue= 6._dp*MFd(i3)*MFu(i1)*MFu(i2)*TfFbFbFbS(MFu2(i1),MFu2(i2),MFd2(i3),MHp2,Qscale)
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

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
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
temptad=temptad*oo16Pi2*oo16Pi2
! tad2L=matmul(temptad,HiggsMixingMatrix)
! ----------------------------

! ------------------------------------
! ------- CP EVEN MASS DIAGRAMS ------
! ------------------------------------
tempcont(:,:)=0._dp
tempcouplingmatrix(:,:)=0._dp
! ---- Topology WoSSSS
! ---- Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],hh,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -1._dp*WfSSSS(p2,MHp2,MHp2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology XoSSS
! ---- Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhAhAh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MAh2,MAh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhhhh
coup2 = cplhhhhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,Mhh2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2 = cplAhAhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2,MHp2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2 = cplhhhhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2,MHp2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2 = cplHpHpcHpcHp!(i2,i3,i1,i3)
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
 funcvalue= 1._dp*XfSSS(p2,MHp2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology YoSSSS
! ---- Ah,Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhAhAh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MAh2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhhhh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,Ah,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,MAh2,MAh2,MAh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplAhAhhhhh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhhhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,Mhh2,Mhh2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplAhAhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,MHp2,MHp2,MHp2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhhhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,MHp2,MHp2,MHp2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplHpHpcHpcHp!(i2,i4,i3,i4)
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
 funcvalue= -2._dp*YfSSSS(p2,MHp2,MHp2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology ZoSSSS
! ---- Ah,Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhAhAh
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
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,MAh2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplhhhhhh
coup3 = cplAhAhhhhh
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
 funcvalue= -1._dp/2._dp*ZfSSSS(p2,MAh2,MAh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplhhHpcHp
coup3 = cplAhAhHpcHp
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
 funcvalue= -1._dp*ZfSSSS(p2,MAh2,MAh2,MHp2,MHp2,Qscale)
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
 funcvalue= -1._dp/4._dp*ZfSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp
coup3 = cplhhhhHpcHp
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
 funcvalue= -1._dp*ZfSSSS(p2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplHpHpcHpcHp!(i2,i4,i1,i3)
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
 funcvalue= -1._dp*ZfSSSS(p2,MHp2,MHp2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology SoSSS
! ---- Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/2._dp*SfSSS(p2,MAh2,MAh2,Mhh2,Qscale)
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
 funcvalue= 1._dp/6._dp*SfSSS(p2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2 = cplhhhhHpcHp
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
 funcvalue= 1._dp*SfSSS(p2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology UoSSSS
! ---- Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhhhh
coup3 = cplAhAhhh
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
 funcvalue= -2._dp*UfSSSS(p2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplAhAhhhhh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp*UfSSSS(p2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],hh,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -4._dp*UfSSSS(p2,MHp2,MHp2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology VoSSSSS
! ---- Ah,Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 1._dp*VfSSSSS(p2,MAh2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhhhhh
coup3 = cplhhHpcHp
coup4 = cplhhHpcHp
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
 funcvalue= 1._dp*VfSSSSS(p2,Mhh2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp,hh,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
coup4 = cplhhHpcHp
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
 funcvalue= 2._dp*VfSSSSS(p2,MHp2,MHp2,MHp2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology MoSSSSS
! ---- Ah,Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,MAh2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,Ah,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplhhhhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 1._dp*MfSSSSS(p2,MAh2,Mhh2,MAh2,Mhh2,MAh2,Qscale)
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
 funcvalue= 1._dp/2._dp*MfSSSSS(p2,Mhh2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Hp,hh,conj[Hp],Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhhh
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
coup4 = cplhhHpcHp
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
 funcvalue= 2._dp*MfSSSSS(p2,Mhh2,MHp2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],conj[Hp],Hp,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
coup4 = cplhhHpcHp
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
 funcvalue= 1._dp*MfSSSSS(p2,MHp2,MHp2,MHp2,MHp2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology WoSSSV
! ---- Topology MoSSSSV
! ---- Topology WoSSFF
! ---- Ah,Ah,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
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
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
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
 funcvalue= -1._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
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
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
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
 funcvalue= -3._dp*MFu(i3)*MFd(i4)*WfSSFbFb(p2,MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
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
 funcvalue= -3._dp*WfSSFF(p2,MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhhhHpcHp
coup2L = cplcFeFvcHpL(i4,i3)
coup2R = cplcFeFvcHpR(i4,i3)
coup3L = cplcFvFeHpL(i3,i4)
coup3R = cplcFvFeHpR(i3,i4)
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
 funcvalue= -1._dp*WfSSFF(p2,MHp2,MHp2,0._dp,MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Topology MoFFFFS
! ---- Fd,bar[Fd],bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
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

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
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

if((MFd(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
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
if((MFd(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 3._dp*MFd(i1)*MFu(i4)*MFd(i3)*MFu(i2)*MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i3)*MFu(i2)*MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i3,i1)
coup1R = cplcFdFdhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i3,i1)
coup1R = cplcFeFehhR(i3,i1)
coup2L = cplcFeFehhL(i2,i4)
coup2R = cplcFeFehhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
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

if((MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
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

if((MFe(i4) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
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
if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 3._dp*MFd(i4)*MFu(i1)*MFd(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFdFdhhL(i2,i4)
coup2R = cplcFdFdhhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i3,i1)
coup1R = cplcFuFuhhR(i3,i1)
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
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

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
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

if((MFu(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
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
! ---- Ah,Fd,Ah,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,MAh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MAh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MAh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Ah,Fe,Ah,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,MAh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MAh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,MAh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Ah,Fu,Ah,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,MAh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MAh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuhhL(i4,i2)
coup2R = cplcFuFuhhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MAh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
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
if((MFd(i2) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
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
if((MFe(i2) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
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
if((MFu(i2) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
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
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5)
coup3R = cplcFdFucHpR(i2,i5)
coup4L = cplcFuFdHpL(i5,i4)
coup4R = cplcFuFdHpR(i5,i4)
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
 funcvalue= 6._dp*MFd(i2)*MFu(i5)*MFd(i4)*MfSFbSFbFb(p2,MHp2,MFd2(i2),MHp2,MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5)
coup3R = cplcFdFucHpR(i2,i5)
coup4L = cplcFuFdHpL(i5,i4)
coup4R = cplcFuFdHpR(i5,i4)
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
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MHp2,MFd2(i2),MHp2,MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFdFdhhL(i4,i2)
coup2R = cplcFdFdhhR(i4,i2)
coup3L = cplcFdFucHpL(i2,i5)
coup3R = cplcFdFucHpR(i2,i5)
coup4L = cplcFuFdHpL(i5,i4)
coup4R = cplcFuFdHpR(i5,i4)
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
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MHp2,MFd2(i2),MHp2,MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Hp,Fe,conj[Hp],bar[Fe],Fv ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFeFehhL(i4,i2)
coup2R = cplcFeFehhR(i4,i2)
coup3L = cplcFeFvcHpL(i2,i5)
coup3R = cplcFeFvcHpR(i2,i5)
coup4L = cplcFvFeHpL(i5,i4)
coup4R = cplcFvFeHpR(i5,i4)
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
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MHp2,MFe2(i2),MHp2,MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Hp,bar[Fu],conj[Hp],Fu,bar[Fd] ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2)
coup3R = cplcFdFucHpR(i5,i2)
coup4L = cplcFuFdHpL(i4,i5)
coup4R = cplcFuFdHpR(i4,i5)
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
 funcvalue= 6._dp*MFu(i4)*MFd(i5)*MFu(i2)*MfSFbSFbFb(p2,MHp2,MFu2(i2),MHp2,MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2)
coup3R = cplcFdFucHpR(i5,i2)
coup4L = cplcFuFdHpL(i4,i5)
coup4R = cplcFuFdHpR(i4,i5)
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
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MHp2,MFu2(i2),MHp2,MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2L = cplcFuFuhhL(i2,i4)
coup2R = cplcFuFuhhR(i2,i4)
coup3L = cplcFdFucHpL(i5,i2)
coup3R = cplcFdFucHpR(i5,i2)
coup4L = cplcFuFdHpL(i4,i5)
coup4R = cplcFuFdHpR(i4,i5)
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
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MHp2,MFu2(i2),MHp2,MFu2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Topology VoSSSFF
! ---- Ah,Ah,Ah,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFdFdAhL(i5,i4)
coup3R = cplcFdFdAhR(i5,i4)
coup4L = cplcFdFdAhL(i4,i5)
coup4R = cplcFdFdAhR(i4,i5)
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
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,MAh2,MAh2,MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFdFdAhL(i5,i4)
coup3R = cplcFdFdAhR(i5,i4)
coup4L = cplcFdFdAhL(i4,i5)
coup4R = cplcFdFdAhR(i4,i5)
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
 funcvalue= 3._dp*VfSSSFF(p2,MAh2,MAh2,MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Ah,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFeFeAhL(i5,i4)
coup3R = cplcFeFeAhR(i5,i4)
coup4L = cplcFeFeAhL(i4,i5)
coup4R = cplcFeFeAhR(i4,i5)
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
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,MAh2,MAh2,MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFeFeAhL(i5,i4)
coup3R = cplcFeFeAhR(i5,i4)
coup4L = cplcFeFeAhL(i4,i5)
coup4R = cplcFeFeAhR(i4,i5)
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
 funcvalue= 1._dp*VfSSSFF(p2,MAh2,MAh2,MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Ah,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFuFuAhL(i5,i4)
coup3R = cplcFuFuAhR(i5,i4)
coup4L = cplcFuFuAhL(i4,i5)
coup4R = cplcFuFuAhR(i4,i5)
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
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,MAh2,MAh2,MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFuFuAhL(i5,i4)
coup3R = cplcFuFuAhR(i5,i4)
coup4L = cplcFuFuAhL(i4,i5)
coup4R = cplcFuFuAhR(i4,i5)
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
 funcvalue= 3._dp*VfSSSFF(p2,MAh2,MAh2,MAh2,MFu2(i4),MFu2(i5),Qscale)
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
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3L = cplcFuFdHpL(i5,i4)
coup3R = cplcFuFdHpR(i5,i4)
coup4L = cplcFdFucHpL(i4,i5)
coup4R = cplcFdFucHpR(i4,i5)
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
 funcvalue= 6._dp*MFd(i4)*MFu(i5)*VfSSSFbFb(p2,MHp2,MHp2,MHp2,MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3L = cplcFuFdHpL(i5,i4)
coup3R = cplcFuFdHpR(i5,i4)
coup4L = cplcFdFucHpL(i4,i5)
coup4R = cplcFdFucHpR(i4,i5)
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
 funcvalue= 6._dp*VfSSSFF(p2,MHp2,MHp2,MHp2,MFd2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Hp,Fe,bar[Fv] ----
Do i4=1,3
Do i5=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplhhHpcHp
coup2 = cplhhHpcHp
coup3L = cplcFvFeHpL(i5,i4)
coup3R = cplcFvFeHpR(i5,i4)
coup4L = cplcFeFvcHpL(i4,i5)
coup4R = cplcFeFvcHpR(i4,i5)
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
 funcvalue= 2._dp*VfSSSFF(p2,MHp2,MHp2,MHp2,MFe2(i4),0._dp,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Topology VoFFFFS
! ---- Fd,bar[Fd],Fd,bar[Fd],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
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

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFu(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdhhL(i2,i1)
coup1R = cplcFdFdhhR(i2,i1)
coup2L = cplcFdFdhhL(i1,i3)
coup2R = cplcFdFdhhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 12._dp*MFd(i3)*MFu(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
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
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
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

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFehhL(i2,i1)
coup1R = cplcFeFehhR(i2,i1)
coup2L = cplcFeFehhL(i1,i3)
coup2R = cplcFeFehhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
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
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
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

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFd(i4)*MFu(i2)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
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
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFd(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuhhL(i2,i1)
coup1R = cplcFuFuhhR(i2,i1)
coup2L = cplcFuFuhhL(i1,i3)
coup2R = cplcFuFuhhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 12._dp*MFu(i3)*MFd(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
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
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
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
do gE1=1,1
Pi2S(gE1,gE1)=Pi2S(gE1,gE1)+tempcont(gE1,gE1)*oo16Pi2*oo16Pi2
do gE2=1,gE1-1
Pi2S(gE1,gE2)=Pi2S(gE1,gE2)+0.5_dp*(tempcont(gE1,gE2)+tempcont(gE2,gE1))*oo16Pi2*oo16Pi2
Pi2S(gE2,gE1)=Pi2S(gE1,gE2)
End do
End do
! Pi2S = Matmul(Pi2S,HiggsMixingMatrix)
! Pi2S = Matmul(Transpose(HiggsMixingMatrix),Pi2S)

! -----------------------------------
! ------- CP ODD MASS DIAGRAMS ------
! -----------------------------------
tempcont(:,:)=0._dp
tempcouplingmatrix(:,:)=0._dp
! ---- Topology WoSSSS
! ---- Ah,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp/2._dp*WfSSSS(p2,MAh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp/4._dp*WfSSSS(p2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -1._dp/2._dp*WfSSSS(p2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],hh,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2 = cplhhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -1._dp*WfSSSS(p2,MHp2,MHp2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology XoSSS
! ---- Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2 = cplAhAhAhAh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Ah,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2 = cplAhAhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MAh2,MAh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/4._dp*XfSSS(p2,Mhh2,Mhh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
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
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplhhhhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,Mhh2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2 = cplAhAhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2,MHp2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2 = cplhhhhHpcHp
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
 funcvalue= 1._dp/2._dp*XfSSS(p2,MHp2,MHp2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Hp,conj[Hp],Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2 = cplHpHpcHpcHp!(i2,i3,i1,i3)
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
 funcvalue= 1._dp*XfSSS(p2,MHp2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology YoSSSS
! ---- Ah,hh,hh,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhhhh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MAh2,Mhh2,Mhh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,MAh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplhhhhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,MAh2,Mhh2,Mhh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhAhAh
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
 funcvalue= -1._dp/2._dp*YfSSSS(p2,Mhh2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Ah,Ah,Hp ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhHpcHp
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
 funcvalue= -1._dp*YfSSSS(p2,Mhh2,MAh2,MAh2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology ZoSSSS
! ---- Ah,hh,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhhhh
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
 funcvalue= -1._dp*ZfSSSS(p2,MAh2,Mhh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology SoSSS
! ---- Ah,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2 = cplAhAhAhAh
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
 funcvalue= 1._dp/6._dp*SfSSS(p2,MAh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhhhh
coup2 = cplAhAhhhhh
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
 funcvalue= 1._dp/2._dp*SfSSS(p2,MAh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2 = cplAhAhHpcHp
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
 funcvalue= 1._dp*SfSSS(p2,MAh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology UoSSSS
! ---- Ah,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhAhAh
coup3 = cplAhAhhh
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
 funcvalue= -1._dp*UfSSSS(p2,MAh2,Mhh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhhhh
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
 funcvalue= -1._dp*UfSSSS(p2,MAh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhHpcHp
coup3 = cplhhHpcHp
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
 funcvalue= -2._dp*UfSSSS(p2,MAh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- hh,Ah,Ah,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhhhh
coup3 = cplAhAhhh
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
 funcvalue= -2._dp*UfSSSS(p2,Mhh2,MAh2,MAh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology VoSSSSS
! ---- Ah,hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MAh2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 1._dp/2._dp*VfSSSSS(p2,MAh2,Mhh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,Hp,conj[Hp] ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplhhHpcHp
coup4 = cplhhHpcHp
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
 funcvalue= 1._dp*VfSSSSS(p2,MAh2,Mhh2,Mhh2,MHp2,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology MoSSSSS
! ---- Ah,Ah,hh,hh,hh ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
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
 funcvalue= 2._dp*MfSSSSS(p2,MAh2,MAh2,Mhh2,Mhh2,Mhh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Ah,hh,hh,Ah,Ah ----
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3 = cplAhAhhh
coup4 = cplAhAhhh
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
 funcvalue= 2._dp*MfSSSSS(p2,MAh2,Mhh2,Mhh2,MAh2,MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
! ---- Topology WoSSSV
! ---- Topology MoSSSSV
! ---- Topology WoSSFF
! ---- Ah,Ah,Fd,bar[Fd] ----
Do i3=1,3
Do i4=1,3
if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*MFd(i3)*MFd(i4)*WfSSFbFb(p2,MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFdFdAhL(i4,i3)
coup2R = cplcFdFdAhR(i4,i3)
coup3L = cplcFdFdAhL(i3,i4)
coup3R = cplcFdFdAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFd2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Fe,bar[Fe] ----
Do i3=1,3
Do i4=1,3
if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
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
 funcvalue= -1._dp/2._dp*MFe(i3)*MFe(i4)*WfSSFbFb(p2,MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFeFeAhL(i4,i3)
coup2R = cplcFeFeAhR(i4,i3)
coup3L = cplcFeFeAhL(i3,i4)
coup3R = cplcFeFeAhR(i3,i4)
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
 funcvalue= -1._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFe2(i3),MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,Ah,Fu,bar[Fu] ----
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*MFu(i3)*MFu(i4)*WfSSFbFb(p2,MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhAhAh
coup2L = cplcFuFuAhL(i4,i3)
coup2R = cplcFuFuAhR(i4,i3)
coup3L = cplcFuFuAhL(i3,i4)
coup3R = cplcFuFuAhR(i3,i4)
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
 funcvalue= -3._dp/2._dp*WfSSFF(p2,MAh2,MAh2,MFu2(i3),MFu2(i4),Qscale)
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
coup1 = cplAhAhhhhh
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
coup1 = cplAhAhhhhh
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
coup1 = cplAhAhhhhh
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
coup1 = cplAhAhhhhh
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
coup1 = cplAhAhhhhh
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
coup1 = cplAhAhhhhh
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
Do i3=1,3
Do i4=1,3
if((MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
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
 funcvalue= -3._dp*MFu(i3)*MFd(i4)*WfSSFbFb(p2,MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2L = cplcFdFucHpL(i4,i3)
coup2R = cplcFdFucHpR(i4,i3)
coup3L = cplcFuFdHpL(i3,i4)
coup3R = cplcFuFdHpR(i3,i4)
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
 funcvalue= -3._dp*WfSSFF(p2,MHp2,MHp2,MFu2(i3),MFd2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Hp,conj[Hp],Fv,bar[Fe] ----
Do i3=1,3
Do i4=1,3
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhHpcHp
coup2L = cplcFeFvcHpL(i4,i3)
coup2R = cplcFeFvcHpR(i4,i3)
coup3L = cplcFvFeHpL(i3,i4)
coup3R = cplcFvFeHpR(i3,i4)
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
 funcvalue= -1._dp*WfSSFF(p2,MHp2,MHp2,0._dp,MFe2(i4),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Topology MoFFFFS
! ---- Fd,bar[Fd],bar[Fd],Fd,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 3._dp*MFd(i1)*MFd(i4)*MFd(i2)*MFd(i3)*MfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i2)*MFd(i3)*MfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFdFdAhL(i1,i2)
coup3R = cplcFdFdAhR(i1,i2)
coup4L = cplcFdFdAhL(i4,i3)
coup4R = cplcFdFdAhR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
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
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
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

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
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

if((MFd(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
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
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
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
if((MFd(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 3._dp*MFd(i1)*MFu(i4)*MFd(i3)*MFu(i2)*MfFbFbFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i3)*MFu(i2)*MfFFbFbFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFd(i3)*MfFFFbFbS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i3,i1)
coup1R = cplcFdFdAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFdFucHpL(i1,i2)
coup3R = cplcFdFucHpR(i1,i2)
coup4L = cplcFuFdHpL(i4,i3)
coup4R = cplcFuFdHpR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFd2(i1),MFu2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],bar[Fe],Fe,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= MFe(i1)*MFe(i4)*MFe(i2)*MFe(i3)*MfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i2)*MFe(i3)*MfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i4)*MFe(i2)*MfFFbFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 2._dp*MFe(i4)*MFe(i3)*MfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
coup3L = cplcFeFeAhL(i1,i2)
coup3R = cplcFeFeAhR(i1,i2)
coup4L = cplcFeFeAhL(i4,i3)
coup4R = cplcFeFeAhR(i4,i3)
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
 funcvalue= 1._dp*MfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
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
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
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

if((MFe(i4) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
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

if((MFe(i4) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
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
coup1L = cplcFeFeAhL(i3,i1)
coup1R = cplcFeFeAhR(i3,i1)
coup2L = cplcFeFeAhL(i2,i4)
coup2R = cplcFeFeAhR(i2,i4)
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
if((MFd(i4) .gt. epsfmass) .and. (MFu(i1) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 3._dp*MFd(i4)*MFu(i1)*MFd(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFd(i2)*MfFFbFFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 6._dp*MFd(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFdFdAhL(i2,i4)
coup2R = cplcFdFdAhR(i2,i4)
coup3L = cplcFuFdHpL(i1,i2)
coup3R = cplcFuFdHpR(i1,i2)
coup4L = cplcFdFucHpL(i4,i3)
coup4R = cplcFdFucHpR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFd2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],bar[Fu],Fu,Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 3._dp*MFu(i1)*MFu(i4)*MFu(i2)*MFu(i3)*MfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i2)*MFu(i3)*MfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i2)*MfFFbFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 6._dp*MFu(i4)*MFu(i3)*MfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
coup3L = cplcFuFuAhL(i1,i2)
coup3R = cplcFuFuAhR(i1,i2)
coup4L = cplcFuFuAhL(i4,i3)
coup4R = cplcFuFuAhR(i4,i3)
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
 funcvalue= 3._dp*MfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
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
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
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

if((MFu(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
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

if((MFu(i4) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
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
coup1L = cplcFuFuAhL(i3,i1)
coup1R = cplcFuFuAhR(i3,i1)
coup2L = cplcFuFuAhL(i2,i4)
coup2R = cplcFuFuAhR(i2,i4)
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
! ---- Ah,Fd,hh,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
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
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,MAh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
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
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,MAh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdAhL(i2,i5)
coup3R = cplcFdFdAhR(i2,i5)
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
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,MAh2,MFd2(i2),Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Ah,Fe,hh,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
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
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,MAh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
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
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,MAh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFeAhL(i2,i5)
coup3R = cplcFeFeAhR(i2,i5)
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
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,MAh2,MFe2(i2),Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Ah,Fu,hh,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
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
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,MAh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
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
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,MAh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuAhL(i2,i5)
coup3R = cplcFuFuAhR(i2,i5)
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
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,MAh2,MFu2(i2),Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fd,Ah,bar[Fd],Fd ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFd(i2) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 6._dp*MFd(i2)*MFd(i5)*MFd(i4)*MfSFbSFbFb(p2,Mhh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 12._dp*MFd(i4)*MfSFSFbF(p2,Mhh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFdFdAhL(i4,i2)
coup2R = cplcFdFdAhR(i4,i2)
coup3L = cplcFdFdhhL(i2,i5)
coup3R = cplcFdFdhhR(i2,i5)
coup4L = cplcFdFdAhL(i5,i4)
coup4R = cplcFdFdAhR(i5,i4)
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
 funcvalue= 6._dp*MFd(i5)*MfSFSFFb(p2,Mhh2,MFd2(i2),MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fe,Ah,bar[Fe],Fe ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFe(i2) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 2._dp*MFe(i2)*MFe(i5)*MFe(i4)*MfSFbSFbFb(p2,Mhh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 4._dp*MFe(i4)*MfSFSFbF(p2,Mhh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFeFeAhL(i4,i2)
coup2R = cplcFeFeAhR(i4,i2)
coup3L = cplcFeFehhL(i2,i5)
coup3R = cplcFeFehhR(i2,i5)
coup4L = cplcFeFeAhL(i5,i4)
coup4R = cplcFeFeAhR(i5,i4)
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
 funcvalue= 2._dp*MFe(i5)*MfSFSFFb(p2,Mhh2,MFe2(i2),MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- hh,Fu,Ah,bar[Fu],Fu ----
Do i2=1,3
Do i4=1,3
Do i5=1,3
if((MFu(i2) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 6._dp*MFu(i2)*MFu(i5)*MFu(i4)*MfSFbSFbFb(p2,Mhh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 12._dp*MFu(i4)*MfSFSFbF(p2,Mhh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2L = cplcFuFuAhL(i4,i2)
coup2R = cplcFuFuAhR(i4,i2)
coup3L = cplcFuFuhhL(i2,i5)
coup3R = cplcFuFuhhR(i2,i5)
coup4L = cplcFuFuAhL(i5,i4)
coup4R = cplcFuFuAhR(i5,i4)
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
 funcvalue= 6._dp*MFu(i5)*MfSFSFFb(p2,Mhh2,MFu2(i2),MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

end do
end do
end do
! ---- Topology VoSSSFF
! ---- Ah,hh,hh,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,MAh2,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 3._dp*VfSSSFF(p2,MAh2,Mhh2,Mhh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,hh,hh,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,MAh2,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 1._dp*VfSSSFF(p2,MAh2,Mhh2,Mhh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Ah,hh,hh,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,MAh2,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
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
 funcvalue= 3._dp*VfSSSFF(p2,MAh2,Mhh2,Mhh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,Ah,Ah,Fd,bar[Fd] ----
Do i4=1,3
Do i5=1,3
if((MFd(i4) .gt. epsfmass) .and. (MFd(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFdFdAhL(i5,i4)
coup3R = cplcFdFdAhR(i5,i4)
coup4L = cplcFdFdAhL(i4,i5)
coup4R = cplcFdFdAhR(i4,i5)
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
 funcvalue= 3._dp*MFd(i4)*MFd(i5)*VfSSSFbFb(p2,Mhh2,MAh2,MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFdFdAhL(i5,i4)
coup3R = cplcFdFdAhR(i5,i4)
coup4L = cplcFdFdAhL(i4,i5)
coup4R = cplcFdFdAhR(i4,i5)
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
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,MAh2,MAh2,MFd2(i4),MFd2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,Ah,Ah,Fe,bar[Fe] ----
Do i4=1,3
Do i5=1,3
if((MFe(i4) .gt. epsfmass) .and. (MFe(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFeFeAhL(i5,i4)
coup3R = cplcFeFeAhR(i5,i4)
coup4L = cplcFeFeAhL(i4,i5)
coup4R = cplcFeFeAhR(i4,i5)
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
 funcvalue= MFe(i4)*MFe(i5)*VfSSSFbFb(p2,Mhh2,MAh2,MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFeFeAhL(i5,i4)
coup3R = cplcFeFeAhR(i5,i4)
coup4L = cplcFeFeAhL(i4,i5)
coup4R = cplcFeFeAhR(i4,i5)
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
 funcvalue= 1._dp*VfSSSFF(p2,Mhh2,MAh2,MAh2,MFe2(i4),MFe2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- hh,Ah,Ah,Fu,bar[Fu] ----
Do i4=1,3
Do i5=1,3
if((MFu(i4) .gt. epsfmass) .and. (MFu(i5) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFuFuAhL(i5,i4)
coup3R = cplcFuFuAhR(i5,i4)
coup4L = cplcFuFuAhL(i4,i5)
coup4R = cplcFuFuAhR(i4,i5)
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
 funcvalue= 3._dp*MFu(i4)*MFu(i5)*VfSSSFbFb(p2,Mhh2,MAh2,MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1 = cplAhAhhh
coup2 = cplAhAhhh
coup3L = cplcFuFuAhL(i5,i4)
coup3R = cplcFuFuAhR(i5,i4)
coup4L = cplcFuFuAhL(i4,i5)
coup4R = cplcFuFuAhR(i4,i5)
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
 funcvalue= 3._dp*VfSSSFF(p2,Mhh2,MAh2,MAh2,MFu2(i4),MFu2(i5),Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
! ---- Topology VoFFFFS
! ---- Fd,bar[Fd],Fd,bar[Fd],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFd(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 12._dp*MFd(i3)*MFd(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFdFdAhL(i4,i2)
coup3R = cplcFdFdAhR(i4,i2)
coup4L = cplcFdFdAhL(i3,i4)
coup4R = cplcFdFdAhR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFd2(i4),MAh2,Qscale)
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
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
if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFd(i3)*MFd(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFd(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 12._dp*MFd(i1)*MFd(i3)*VfFbFFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i1)*MFu(i4)*VfFbFFFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFd(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*MFd(i3)*MFd(i2)*VfFFbFbFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFd(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 12._dp*MFd(i3)*MFu(i4)*VfFFFbFbS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i3)
coup2R = cplcFdFdAhR(i1,i3)
coup3L = cplcFuFdHpL(i4,i2)
coup3R = cplcFuFdHpR(i4,i2)
coup4L = cplcFdFucHpL(i3,i4)
coup4R = cplcFdFucHpR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFd2(i1),MFd2(i2),MFd2(i3),MFu2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fe,bar[Fe],Fe,bar[Fe],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i1)*MFe(i3)*MFe(i2)*MFe(i4)*VfFbFbFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i1) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i1)*MFe(i4)*VfFbFFFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 4._dp*MFe(i3)*MFe(i4)*VfFFFbFbS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFeFeAhL(i4,i2)
coup3R = cplcFeFeAhR(i4,i2)
coup4L = cplcFeFeAhL(i3,i4)
coup4R = cplcFeFeAhR(i3,i4)
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
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),MFe2(i4),MAh2,Qscale)
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass) .and. (MFe(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
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
if((MFe(i1) .gt. epsfmass) .and. (MFe(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 4._dp*MFe(i1)*MFe(i3)*VfFbFFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFe(i3) .gt. epsfmass) .and. (MFe(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 2._dp*MFe(i3)*MFe(i2)*VfFFbFbFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFeFeAhL(i2,i1)
coup1R = cplcFeFeAhR(i2,i1)
coup2L = cplcFeFeAhL(i1,i3)
coup2R = cplcFeFeAhR(i1,i3)
coup3L = cplcFvFeHpL(i4,i2)
coup3R = cplcFvFeHpR(i4,i2)
coup4L = cplcFeFvcHpL(i3,i4)
coup4R = cplcFeFvcHpR(i3,i4)
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
 funcvalue= 2._dp*VfFFFFS(p2,MFe2(i1),MFe2(i2),MFe2(i3),0._dp,MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end do
end do
end do
end do
! ---- Fu,bar[Fu],Fu,bar[Fu],Ah ----
Do i1=1,3
Do i2=1,3
Do i3=1,3
Do i4=1,3
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFu(i2)*MFu(i4)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 12._dp*MFu(i3)*MFu(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFuFuAhL(i4,i2)
coup3R = cplcFuFuAhR(i4,i2)
coup4L = cplcFuFuAhL(i3,i4)
coup4R = cplcFuFuAhR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFu2(i4),MAh2,Qscale)
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass) .and. (MFu(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
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
if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFu(i3)*MFd(i4)*MFu(i2)*VfFbFbFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFu(i3) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 12._dp*MFu(i1)*MFu(i3)*VfFbFFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i1) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i1)*MFd(i4)*VfFbFFFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFu(i2) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*MFu(i3)*MFu(i2)*VfFFbFbFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

if((MFu(i3) .gt. epsfmass) .and. (MFd(i4) .gt. epsfmass)) then 
nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 12._dp*MFu(i3)*MFd(i4)*VfFFFbFbS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
end if

nonzerocoupling=.false.
  Do gE1=1,1
   Do gE2=1,1
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i3)
coup2R = cplcFuFuAhR(i1,i3)
coup3L = cplcFdFucHpL(i4,i2)
coup3R = cplcFdFucHpR(i4,i2)
coup4L = cplcFuFdHpL(i3,i4)
coup4R = cplcFuFdHpR(i3,i4)
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
 funcvalue= 6._dp*VfFFFFS(p2,MFu2(i1),MFu2(i2),MFu2(i3),MFd2(i4),MHp2,Qscale)
 tempcont=tempcont+tempcouplingmatrix*funcvalue
end if
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i2)
coup2R = cplcFdFdAhR(i1,i2)
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
coup1L = cplcFdFdAhL(i2,i1)
coup1R = cplcFdFdAhR(i2,i1)
coup2L = cplcFdFdAhL(i1,i2)
coup2R = cplcFdFdAhR(i1,i2)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i2)
coup2R = cplcFuFuAhR(i1,i2)
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
coup1L = cplcFuFuAhL(i2,i1)
coup1R = cplcFuFuAhR(i2,i1)
coup2L = cplcFuFuAhL(i1,i2)
coup2R = cplcFuFuAhR(i1,i2)
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
do gE1=1,1
Pi2P(gE1,gE1)=Pi2P(gE1,gE1)+tempcont(gE1,gE1)*oo16Pi2*oo16Pi2
do gE2=1,gE1-1
Pi2P(gE1,gE2)=Pi2P(gE1,gE2)+0.5_dp*(tempcont(gE1,gE2)+tempcont(gE2,gE1))*oo16Pi2*oo16Pi2
Pi2P(gE2,gE1)=Pi2P(gE1,gE2)
End do
End do
! Pi2P = Matmul(Pi2P,PseudoScalarMixingMatrix)
! Pi2P = Matmul(Transpose(PseudoScalarMixingMatrix),Pi2P)
End Subroutine CalculatePi2S_SM
End Module Pole2L_SM_HC 
 
