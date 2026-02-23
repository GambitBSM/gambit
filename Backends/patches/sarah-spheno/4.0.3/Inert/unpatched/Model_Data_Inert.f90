! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:33 on 18.2.2026   
! ----------------------------------------------------------------------  
 
 
Module Model_Data_Inert 
 
Use Control 
Use Settings 
Use LoopFunctions 
Logical, Save :: CalcLoopDecay_LoopInducedOnly=.False.
 Logical, Save :: CalcLoopDecay_Fu=.True.
Logical, Save :: CalcLoopDecay_Fe=.True.
Logical, Save :: CalcLoopDecay_Fd=.True.
Logical, Save :: CalcLoopDecay_hh=.True.
Logical, Save :: CalcLoopDecay_H0=.True.
Logical, Save :: CalcLoopDecay_A0=.True.
Logical, Save :: CalcLoopDecay_Hp=.True.
Logical, Save :: Calc3BodyDecay_Fu=.True.
Logical, Save :: Calc3BodyDecay_Fe=.True.
Logical, Save :: Calc3BodyDecay_Fd=.True.
Real(dp) :: tau_pi0=26033._dp, tau_pip,tau_rho0,tau_rhop,tau_Dp= 1.040E-12_dp,tau_D0,tau_DSp,tau_DSsp, & 
 & tau_eta,tau_etap,tau_omega,tau_phi, tau_KL0,tau_KS0,tau_K0,tau_Kp=1238.0E-11_dp,tau_B0s=1.472E-12_dp, tau_B0d=1.525E-12_dp, tau_B0p,tau_B0c,tau_Bpc,tau_Bs0c, tau_Bp=1.519E-12_dp, & 
 & tau_Bcp,tau_Bcpc,tau_K0c,tau_Kpc,tau_etac,tau_JPsi,tau_Ups,tau_etab  
Real(dp) :: mass_pi0=0.1396_dp, mass_pip,mass_rho0,mass_rhop,mass_Dp,mass_D0=1.8648_dp,mass_DSp,mass_DSsp, & 
 & mass_eta,mass_etap,mass_omega,mass_phi, mass_KL0,mass_KS0,mass_K0=0.4937_dp,mass_Kp=0.493_dp,mass_B0s=5.3663_dp, mass_B0d=5.2795_dp,mass_B0p=5.279_dp,mass_B0c,mass_Bpc,mass_Bs0c, & 
 & mass_Bcp,mass_Bcpc,mass_K0c=0.8959_dp,mass_Kpc,mass_etac,mass_JPsi,mass_Ups,mass_etab  
Real(dp) :: f_k_CONST=0.1598_dp, h_k_CONST, f_eta_q_CONST, f_eta_s_CONST, h_eta_q_CONST, h_eta_s_CONST, & 
 & f_rho_CONST, h_rho_CONST,  f_omega_q_CONST, f_omega_s_CONST, h_omega_q_CONST, h_omega_s_CONST, f_B0d_CONST=0.190_dp, f_B0s_CONST=0.227_dp, & 
 & f_D_CONST= 0.248_dp, f_Bp_CONST =  0.234_dp, f_Kp_CONST = 0.156_dp 
Real(dp) :: MW_SM 
Real(dp) :: Alpha_160, AlphaS_160, SinW2_160, sinW2_MZ 
Real(dp) :: mf_d_160(3), mf_u_160(3), mf_l_160(3), mf_d2_160(3), mf_u2_160(3), mf_l2_160(3) 
Real(dp) :: mf_d2_MZ(3), mf_u2_MZ(3), mf_l2_MZ(3) 
Complex(dp) :: CKM_160(3,3), CKM_MZ(3,3) 
Logical :: TransposedYukawa= .False. 
Logical :: KineticMixing = .True. 
Logical :: KineticMixingSave = .True. 
Logical :: TwoLoopMatching = .True., GuessTwoLoopMatchingBSM=.false. 
Logical :: OneLoopMatching = .True. 
Logical :: TreeLevelUnitarityLimits = .True. 
Real(dp) :: max_scattering_eigenvalue=0._dp
Real(dp) :: TreeUnitarity=1
Real(dp) :: CutSpole=0.25_dp 
Logical :: TrilinearUnitarity = .True. 
Logical :: RunRGEs_unitarity = .false. 
Real(dp) :: max_scattering_eigenvalue_trilinears=0._dp
Real(dp) :: TreeUnitarityTrilinear=1
Real(dp) :: unitarity_s_best=0._dp
Real(dp) :: unitarity_s_min=2000._dp
Real(dp) :: unitarity_s_max=3000._dp
Integer :: unitarity_steps=5
Integer :: TUcutLevel=2
Logical :: WriteTreeLevelTadpoleSolutions = .False. 
Logical :: WriteHiggsDiphotonLoopContributions = .False. 
Logical :: WriteEffHiggsCouplingRatios = .False. 
Real(dp) :: ZPOS_0(2, 2)
Real(dp) :: ZPOS_p2(2, 2)
Complex(dp) :: ZDLOS_0(3, 3)
Complex(dp) :: ZDLOS_p2(3, 3)
Complex(dp) :: ZDROS_0(3, 3)
Complex(dp) :: ZDROS_p2(3, 3)
Complex(dp) :: ZULOS_0(3, 3)
Complex(dp) :: ZULOS_p2(3, 3)
Complex(dp) :: ZUROS_0(3, 3)
Complex(dp) :: ZUROS_p2(3, 3)
Complex(dp) :: ZELOS_0(3, 3)
Complex(dp) :: ZELOS_p2(3, 3)
Complex(dp) :: ZEROS_0(3, 3)
Complex(dp) :: ZEROS_p2(3, 3)
Real(dp) :: mHd2Tree 
Real(dp) :: mHd21L 
Real(dp) :: mHd22L 
Real(dp) :: mHu2Tree 
Real(dp) :: mHu21L 
Real(dp) :: mHu22L 
Real(dp) :: mass_uncertainty_Q(15), mass_uncertainty_Yt(15), g_SM_save(62) 
Logical :: GetMassUncertainty = .false. 
Integer :: SolutionTadpoleNr = 1 
Real(dp) :: g1,g2,g3,mHd2,mHu2

Complex(dp) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp) :: g1IN,g2IN,g3IN,mHd2IN,mHu2IN

Complex(dp) :: Lam5IN,Lam1IN,Lam4IN,Lam3IN,Lam2IN,YeIN(3,3),YdIN(3,3),YuIN(3,3)

Real(dp) :: g1MZ,g2MZ,g3MZ,mHd2MZ,mHu2MZ

Complex(dp) :: Lam5MZ,Lam1MZ,Lam4MZ,Lam3MZ,Lam2MZ,YeMZ(3,3),YdMZ(3,3),YuMZ(3,3)

Real(dp) :: g1GUT,g2GUT,g3GUT,mHd2GUT,mHu2GUT

Complex(dp) :: Lam5GUT,Lam1GUT,Lam4GUT,Lam3GUT,Lam2GUT,YeGUT(3,3),YdGUT(3,3),YuGUT(3,3)

Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp) :: v

Real(dp) :: vIN

Real(dp) :: vFix

Real(dp) :: gPFu(3,159),gTFu(3),BRFu(3,159),gPFe(3,156),gTFe(3),BRFe(3,156),gPFd(3,159),          & 
& gTFd(3),BRFd(3,159),gPhh(1,59),gThh,BRhh(1,59),gPH0(1,54),gTH0,BRH0(1,54),             & 
& gPA0(1,54),gTA0,BRA0(1,54),gPHp(2,28),gTHp(2),BRHp(2,28)

Real(dp) :: gP1LFu(3,24),gT1LFu(3),BR1LFu(3,24),gP1LFe(3,21),gT1LFe(3),BR1LFe(3,21),              & 
& gP1LFd(3,24),gT1LFd(3),BR1LFd(3,24),gP1Lhh(1,59),gT1Lhh,BR1Lhh(1,59),gP1LH0(1,54),     & 
& gT1LH0,BR1LH0(1,54),gP1LA0(1,54),gT1LA0,BR1LA0(1,54),gP1LHp(2,28),gT1LHp(2),           & 
& BR1LHp(2,28)

Real(dp) :: ratioFd(1,3),ratioFe(1,3),ratioFu(1,3),ratioHp(1,2),ratioVWp

Complex(dp) :: ratioGG,ratioPP

Real(dp) :: ratioPFd(1,3),ratioPFe(1,3),ratioPFu(1,3),ratioPHp(1,2),ratioPVWp

Complex(dp) :: ratioPGG,ratioPPP

Real(dp) :: gForTadpoles(70)
Complex(dp) :: tForTadpoles(2)
Real(dp) :: g1_saveEP 
Real(dp) :: g2_saveEP 
Complex(dp) :: Ye_saveEP(3,3) 
Complex(dp) :: Yd_saveEP(3,3) 
Complex(dp) :: Yu_saveEP(3,3) 
Logical :: RotateNegativeFermionMasses=.True. 
Logical,save::IgnoreNegativeMasses= .False.
Logical,save::IgnoreMuSignFlip= .False.
Logical,save::IgnoreNegativeMassesMZ= .False.
Logical,save::Write_WHIZARD= .False.
Integer,save::BoundaryCondition=1 
Logical,Save::MZ_input= .False. 
 
Real(dp) :: CS_Higgs_LHC(5,1,5) 
 
Real (dp) :: MhhL, Mhh2L 
Real (dp) :: Mhh_s, Mhh2_s
Real (dp) :: MAhL, MAh2L 
Real (dp) :: MAh_s, MAh2_s 
Real (dp) :: FineTuningResults(0) 
Real (dp) :: FineTuningResultsAllVEVs(0) 
Logical, Save :: OneLoopFT = .False. 
Logical, Save :: CalcFT = .True. 
Integer,save::YukawaScheme=1
Logical, save :: CheckSugraDetails(10) =.False. & 
                        &, SugraErrors(10) =.False. &
                        &, StrictUnification =.False. &
                        &, UseFixedScale =.False. &
                        &, UseFixedGUTScale =.False. 
Real(dp), save :: GUT_scale 
Real(dp) :: g3running 
Logical, save :: InputValueforg1 =.False. 
Logical, save :: InputValueforg2 =.False. 
Logical, save :: InputValueforg3 =.False. 
Logical, save :: InputValueforLam5 =.False. 
Logical, save :: InputValueforLam1 =.False. 
Logical, save :: InputValueforLam4 =.False. 
Logical, save :: InputValueforLam3 =.False. 
Logical, save :: InputValueforLam2 =.False. 
Logical, save :: InputValueforYe =.False. 
Logical, save :: InputValueforYd =.False. 
Logical, save :: InputValueforYu =.False. 
Logical, save :: InputValueformHd2 =.False. 
Logical, save :: InputValueformHu2 =.False. 
Real (dp) :: vSM_Q 
Real(dp), save :: RXiG = 1._dp 
Real(dp), save :: RXiP = 1._dp 
Real(dp), save :: RXiWp = 1._dp 
Real(dp), save :: RXiZ = 1._dp 
Complex(dp) :: temporaryValue 
Complex(dp) :: Lambda1IN
Complex(dp) :: Lambda2IN
Complex(dp) :: Lambda3IN
Complex(dp) :: Lambda4IN
Complex(dp) :: Lambda5IN
Real(dp) :: vMZ 
Real(dp) :: vSUSY 
! For HiggsBounds 
Real(dp) :: BR_HpHW(2,1)  = 0._dp
Real(dp) :: BR_HpAW(2,1) = 0._dp
Real(dp) :: BR_HpTB(2) = 0._dp 
Real(dp) :: BR_HpWZ(2) = 0._dp
Real(dp) :: BR_tHb(2) = 0._dp
Real(dp) :: BR_Hcs(2)= 0._dp 
Real(dp) :: BR_Hcb(2)=0._dp 
Real(dp) :: BR_Htaunu(2)=0._dp 
Real(dp) :: BR_tWb = 0._dp
Real(dp) :: BRHll(1,3,3)  = 0._dp
Real(dp) :: BRAll(1,3,3)   = 0._dp 
 Real(dp) :: BRHHH(1,1)=0._dp
Real(dp) :: BRHAA(1,1)= 0._dp 
 Real(dp) :: BRAHH(1,1)=0._dp
Real(dp) :: BRAAA(1,1)  = 0._dp 
 Real(dp) :: BRHHHijk(1,1,1)=0._dp
Real(dp) :: BRHHAijk(1,1,1)=0._dp
Real(dp) :: BRHAAijk(1,1,1)  = 0._dp 
 Real(dp) :: BRAHHijk(1,1,1)=0._dp
Real(dp) :: BRAHAijk(1,1,1)=0._dp
Real(dp) ::  BRAAAijk(1,1,1)  = 0._dp 
 Real(dp) :: BRHHZ(1,1)=0._dp
Real(dp) :: BRHAZ(1,1)  = 0._dp 
 Real(dp) :: BRAHZ(1,1) =0._dp
Real(dp) :: BRAAZ(1,1)  = 0._dp 
 Real(dp) :: BRAHpW(1,2)=0._dp
Real(dp) :: BRHhpW(1,2)  = 0._dp 
 Real(dp) :: BRinvH(1), BRinvA(1)  = 0._dp 
Real(dp) :: rHB_P_VP(1),rHB_S_VP(1)
Real(dp) :: rHB_P_VZ(1),rHB_S_VZ(1)
Real(dp) :: rHB_P_VG(1),rHB_S_VG(1)
Real(dp) :: rHB_P_VWp(1),rHB_S_VWp(1)
Real(dp) :: rHB_P_P_Fd(1,3),rHB_P_S_Fd(1,3),rHB_S_S_Fd(1,3),rHB_S_P_Fd(1,3)
Real(dp) :: rHB_P_P_Fu(1,3),rHB_P_S_Fu(1,3),rHB_S_S_Fu(1,3),rHB_S_P_Fu(1,3)
Real(dp) :: rHB_P_P_Fe(1,3),rHB_P_S_Fe(1,3),rHB_S_S_Fe(1,3),rHB_S_P_Fe(1,3)
Real(dp) :: rHB_P_P_Fv(1),rHB_P_S_Fv(1),rHB_S_S_Fv(1),rHB_S_P_Fv(1)
Complex(dp) :: CPL_A_H_Z  =0._dp 
 Complex(dp) :: CPL_H_H_Z(1,1) =0._dp 
 Complex(dp) :: CoupHPP, CoupHGG 
Complex(dp) :: CPL_A_A_Z(1,1) =0._dp 
 Complex(dp) :: CoupAPP, CoupAGG 
Real(dp) :: HPPloopVWp
Real(dp) :: HPPloopHp(2)
Real(dp) :: HPPloopFd(3)
Real(dp) :: HPPloopFu(3)
Real(dp) :: HPPloopFe(3)

 Real(dp) :: m32, tanbetaMZ 
Complex(dp),Dimension(3,3)::Y_l,Y_d,Y_u,Y_l_mZ,Y_d_mZ,Y_u_mZ&
&,Y_l_0,Y_d_0,Y_u_0
Real(dp),Dimension(3)::gauge,gauge_mZ,gauge_0 
Real(dp)::tanb,vevSM(2),tanb_mZ 
Contains 
 
Real(dp) Function Kronecker(t1,t2) Result(d) 
Implicit None 
Integer,Intent(in)::t1,t2 
If(t1.eq.t2) Then 
d=1. 
Else 
d=0. 
End If 
End Function Kronecker 

Real(dp) Function ThetaStep(t1,t2) Result(d) 
Implicit None 
Integer,Intent(in)::t1,t2 
If(t1.le.t2) Then 
d=1. 
Else 
d=0. 
End If 
End Function ThetaStep 

Real(dp) Function epsTensor(t1,t2,t3) Result(e)
Implicit None
Integer,Intent(in)::t1,t2,t3
If ((t1.eq.1).and.(t2.eq.2).and.(t3.eq.3)) Then
  e=1.
Else If ((t1.eq.2).and.(t2.eq.3).and.(t3.eq.1)) Then
  e=1.
Else If ((t1.eq.3).and.(t2.eq.1).and.(t3.eq.2)) Then
  e=1.
Else If ((t1.eq.3).and.(t2.eq.2).and.(t3.eq.1)) Then
  e=-1.
Else If ((t1.eq.2).and.(t2.eq.1).and.(t3.eq.3)) Then
  e=-1.
Else If ((t1.eq.1).and.(t2.eq.3).and.(t3.eq.2)) Then
  e=-1.
Else
  e=0.
End If
End Function epsTensor
Real(dp) Function gGMSB(ratio) 
Implicit None 
 Real(dp),Intent(in)::ratio 
 gGMSB=(1._dp+ratio)/ratio**2*Log(1._dp+ratio)& 
   &+(1._dp-ratio)/ratio**2*Log(1._dp-ratio) 
End Function gGMSB 
 
Real(dp) Function fGMSB(ratio) 
Implicit None 
Real(dp),Intent(in)::ratio 
If (ratio.lt.0.0001) Then 
 fGMSB = 1._dp 
Else 
 fGMSB=(1._dp+ratio)/ratio**2*(Log(1._dp+ratio)&
  & -2._dp*Li2(ratio/(1._dp+ratio))&
  & +0.5_dp*Li2(2._dp*ratio/(1._dp+ratio)))&
  & +(1._dp-ratio)/ratio**2*(Log(1._dp-ratio)&
  & -2._dp*Li2(ratio/(ratio-1._dp))&
  & +0.5_dp*Li2(2._dp*ratio/(ratio-1._dp)))
End If 
End Function fGMSB 
 
Complex(dp) Recursive Function h(a,b) 
Implicit None 
Real(dp),Intent(in)::a,b 
h=1._dp-(Log(a)*Log(b))/2._dp-&
& ((-(1._dp,-10D-12)+a+b)*(Pi2o6&
& +CLi2(-(((1._dp,-10D-12)-a+b-Sqrt((1._dp,-10.D-12)+(a-b)**2-&
& 2._dp*(a+b)))/&
& ((1._dp,-10D-12)+a-b+Sqrt((1._dp,-10D-12)+&
& (a-b)**2-2._dp*(a+b)))))&
& +CLi2(-((1._dp+a-b-Sqrt((1._dp,-10D-12)+&
& (a-b)**2-2._dp*(a+b)))/&
& ((1._dp,-10D-12)-a+b+Sqrt((1._dp,-10D-12)+&
& (a-b)**2-2._dp*(a+b)))))&
& -Log(((1._dp,-10D-12)-a+b-&
& Sqrt((1._dp,-10D-12)+(a-b)**2-2._dp*(a+b)))/&
& ((1._dp,-10D-12)+a-b-Sqrt((1._dp,-10D-12)+&
& (a-b)**2-2._dp*(a+b))))**2/4._dp&
& +Log(((1._dp,-10D-12)-a+b-&
& Sqrt((1._dp,-10D-12)+(a-b)**2-2._dp*(a+b)))/&
& ((1._dp,-10D-12)+a-b+Sqrt((1._dp,-10D-12)+&
& (a-b)**2-2._dp*(a+b))))**2/4._dp&
& +Log(((1._dp,10D-12)+a-b-&
& Sqrt((1._dp,10D-12)+(a-b)**2-2._dp*(a+b)))/&
& ((1._dp,10D-12)-a+b+Sqrt((1._dp,10D-12)+&
& (a-b)**2-2._dp*(a+b))))**2/4._dp&
& +Log(((1._dp,10D-12)-a+b+&
& Sqrt((1._dp,-10.D-12)+(a-b)**2-&
& (2._dp,10.D-12)*(a+b)))/((1._dp,-10D-12)+a-b+&
& Sqrt((1._dp,-10.D-12)+(a-b)**2-2._dp*(a+b))))**2/4._dp))/&
& Sqrt((1._dp,-10.D-12)+(a-b)**2-2._dp*(a+b))
End Function h 
 
Complex(dp) Function SQuiver(xQ,yQ) 
Implicit None 
Real(dp),Intent(in)::xQ,yQ 
SQuiver=(-8._dp*xQ**2+4._dp*xQ*yQ**2*atanh(xQ)&
 & -4._dp*(4._dp+yQ**2)*h(1._dp,yQ**2)+(-1._dp+xQ)*(-8._dp+8._dp*xQ+&
 & yQ**2)*h(1._dp,yQ**2/(1._dp-xQ))+8._dp*h(1._dp,yQ**2/(1._dp+xQ))+&
 & 16._dp*xQ*h(1._dp,yQ**2/(1._dp+xQ))+&
 & 8._dp*xQ**2*h(1._dp,yQ**2/(1._dp+xQ))-&
 & yQ**2*h(1._dp,yQ**2/(1._dp+xQ))-&
 & xQ*yQ**2*h(1._dp,yQ**2/(1._dp+xQ))&
 & +4._dp*xQ*h(1._dp/(1._dp-xQ),yQ**2/(1._dp-xQ))-&
 & 4._dp*xQ**2*h(1._dp/(1._dp-xQ),yQ**2/(1._dp-xQ))+&
 & 2._dp*yQ**2*h(1._dp/(1._dp-xQ),yQ**2/(1._dp-xQ))-&
 & 2._dp*xQ*yQ**2*h(1._dp/(1._dp-xQ),yQ**2/(1._dp-xQ))+&
 & 4._dp*xQ*h(1._dp-xQ,yQ**2)+2._dp*yQ**2*h(1._dp-xQ,yQ**2)-&
 & 4._dp*xQ*h(1._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))-&
 & 4._dp*xQ**2*h(1._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))+&
 & 2._dp*yQ**2*h(1._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))+&
 & 2._dp*xQ*yQ**2*h(1._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))-&
 & 4._dp*xQ*h(1._dp+xQ,yQ**2)+2._dp*yQ**2*h(1._dp+xQ,yQ**2)-&
 & yQ**2*h((1._dp+xQ)/(1._dp-xQ),yQ**2/(1._dp-xQ))+&
 & xQ*yQ**2*h((1._dp+xQ)/(1._dp-xQ),yQ**2/(1._dp-xQ))-&
 & yQ**2*h(-1._dp+2._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))-&
 & xQ*yQ**2*h(-1._dp+2._dp/(1._dp+xQ),yQ**2/(1._dp+xQ))-&
 & 4._dp*yQ**2*h(yQ**(-2),yQ**(-2))+&
 & 2._dp*xQ*yQ**2*h((1._dp-xQ)/yQ**2,yQ**(-2))+&
 & 2._dp*yQ**2*h((1._dp-xQ)/yQ**2,(1._dp-xQ)/yQ**2)-&
 & 2._dp*xQ*yQ**2*h((1._dp-xQ)/yQ**2,(1._dp-xQ)/yQ**2)-&
 & 2._dp*xQ*yQ**2*h((1._dp+xQ)/yQ**2,yQ**(-2))+&
 & 2._dp*yQ**2*h((1._dp+xQ)/yQ**2,(1._dp+xQ)/yQ**2)+&
 & 2._dp*xQ*yQ**2*h((1._dp+xQ)/yQ**2,(1._dp+xQ)/yQ**2)-&
 & 8._dp*xQ*CLi2((1._dp,10D-12)*xQ)+&
 & 4._dp*(-1._dp+xQ)*(xQ+yQ**2)*CLi2(xQ/(-(1._dp,10D-12)+xQ))-&
 & (-1._dp+xQ)*yQ**2*CLi2((2._dp*xQ)/(-(1._dp,10D-12)+xQ))+&
 & 2._dp*xQ*CLi2((1._dp,10D-12)*xQ**2)+&
 & 4._dp*(1._dp+xQ)*(xQ-yQ**2)*CLi2(xQ/((1._dp,10D-12)+xQ))+&
 & (1._dp+xQ)*yQ**2*CLi2(((2._dp,10D-12)*xQ)/(1._dp+xQ))+&
 & 2._dp*yQ**2*Log(1._dp-xQ)+&
 & 2._dp*yQ**2*Log(1._dp+xQ))/(2._dp*xQ**2*yQ**2)
End Function SQuiver 
 
Subroutine RGE10_SMa(len,t,gy,f)
 !--------------------------------------------------------
 ! RGEs within the SM assuming the MSbar scheme
 ! 2-loop RGEs for e
 ! 4-loop RGEs for g_3
 ! 2-loop RGEs for lepton masses
 ! 4-loop QCD and 2-loop QED RGES for quark masses
 ! Assumption: the only threhold to be checked is m_b
 ! input: t = Log(Q^2)
 !        gy(i) ... i=1  -> e(Q)
 !                  i=2  -> g_3
 !                  i=3  -> m_e
 !                  i=4  -> m_mu
 !                  i=5  -> m_tau
 !                  i=6  -> m_u
 !                  i=7  -> m_c
 !                  i=8  -> m_d
 !                  i=9  -> m_s
 !                  i=10 -> m_b, is optional
 ! output:
 !   f = d(gy)/d(t)
 ! written by Werner Porod, 03.12.03
 !--------------------------------------------------------
 Implicit None

  Integer, Intent(in) :: len
  Real(dp), Intent(in) :: t, gy(len)
  Real(dp), Intent(out) :: f(len)

  Integer :: i1
  Real(dp) :: g32, g34, g36, g38, e2, e4, g32e2, q
  Real(dp), Parameter :: b_e1(2) = (/ 76._dp / 9._dp , 80._dp / 9._dp /)    &
       & , b_e2(2) = (/ 460._dp / 27._dp , 464._dp / 27._dp /)              & 
       & , b_e3(2) = (/ 160._dp / 9._dp , 176._dp / 9._dp  /)               & 
       & , b_g1(2) = (/ -25._dp / 3._dp, -23._dp/3._dp /)                   &
       & , b_g2(2) = (/ -154._dp / 3._dp, -116._dp/3._dp /)                 &
       & , b_g3(2) = (/ 20._dp / 3._dp, 22._dp/3._dp /)                     &
       & , b_g4(2) = (/ -21943._dp/54._dp, 9769._dp/54._dp /)               &
       & , b_g5(2) = (/ -4918247._dp/1458._dp-414140._dp*zeta3/81._dp       &
       &             , 598391._dp/1458._dp - 352864._dp*zeta3/81._dp /)     &
       & , g_el1(2) = (/ -6._dp, -6._dp /)                                  &
       & , g_el2(2) = (/ 353._dp / 9._dp,  373._dp / 9._dp /)               & 
       & , g_eu1(2) = (/ -8._dp/3._dp, -8._dp/3._dp /)                      &
       & , g_eu2(2) = (/ 1472._dp / 81._dp, 1552._dp / 81._dp/)             & 
       & , g_eu3(2) = (/ -32._dp / 9._dp,  -32._dp / 9._dp/)                & 
       & , g_ed1(2) = (/ -2._dp/3._dp, -2._dp/3._dp /)                      &
       & , g_ed2(2) = (/ 377._dp / 81._dp,  397._dp / 81._dp /)             & 
       & , g_ed3(2) = (/ -8._dp / 9._dp,  -8._dp / 9._dp /)                 & 
       & , g_q1(2) = (/ - 8._dp , -8._dp /)                                 &
       & , g_q2(2) = (/ -1052._dp / 9._dp ,  -1012._dp / 9._dp /)           &
       & , g_q3(2) = (/ -144674._dp/81._dp + 1280._dp * zeta3 / 3._dp       &
       &              , -128858._dp/81._dp + 1600._dp * zeta3 / 3._dp /)    &
       & , g_q4(2) = (/ -7330357._dp/243._dp + 51584._dp* zeta3/3._dp       &
       &                - 16000._dp*zeta4 / 3._dp + 11200._dp* zeta5 /9._dp &
       &             , -1911065._dp/81._dp + 618400._dp* zeta3/27._dp       &
       &                - 18400._dp*zeta4 / 3._dp - 25600._dp* zeta5 /9._dp  /)

       
  Iname = Iname + 1
  NameOfUnit(Iname) = 'RGE10_SMa'

  q = t

  If (len.Eq.9) Then ! check which beta function (anomalous dimension) to use
   i1 = 1
  Else If (len.Eq.10) Then
   i1 = 2
  Else
   Write(ErrCan,*) "Error in routine "//Trim(NameOfUnit(Iname))
   Write(ErrCan,*) "Length of the vector gy = ",len
   Call TerminateProgram
  End If

  g32 = gy(1)**2
  g34 = gy(1)**4
  g36 = gy(1)**6
  g38 = gy(1)**8
  e2 = gy(2)**2
  e4 = gy(2)**4
  g32e2 = g32 * e2 
 !--------
 ! g_3
 !--------
  f(1) = oo16pi2 * gy(1) * ( b_g1(i1)*g32                                     &
       &                   + oo16pi2 * ( b_g2(i1)*g34 + b_g3(i1)*g32e2        &
       &                               + oo16pi2 * ( b_g4(i1)*g36             &
       &                                           + oo16pi2 * b_g5(i1)*g38 )))
 !--------
 ! e
 !--------
  f(2) = oo16pi2 * gy(2) * ( b_e1(i1) * e2                                &
       &                   + oo16pi2 * (b_e2(i1) * e4 + b_e3(i1) * g32e2 ))
 !-----------------
 ! m_l, l=e,mu,tau
 !-----------------
  f(3:5) =  oo16pi2 * gy(3:5) * (g_el1(i1) * e2 + oo16pi2 *g_el2(i1) * e4)
 !---------
 ! m_u, m_c
 !---------
  f(6:7) = oo16pi2 * gy(6:7) * (g_eu1(i1) * e2 + g_q1(i1) * g32              &
         &                     + oo16pi2 * (g_eu2(i1)*e4 + g_eu3(i1) * g32e2 &
         &                                 + g_q2(i1) * g34                  &
         &                                 + oo16pi2 * (g_q3(i1) * g36       &
         &                                       + oo16pi2 * g_q4(i1) * g38 )))
 !---------------
 ! m_d, m_s, m_b
 !---------------
  f(8:len) = oo16pi2 * gy(8:len) * (g_ed1(i1) * e2 + g_q1(i1) * g32          &
         &                     + oo16pi2 * (g_ed2(i1)*e4 + g_ed3(i1) * g32e2 &
         &                                 + g_q2(i1) * g34                  &
         &                                 + oo16pi2 * (g_q3(i1) * g36       &
         &                                       + oo16pi2 * g_q4(i1) * g38 )))

  Iname = Iname - 1

 End Subroutine RGE10_SMa

Subroutine RGE11_SMa(len,t,gy,f)
  Implicit None
  Integer, Intent(in) :: len
  Real(dp), Intent(in) :: t, gy(len)
  Real(dp), Intent(out) :: f(len)

  Real(dp) :: g3, e, md, mu, ms, mc, mt, mb, ml, mmu, mtau
  Real(dp) :: g32, g34, g36, g38, e2, e4, g32e2
  Real(dp) :: nQuark
  Real(dp) :: gamma1, gamma3, gamma13, gamma11,  gamma33, gamma333

  nQuark = nUp + nDown

  g3  = gy(2)
  g32 = gy(2)**2
  g34 = gy(2)**4
  g36 = gy(2)**6
  g38 = gy(2)**8
  e  = gy(1)
  e2 = gy(1)**2
  e4 = gy(1)**4
  g32e2 = g32 * e2 


  ! g3
  f(2) = g3*((2._dp/3._dp*nQuark - 11._dp)*g32 + (38._dp/3._dp*nQuark - 102)*g34*oo16pi2 + &
         & (8._dp/9._dp*nUp + 2._dp/9._dp*nDown)*oo16pi2*g32e2 + &
         & (5033._dp/18._dp*nQuark - 325._dp/54._dp*nQuark**2 - 2857._dp/2._dp)*g36*oo16pi2*oo16pi2)

  ! e
  f(1) = e*((16._dp/9._dp*nUp+4._dp/9._dp*nDown+4._dp/3._dp*nLep)*e2 + &
          & (64._dp/27._dp*nUp + 4._dp/27._dp*nDown + 4._dp*nLep)*e4*oo16pi2 + &
          & (64._dp/9._dp*nUp + 16._dp/9._dp*nDown)*g32e2*oo16pi2*oo16pi2)

  gamma1 = -6._dp
  gamma11 = -3._dp + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)

  ! m_e, m_mu, m_tau
  f(3:5) = gy(3:5)*(gamma1*e2 + oo16pi2*gamma11*e4)

  gamma1 = -6._dp*(2._dp/3._dp)
  gamma3 = -8._dp
  gamma11 = -3._dp*(2._dp/3._dp)**4 + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)*(2._dp/3._dp)**2
  gamma13 = -4._dp*(2._dp/3._dp)**2
  gamma33 = -404._dp/3._dp + 40._dp/9._dp*nQuark
  gamma333 = 2._dp/3._dp*(140._dp/27._dp*nQuark**2 + (160._dp*Zeta3 + 2216._dp/9._dp)*nQuark - 3747._dp)  

  ! m_u, m_c, m_t
  f(6:8) = gy(6:8)*(gamma1*e2 +  gamma3*g32 +  &
           & oo16pi2*(gamma11*e4 + gamma33*g34 + 2._dp*gamma13*g32e2) + &
           & gamma333*g36*oo16pi2*oo16pi2)


  ! m_d, m_s, m_b
  gamma1 = -6._dp*(-1._dp/3._dp)
  gamma3 = -8._dp
  gamma11 = -3._dp*(1._dp/3._dp)**4 + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)*(1._dp/3._dp)**2
  gamma13 = -4._dp*(1._dp/3._dp)**2
  gamma33 = -404._dp/3._dp + 40._dp/9._dp*nQuark
  gamma333 = 2._dp/3._dp*(140._dp/27._dp*nQuark**2 + (160._dp*Zeta3 + 2216._dp/9._dp)*nQuark - 3747._dp)  

  f(9:11) = gy(9:11)*(gamma1*e2 +  gamma3*g32 +  &
           & oo16pi2*(gamma11*e4 + gamma33*g34 + 2._dp*gamma13*g32e2) + &
           & gamma333*g36*oo16pi2*oo16pi2)

  If (nUp.lt.2.9_dp)  f(8) = 0._dp
  If (nDown.lt.2.9_dp)  f(12) = 0._dp

  f = oo16pi2*f


End Subroutine RGE11_SMa

Subroutine RGE11(len,t,gy,f)
  Implicit None
  Integer, Intent(in) :: len
  Real(dp), Intent(in) :: t, gy(len)
  Real(dp), Intent(out) :: f(len)

  Real(dp) :: g3, e, md, mu, ms, mc, mt, mb, ml, mmu, mtau
  Real(dp) :: g32, g34, g36, g38, e2, e4, g32e2
  Real(dp) :: nQuark, a1, a2, a3, nG
  Real(dp) :: gamma1, gamma3, gamma13, gamma11,  gamma33, gamma333

  nQuark = nUp + nDown

  g3  = gy(2)
  g32 = gy(2)**2
  g34 = gy(2)**4
  g36 = gy(2)**6
  g38 = gy(2)**8
  e  = gy(1)
  e2 = gy(1)**2
  e4 = gy(1)**4
  g32e2 = g32 * e2 

  nG = 3._dp
  a1 = gy(12)
  a2 = gy(13)
  a3 = gy(14)


  ! g3
  f(2) = g3*((2._dp/3._dp*nQuark - 11._dp)*g32 + (38._dp/3._dp*nQuark - 102)*g34*oo16pi2 + &
         & (8._dp/9._dp*nUp + 2._dp/9._dp*nDown)*oo16pi2*g32e2 + &
         & (5033._dp/18._dp*nQuark - 325._dp/54._dp*nQuark**2 - 2857._dp/2._dp)*g36*oo16pi2*oo16pi2)

  ! e
  f(1) = e*((16._dp/9._dp*nUp+4._dp/9._dp*nDown+4._dp/3._dp*nLep)*e2 + &
          & (64._dp/27._dp*nUp + 4._dp/27._dp*nDown + 4._dp*nLep)*e4*oo16pi2 + &
          & (64._dp/9._dp*nUp + 16._dp/9._dp*nDown)*g32e2*oo16pi2*oo16pi2)

  gamma1 = -6._dp
  gamma11 = -3._dp + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)

  ! m_e, m_mu, m_tau
  f(3:5) = gy(3:5)*(gamma1*e2 + oo16pi2*gamma11*e4)

  gamma1 = -6._dp*(2._dp/3._dp)
  gamma3 = -8._dp
  gamma11 = -3._dp*(2._dp/3._dp)**4 + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)*(2._dp/3._dp)**2
  gamma13 = -4._dp*(2._dp/3._dp)**2
  gamma33 = -404._dp/3._dp + 40._dp/9._dp*nQuark
  gamma333 = 2._dp/3._dp*(140._dp/27._dp*nQuark**2 + (160._dp*Zeta3 + 2216._dp/9._dp)*nQuark - 3747._dp)  

  ! m_u, m_c, m_t
  f(6:8) = gy(6:8)*(gamma1*e2 +  gamma3*g32 +  &
           & oo16pi2*(gamma11*e4 + gamma33*g34 + 2._dp*gamma13*g32e2) + &
           & gamma333*g36*oo16pi2*oo16pi2)


  ! m_d, m_s, m_b
  gamma1 = -6._dp*(-1._dp/3._dp)
  gamma3 = -8._dp
  gamma11 = -3._dp*(1._dp/3._dp)**4 + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)*(1._dp/3._dp)**2
  gamma13 = -4._dp*(1._dp/3._dp)**2
  gamma33 = -404._dp/3._dp + 40._dp/9._dp*nQuark
  gamma333 = 2._dp/3._dp*(140._dp/27._dp*nQuark**2 + (160._dp*Zeta3 + 2216._dp/9._dp)*nQuark - 3747._dp)  

  f(9:11) = gy(9:11)*(gamma1*e2 +  gamma3*g32 +  &
           & oo16pi2*(gamma11*e4 + gamma33*g34 + 2._dp*gamma13*g32e2) + &
           & gamma333*g36*oo16pi2*oo16pi2)



!! running of alpha_i to calculate running sin(w2); equations by Steinhauser
  ! alpha_1
  f(12) = a1**2*(2._dp/5._dp + nG*16._dp/3._dp) + &
    & a1**2*oo4pi2*(18._dp/25._dp*a1 + 18._dp/5._dp*a2 + nG*(76._dp/15._dp*a1 + 12._dp/5._dp*a2 + 176._dp/15._dp*a3))

  ! alpha_2
  f(13) = a2**2*(-86._dp/3._dp + nG*16._dp/3._dp) + &
   & a2**2*oo4pi2*(6._dp/5._dp*a1 - 518._dp/3._dp*a2 + nG*(4._dp/3._dp + 196._dp/3._dp*a2 + 16._dp*a3))

  ! alpha_3
  f(14) = a3**2*(-44._dp + nG*16._dp/3._dp) + &
    & a3**2*oo4pi2*(-408._dp*a3 + nG*(22._dp/15._dp*a1 + 6._dp*a2 + 304._dp/3._dp*a3))

  f = oo16pi2*f


End Subroutine RGE11


Subroutine RGEAlphaS(len,t,gy,f)
  Implicit None
  Integer, Intent(in) :: len
  Real(dp), Intent(in) :: t, gy(len)
  Real(dp), Intent(out) :: f(len)

  Real(dp) :: g3, e, md, mu, ms, mc, mt, mb, ml, mmu, mtau
  Real(dp) :: g32, g34, g36, g38, e2, e4, g32e2
  Real(dp) :: nQuark
  Real(dp) :: gamma1, gamma3, gamma13, gamma11,  gamma33, gamma333

  nQuark = nUp + nDown

  g3  = gy(2)
  g32 = gy(2)**2
  g34 = gy(2)**4
  g36 = gy(2)**6
  g38 = gy(2)**8
  e  = gy(1)
  e2 = gy(1)**2
  e4 = gy(1)**4
  g32e2 = g32 * e2 


  ! g3
  f(2) = g3*((2._dp/3._dp*nQuark - 11._dp)*g32 + (38._dp/3._dp*nQuark - 102)*g34*oo16pi2 + &
         & (8._dp/9._dp*nUp + 2._dp/9._dp*nDown)*oo16pi2*g32e2 + &
         & (5033._dp/18._dp*nQuark - 325._dp/54._dp*nQuark**2 - 2857._dp/2._dp)*g36*oo16pi2*oo16pi2)

  ! e
  f(1) = e*((16._dp/9._dp*nUp+4._dp/9._dp*nDown+4._dp/3._dp*nLep)*e2 + &
          & (64._dp/27._dp*nUp + 4._dp/27._dp*nDown + 4._dp*nLep)*e4*oo16pi2 + &
          & (64._dp/9._dp*nUp + 16._dp/9._dp*nDown)*g32e2*oo16pi2*oo16pi2)


  f = oo16pi2*f


End Subroutine RGEAlphaS

Subroutine RGETop(len,t,gy,f)
  Implicit None
  Integer, Intent(in) :: len
  Real(dp), Intent(in) :: t, gy(len)
  Real(dp), Intent(out) :: f(len)

  Real(dp) :: g3, e, md, mu, ms, mc, mt, mb, ml, mmu, mtau
  Real(dp) :: g32, g34, g36, g38, e2, e4, g32e2
  Real(dp) :: nQuark
  Real(dp) :: gamma1, gamma3, gamma13, gamma11,  gamma33, gamma333

  nQuark = nUp + nDown

  g3  = gy(2)
  g32 = gy(2)**2
  g34 = gy(2)**4
  g36 = gy(2)**6
  g38 = gy(2)**8
  e  = gy(1)
  e2 = gy(1)**2
  e4 = gy(1)**4
  g32e2 = g32 * e2 


  ! g3
  f(2) = g3*((2._dp/3._dp*nQuark - 11._dp)*g32 + (38._dp/3._dp*nQuark - 102)*g34*oo16pi2 + &
         & (8._dp/9._dp*nUp + 2._dp/9._dp*nDown)*oo16pi2*g32e2 + &
         & (5033._dp/18._dp*nQuark - 325._dp/54._dp*nQuark**2 - 2857._dp/2._dp)*g36*oo16pi2*oo16pi2)

  ! e
  f(1) = e*((16._dp/9._dp*nUp+4._dp/9._dp*nDown+4._dp/3._dp*nLep)*e2 + &
          & (64._dp/27._dp*nUp + 4._dp/27._dp*nDown + 4._dp*nLep)*e4*oo16pi2 + &
          & (64._dp/9._dp*nUp + 16._dp/9._dp*nDown)*g32e2*oo16pi2*oo16pi2)


  gamma1 = -6._dp*(2._dp/3._dp)
  gamma3 = -8._dp
  gamma11 = -3._dp*(2._dp/3._dp)**4 + (80._dp/9._dp*nUp + 20._dp/9._dp*nDown + 20._dp/3._dp*nLep)*(2._dp/3._dp)**2
  gamma13 = -4._dp*(2._dp/3._dp)**2
  gamma33 = -404._dp/3._dp + 40._dp/9._dp*nQuark
  gamma333 = 2._dp/3._dp*(140._dp/27._dp*nQuark**2 + (160._dp*Zeta3 + 2216._dp/9._dp)*nQuark - 3747._dp)  

  ! m_u, m_c, m_t
  f(3) = gy(3)*(gamma1*e2 +  gamma3*g32 +  &
           & oo16pi2*(gamma11*e4 + gamma33*g34 + 2._dp*gamma13*g32e2) + &
           & gamma333*g36*oo16pi2*oo16pi2)


  f = oo16pi2*f


End Subroutine RGETop
Subroutine SetGUTScale(scale)
Implicit None
Real(dp),Intent(in)::scale
If (scale.Lt.0._dp) Then
UseFixedGUTScale= .False.
Else
UseFixedGUTScale= .True.
GUT_scale=scale
End If
End Subroutine SetGUTScale
 

Subroutine SetRGEScale(scale)
Implicit None
Real(dp),Intent(in)::scale
Real(dp)::old_scale
If (scale.Lt.0._dp) Then
UseFixedScale= .False.
Else
UseFixedScale= .True.
old_scale=SetRenormalizationScale(scale)
End If
End Subroutine SetRGEScale


Logical Function SetStrictUnification(V1)
Implicit None
Logical,Intent(in)::V1
SetStrictUnification= .False.
StrictUnification=V1
SetStrictUnification= .True.
End Function SetStrictUnification


Integer Function SetYukawaScheme(V1)
Implicit None
Integer,Intent(in)::V1
SetYukawaScheme=YukawaScheme
YukawaScheme=V1
End Function SetYukawaScheme


Subroutine Set_All_Parameters_0() 
Implicit None 
Y_l= 0._dp 
Y_d= 0._dp 
Y_u= 0._dp 
Y_l_mZ= 0._dp 
Y_d_mZ= 0._dp 
Y_u_mZ= 0._dp 
Y_l_0= 0._dp 
Y_d_0= 0._dp 
Y_u_0= 0._dp 
gauge= 0._dp 
gauge_mZ= 0._dp 
gauge_0 = 0._dp 
tanb= 0._dp 
vevSM= 0._dp 
tanb_mZ = 0._dp 
GUT_scale = 0._dp 
HPPloopVWp = 0._dp 
HPPloopHp = 0._dp 
HPPloopFd = 0._dp 
HPPloopFu = 0._dp 
HPPloopFe = 0._dp 
g1IN = 0._dp 
g2IN = 0._dp 
g3IN = 0._dp 
Lam5IN = 0._dp 
Lam1IN = 0._dp 
Lam4IN = 0._dp 
Lam3IN = 0._dp 
Lam2IN = 0._dp 
YeIN = 0._dp 
YdIN = 0._dp 
YuIN = 0._dp 
mHd2IN = 0._dp 
mHu2IN = 0._dp 
g1 = 0._dp 
g1MZ = 0._dp 
g2 = 0._dp 
g2MZ = 0._dp 
g3 = 0._dp 
g3MZ = 0._dp 
Lam5 = 0._dp 
Lam5MZ = 0._dp 
Lam1 = 0._dp 
Lam1MZ = 0._dp 
Lam4 = 0._dp 
Lam4MZ = 0._dp 
Lam3 = 0._dp 
Lam3MZ = 0._dp 
Lam2 = 0._dp 
Lam2MZ = 0._dp 
Ye = 0._dp 
YeMZ = 0._dp 
Yd = 0._dp 
YdMZ = 0._dp 
Yu = 0._dp 
YuMZ = 0._dp 
mHd2 = 0._dp 
mHd2MZ = 0._dp 
mHu2 = 0._dp 
mHu2MZ = 0._dp 
vIN = 0._dp 
MA0 = 0._dp 
MA02 = 0._dp 
MFd = 0._dp 
MFd2 = 0._dp 
MFe = 0._dp 
MFe2 = 0._dp 
MFu = 0._dp 
MFu2 = 0._dp 
MG0 = 0._dp 
MG02 = 0._dp 
MH0 = 0._dp 
MH02 = 0._dp 
Mhh = 0._dp 
Mhh2 = 0._dp 
MHp = 0._dp 
MHp2 = 0._dp 
MVWp = 0._dp 
MVWp2 = 0._dp 
MVZ = 0._dp 
MVZ2 = 0._dp 
TW = 0._dp 
ZDL = 0._dp 
ZDR = 0._dp 
ZEL = 0._dp 
ZER = 0._dp 
ZP = 0._dp 
ZUL = 0._dp 
ZUR = 0._dp 
ZW = 0._dp 
ZZ = 0._dp 
betaH = 0._dp 
v = 0._dp 
gPFu = 0._dp 
gTFu = 0._dp 
BRFu = 0._dp 
gPFe = 0._dp 
gTFe = 0._dp 
BRFe = 0._dp 
gPFd = 0._dp 
gTFd = 0._dp 
BRFd = 0._dp 
gPhh = 0._dp 
gThh = 0._dp 
BRhh = 0._dp 
gPH0 = 0._dp 
gTH0 = 0._dp 
BRH0 = 0._dp 
gPA0 = 0._dp 
gTA0 = 0._dp 
BRA0 = 0._dp 
gPHp = 0._dp 
gTHp = 0._dp 
BRHp = 0._dp 
ratioFd =  0._dp  
ratioFe =  0._dp  
ratioFu =  0._dp  
ratioHp =  0._dp  
ratioVWp =  0._dp  
ratioGG =  0._dp  
ratioPP =  0._dp  
ratioPFd =  0._dp  
ratioPFe =  0._dp  
ratioPFu =  0._dp  
ratioPHp =  0._dp  
ratioPVWp =  0._dp  
ratioPGG =  0._dp  
ratioPPP =  0._dp  
Lambda1IN=(0._dp,0._dp) 
Lambda2IN=(0._dp,0._dp) 
Lambda3IN=(0._dp,0._dp) 
Lambda4IN=(0._dp,0._dp) 
Lambda5IN=(0._dp,0._dp) 
End Subroutine Set_All_Parameters_0 
 


Subroutine SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,v,g1,              & 
& g2,g3,Lam5,Lam1,Lam4,Lam3,Lam2,Ye,Yd,Yu,mHd2,mHu2,MZsuffix)

Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(inout) :: Lam5,Lam1,Lam4,Lam3,Lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(inout) :: v

Logical,Intent(in)::MZsuffix 
Real(dp), Intent(in) :: g1SM, g2SM, g3SM, vSM 
Complex(dp),Intent(in) :: YuSM(3,3),YdSM(3,3),YeSM(3,3) 
If (MZsuffix) Then 
  vMZ = vSM 
  YeMZ = YeSM 
  YdMZ = YdSM 
  YuMZ = YuSM 
  g1MZ = g1SM 
  g2MZ = g2SM 
  g3MZ = g3SM 
Else 
  v = vSM 
  Ye = YeSM 
  Yd = YdSM 
  Yu = YuSM 
  g1 = g1SM 
  g2 = g2SM 
  g3 = g3SM 
End if 
End Subroutine SetMatchingConditions 
End Module Model_Data_Inert