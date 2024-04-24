! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:54 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Program SPhenoInert2 
 
Use Control
Use InputOutput_Inert2
Use LoopFunctions
Use Settings
Use LowEnergy_Inert2
Use Mathematics
Use Model_Data_Inert2
Use Tadpoles_Inert2 
 !Use StandardModel
Use Boundaries_Inert2
 Use HiggsCS_Inert2
Use TreeLevelMasses_Inert2
Use LoopMasses_Inert2
 
Use BranchingRatios_Inert2
 
Implicit None
 
Real(dp) :: epsI=0.00001_dp, deltaM = 0.000001_dp 
Real(dp) :: mGut = -1._dp, ratioWoM = 0._dp
Integer :: kont, n_tot 
 
Integer,Parameter :: p_max=100
Real(dp) :: Ecms(p_max),Pm(p_max),Pp(p_max), dt, tz, Qin, gSM(11) 
Real(dp) :: vev, sinw2
Complex(dp) :: YdSM(3,3), YuSM(3,3), YeSM(3,3)
Real(dp) :: vSM, g1SM, g2SM, g3SM
Integer :: i1 
Logical :: ISR(p_max)=.False.
Logical :: CalcTBD
Real(dp) :: Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,ratioBsGamma,             & 
& BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,     & 
& BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,tauEgamma,tauMuGamma,         & 
& CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,         & 
& BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,     & 
& BrhtoMuE,BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,           & 
& BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,            & 
& BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,   & 
& BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,            & 
& BrBtoSMuMu,ratioBtoSMuMu,BrBtoKee,ratioBtoKee,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,     & 
& ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,    & 
& ratioKltoPinunu,BrK0eMu,ratioK0eMu,DelMK,ratioDelMK,epsK,ratioepsK

Tpar = 0._dp 
Spar = 0._dp 
Upar = 0._dp 
ae = 0._dp 
amu = 0._dp 
atau = 0._dp 
EDMe = 0._dp 
EDMmu = 0._dp 
EDMtau = 0._dp 
dRho = 0._dp 
BrBsGamma = 0._dp 
ratioBsGamma = 0._dp 
BrDmunu = 0._dp 
ratioDmunu = 0._dp 
BrDsmunu = 0._dp 
ratioDsmunu = 0._dp 
BrDstaunu = 0._dp 
ratioDstaunu = 0._dp 
BrBmunu = 0._dp 
ratioBmunu = 0._dp 
BrBtaunu = 0._dp 
ratioBtaunu = 0._dp 
BrKmunu = 0._dp 
ratioKmunu = 0._dp 
RK = 0._dp 
RKSM = 0._dp 
muEgamma = 0._dp 
tauEgamma = 0._dp 
tauMuGamma = 0._dp 
CRmuEAl = 0._dp 
CRmuETi = 0._dp 
CRmuESr = 0._dp 
CRmuESb = 0._dp 
CRmuEAu = 0._dp 
CRmuEPb = 0._dp 
BRmuTo3e = 0._dp 
BRtauTo3e = 0._dp 
BRtauTo3mu = 0._dp 
BRtauToemumu = 0._dp 
BRtauTomuee = 0._dp 
BRtauToemumu2 = 0._dp 
BRtauTomuee2 = 0._dp 
BrZtoMuE = 0._dp 
BrZtoTauE = 0._dp 
BrZtoTauMu = 0._dp 
BrhtoMuE = 0._dp 
BrhtoTauE = 0._dp 
BrhtoTauMu = 0._dp 
DeltaMBs = 0._dp 
ratioDeltaMBs = 0._dp 
DeltaMBq = 0._dp 
ratioDeltaMBq = 0._dp 
BrTautoEPi = 0._dp 
BrTautoEEta = 0._dp 
BrTautoEEtap = 0._dp 
BrTautoMuPi = 0._dp 
BrTautoMuEta = 0._dp 
BrTautoMuEtap = 0._dp 
BrB0dEE = 0._dp 
ratioB0dEE = 0._dp 
BrB0sEE = 0._dp 
ratioB0sEE = 0._dp 
BrB0dMuMu = 0._dp 
ratioB0dMuMu = 0._dp 
BrB0sMuMu = 0._dp 
ratioB0sMuMu = 0._dp 
BrB0dTauTau = 0._dp 
ratioB0dTauTau = 0._dp 
BrB0sTauTau = 0._dp 
ratioB0sTauTau = 0._dp 
BrBtoSEE = 0._dp 
ratioBtoSEE = 0._dp 
BrBtoSMuMu = 0._dp 
ratioBtoSMuMu = 0._dp 
BrBtoKee = 0._dp 
ratioBtoKee = 0._dp 
BrBtoKmumu = 0._dp 
ratioBtoKmumu = 0._dp 
BrBtoSnunu = 0._dp 
ratioBtoSnunu = 0._dp 
BrBtoDnunu = 0._dp 
ratioBtoDnunu = 0._dp 
BrKptoPipnunu = 0._dp 
ratioKptoPipnunu = 0._dp 
BrKltoPinunu = 0._dp 
ratioKltoPinunu = 0._dp 
BrK0eMu = 0._dp 
ratioK0eMu = 0._dp 
DelMK = 0._dp 
ratioDelMK = 0._dp 
epsK = 0._dp 
ratioepsK = 0._dp 
Call get_command_argument(1,inputFileName)
If (len_trim(inputFileName)==0) Then
  inputFileName="LesHouches.in.Inert2"
Else
  inputFileName=trim(inputFileName)
End if
Call get_command_argument(2,outputFileName)
If (len_trim(outputFileName)==0) Then
  outputFileName="SPheno.spc.Inert2"
Else
  outputFileName=trim(outputFileName)
End if 
g1SM = 0._dp 
g2SM = 0._dp 
g3SM = 0._dp 
YdSM = 0._dp 
YeSM = 0._dp 
YuSM = 0._dp 
vSM = 0._dp 
Call Set_All_Parameters_0() 
 
Qin = SetRenormalizationScale(1.6E2_dp**2)  
kont = 0 
delta_Mass = 0.0001_dp 
CalcTBD = .false. 
Call ReadingData(kont) 
 
 HighScaleModel = "LOW" 
If ((MatchingOrder.lt.-1).or.(MatchingOrder.gt.2)) Then 
  If (HighScaleModel.Eq."LOW") Then 
    If (.not.CalculateOneLoopMasses) Then 
       MatchingOrder = -1 
    Else 
       MatchingOrder =  2 
    End if 
   Else 
       MatchingOrder =  2 
   End If 
End If 
Select Case(MatchingOrder) 
 Case(0) 
   OneLoopMatching = .false. 
   TwoLoopMatching = .false. 
   GuessTwoLoopMatchingBSM = .false. 
 Case(1) 
   OneLoopMatching = .true. 
   TwoLoopMatching = .false. 
   GuessTwoLoopMatchingBSM = .false. 
 Case(2) 
   OneLoopMatching = .true. 
   TwoLoopMatching = .true. 
   GuessTwoLoopMatchingBSM = .true. 
End Select 
If (MatchingOrder.eq.-1) Then 
 ! Setting values 
 v = vIN 
 g1 = g1IN 
 g2 = g2IN 
 g3 = g3IN 
 lam5 = lam5IN 
 lam1 = lam1IN 
 lam4 = lam4IN 
 lam3 = lam3IN 
 lam2 = lam2IN 
 Ye = YeIN 
 Yd = YdIN 
 Yu = YuIN 
 MHD2 = MHD2IN 
 MHU2 = MHU2IN 
 lam1 = Lambdaa1IN
lam2 = Lambdaa2IN
lam3 = Lambdaa3IN
lam4 = Lambdaa4IN
lam5 = Lambdaa5IN
MHU2 = MHUIN

 
 ! Setting VEVs used for low energy constraints 
 vMZ = v 
    sinW2=1._dp-mW2/mZ2 
   vSM=1/Sqrt((G_F*Sqrt(2._dp)))
   g1SM=sqrt(4*Pi*Alpha_MZ/(1-sinW2)) 
   g2SM=sqrt(4*Pi*Alpha_MZ/Sinw2 ) 
   g3SM=sqrt(AlphaS_MZ*4*Pi) 
   Do i1=1,3 
      YuSM(i1,i1)=sqrt(2._dp)*mf_u(i1)/vSM 
      YeSM(i1,i1)=sqrt(2._dp)*mf_l(i1)/vSM 
      YdSM(i1,i1)=sqrt(2._dp)*mf_d(i1)/vSM 
    End Do 
    If (GenerationMixing) YuSM = Matmul(Transpose(CKM),YuSM) 


! Transpose Yukawas to fit SPheno conventions 
YuSM= Transpose(YuSM) 
YdSM= Transpose(YdSM)
YeSM= Transpose(YeSM)

 ! Setting Boundary conditions 
 Call SetMatchingConditions(g1SM,g2SM,g3SM,YuSM,YdSM,YeSM,vSM,v,g1,g2,g3,              & 
& lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,.False.)

lam1 = Lambdaa1IN
lam2 = Lambdaa2IN
lam3 = Lambdaa3IN
lam4 = Lambdaa4IN
lam5 = Lambdaa5IN
MHU2 = MHUIN
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,(/ ZeroC, ZeroC /))

Call OneLoopMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,             & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,             & 
& betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,kont)


 If (SignOfMassChanged) Then  
 If (.Not.IgnoreNegativeMasses) Then 
  Write(*,*) " Stopping calculation because of negative mass squared." 
  Call TerminateProgram 
 Else 
  SignOfMassChanged= .False. 
  kont=0  
 End If 
End If 
If (SignOfMuChanged) Then 
 If (.Not.IgnoreMuSignFlip) Then 
  Write(*,*) " Stopping calculation because of negative mass squared in tadpoles." 
  Call TerminateProgram 
 Else 
  SignOfMuChanged= .False. 
  kont=0 
 End If 
End If 

Else 
   If (GetMassUncertainty) Then 
   ! Uncertainty from Y_top 
 If ((CalculateOneLoopMasses).and.(CalculateTwoLoopHiggsMasses)) Then 
OneLoopMatching = .true. 
TwoLoopMatching = .false. 
GuessTwoLoopMatchingBSM = .True. 
Elseif ((CalculateOneLoopMasses).and.(.not.CalculateTwoLoopHiggsMasses)) Then  
OneLoopMatching = .true. 
TwoLoopMatching = .false. 
GuessTwoLoopMatchingBSM = .false. 
Else  
OneLoopMatching = .true. 
TwoLoopMatching = .false. 
GuessTwoLoopMatchingBSM = .false. 
End if 
Call CalculateSpectrum(n_run,delta_mass,WriteOut,kont,MA0,MA02,MFd,MFd2,              & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,              & 
& lam2,Ye,Yd,Yu,MHD2,MHU2,mGUT)

n_tot =1
mass_uncertainty_Yt(n_tot:n_tot+1) = MHp! difference will be taken later 
n_tot = n_tot + 2 
mass_uncertainty_Yt(n_tot:n_tot+0) = MG0! difference will be taken later 
n_tot = n_tot + 1 
mass_uncertainty_Yt(n_tot:n_tot+0) = Mhh! difference will be taken later 
n_tot = n_tot + 1 
mass_uncertainty_Yt(n_tot:n_tot+0) = MA0! difference will be taken later 
n_tot = n_tot + 1 
mass_uncertainty_Yt(n_tot:n_tot+0) = MH0! difference will be taken later 
If ((CalculateOneLoopMasses).and.(CalculateTwoLoopHiggsMasses)) Then 
OneLoopMatching = .true. 
TwoLoopMatching = .true. 
GuessTwoLoopMatchingBSM = .false. 
Elseif ((CalculateOneLoopMasses).and.(.not.CalculateTwoLoopHiggsMasses)) Then  
OneLoopMatching = .false. 
TwoLoopMatching = .false. 
GuessTwoLoopMatchingBSM = .false. 
Else  
OneLoopMatching = .false. 
TwoLoopMatching = .false. 
GuessTwoLoopMatchingBSM = .false. 
End if 
  End if 
 Call CalculateSpectrum(n_run,delta_mass,WriteOut,kont,MA0,MA02,MFd,MFd2,              & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,              & 
& lam2,Ye,Yd,Yu,MHD2,MHU2,mGUT)

  If (GetMassUncertainty) Then 
 Call GetScaleUncertainty(delta_mass,WriteOut,kont,MA0,MA02,MFd,MFd2,MFe,              & 
& MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,              & 
& ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,            & 
& Ye,Yd,Yu,MHD2,MHU2,mass_uncertainty_Q)

  End if 
 End If 
 ! Save correct Higgs masses for calculation of L -> 3 L' 
MhhL = Mhh
Mhh2L = MhhL**2 
MAhL = MG0
MAh2L = MAhL**2 
 
betaH = ASin(Abs(ZP(1,2)))
TW = ACos(Abs(ZZ(1,1)))
If ((L_BR).And.(kont.Eq.0)) Then 
 Call CalculateBR(CalcTBD,ratioWoM,epsI,deltaM,kont,MA0,MA02,MFd,MFd2,MFe,             & 
& MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,              & 
& ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,            & 
& Ye,Yd,Yu,MHD2,MHU2,gPFu,gTFu,BRFu,gPFe,gTFe,BRFe,gPFd,gTFd,BRFd,gPhh,gThh,             & 
& BRhh,gPH0,gTH0,BRH0,gPA0,gTA0,BRA0,gPHp,gTHp,BRHp)

End If 
 
 If (CalculateLowEnergy) then 
Call CalculateLowEnergyConstraints(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,              & 
& Yd,Yu,MHD2,MHU2,v,Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,         & 
& ratioBsGamma,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,           & 
& BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,           & 
& tauEgamma,tauMuGamma,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,         & 
& BRtauTo3e,BRtauTo3mu,BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2,              & 
& BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,    & 
& DeltaMBq,ratioDeltaMBq,BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,   & 
& BrTautoMuEtap,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,            & 
& BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,          & 
& BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu,BrBtoKee,ratioBtoKee,BrBtoKmumu,         & 
& ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,         & 
& ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,BrK0eMu,ratioK0eMu,DelMK,ratioDelMK,     & 
& epsK,ratioepsK)

MVZ = mz 
MVZ2 = mz2 
MVWp = mW 
MVWp2 = mW2 
If (WriteParametersAtQ) Then 
Call TreeMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,GenerationMixing,kont)

End If 
 
End if 
 
If ((FoundIterativeSolution).or.(WriteOutputForNonConvergence)) Then 
If (OutputForMO) Then 
Call RunningFermionMasses(MFe,MFe2,MFd,MFd2,MFu,MFu2,v,g1,g2,g3,lam5,lam1,            & 
& lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,kont)

End if 
Write(*,*) "Writing output files" 
Call LesHouches_Out(67,11,kont,MGUT,Tpar,Spar,Upar,ae,amu,atau,EDMe,EDMmu,            & 
& EDMtau,dRho,BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,            & 
& BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,     & 
& RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,         & 
& CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,BRtauTomuee,BRtauToemumu2,          & 
& BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,BrhtoTauE,BrhtoTauMu,              & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,BrTautoEEta,BrTautoEEtap,     & 
& BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,          & 
& BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,              & 
& BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu,              & 
& BrBtoKee,ratioBtoKee,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,     & 
& ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,             & 
& BrK0eMu,ratioK0eMu,DelMK,ratioDelMK,epsK,ratioepsK,GenerationMixing)

End if 
Write(*,*) "Finished!" 
Contains 
 
Subroutine CalculateSpectrum(n_run,delta,WriteOut,kont,MA0,MA02,MFd,MFd2,             & 
& MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,             & 
& TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,              & 
& lam2,Ye,Yd,Yu,MHD2,MHU2,mGUT)

Implicit None 
Integer, Intent(in) :: n_run 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: WriteOut 
Real(dp), Intent(in) :: delta 
Real(dp), Intent(inout) :: mGUT 
Real(dp),Intent(inout) :: g1,g2,g3,MHD2,MHU2

Complex(dp),Intent(inout) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp),Intent(inout) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp),Intent(inout) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp),Intent(inout) :: v

kont = 0 
Call FirstGuess(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,Mhh,            & 
& Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,betaH,           & 
& v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,kont)

!If (kont.ne.0) Call TerminateProgram 
 
If (SPA_Convention) Call SetRGEScale(1.e3_dp**2) 
 
If (.Not.UseFixedScale) Then 
 Call SetRGEScale(160._dp**2) 
End If
Call Match_and_Run(delta,MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,            & 
& MH02,Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,              & 
& ZW,ZZ,betaH,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,mGut,kont,            & 
& WriteOut,n_run)

If (kont.ne.0) Then 
 Write(*,*) "Error appeared in calculation of masses "
 
 Call TerminateProgram 
End If 
 
End Subroutine CalculateSpectrum 
 

 
Subroutine ReadingData(kont)
Implicit None
Integer,Intent(out)::kont
Logical::file_exists
kont=-123456
Inquire(file=inputFileName,exist=file_exists)
If (file_exists) Then
kont=1
Call LesHouches_Input(kont,Ecms,Pm,Pp,ISR,F_GMSB)
LesHouches_Format= .True.
Else
Write(*,*)&
& "File ",inputFileName," does not exist"
Call TerminateProgram
End If
End Subroutine ReadingData

 
Subroutine GetScaleUncertainty(delta,WriteOut,kont,MA0input,MA02input,MFdinput,       & 
& MFd2input,MFeinput,MFe2input,MFuinput,MFu2input,MG0input,MG02input,MH0input,           & 
& MH02input,Mhhinput,Mhh2input,MHpinput,MHp2input,MVWpinput,MVWp2input,MVZinput,         & 
& MVZ2input,TWinput,ZDLinput,ZDRinput,ZELinput,ZERinput,ZPinput,ZULinput,ZURinput,       & 
& ZWinput,ZZinput,betaHinput,vinput,g1input,g2input,g3input,lam5input,lam1input,         & 
& lam4input,lam3input,lam2input,Yeinput,Ydinput,Yuinput,MHD2input,MHU2input,             & 
& mass_Qerror)

Implicit None 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: WriteOut 
Real(dp), Intent(in) :: delta 
Real(dp) :: mass_in(15), mass_new(15) 
Real(dp), Intent(out) :: mass_Qerror(15) 
Real(dp) :: gD(70), Q, Qsave, Qstep, Qt, g_SM(62), mh_SM 
Integer :: i1, i2, iupdown, ntot 
Real(dp),Intent(in) :: g1input,g2input,g3input,MHD2input,MHU2input

Complex(dp),Intent(in) :: lam5input,lam1input,lam4input,lam3input,lam2input,Yeinput(3,3),Ydinput(3,3),          & 
& Yuinput(3,3)

Real(dp),Intent(in) :: MA0input,MA02input,MFdinput(3),MFd2input(3),MFeinput(3),MFe2input(3),MFuinput(3),     & 
& MFu2input(3),MG0input,MG02input,MH0input,MH02input,Mhhinput,Mhh2input,MHpinput(2),     & 
& MHp2input(2),MVWpinput,MVWp2input,MVZinput,MVZ2input,TWinput,ZPinput(2,2),             & 
& ZZinput(2,2),betaHinput

Complex(dp),Intent(in) :: ZDLinput(3,3),ZDRinput(3,3),ZELinput(3,3),ZERinput(3,3),ZULinput(3,3),ZURinput(3,3),  & 
& ZWinput(2,2)

Real(dp),Intent(in) :: vinput

Real(dp) :: g1,g2,g3,MHD2,MHU2

Complex(dp) :: lam5,lam1,lam4,lam3,lam2,Ye(3,3),Yd(3,3),Yu(3,3)

Real(dp) :: MA0,MA02,MFd(3),MFd2(3),MFe(3),MFe2(3),MFu(3),MFu2(3),MG0,MG02,MH0,MH02,              & 
& Mhh,Mhh2,MHp(2),MHp2(2),MVWp,MVWp2,MVZ,MVZ2,TW,ZP(2,2),ZZ(2,2),betaH

Complex(dp) :: ZDL(3,3),ZDR(3,3),ZEL(3,3),ZER(3,3),ZUL(3,3),ZUR(3,3),ZW(2,2)

Real(dp) :: v

kont = 0 
Write(*,*) "Check scale uncertainty" 
n_tot =1
mass_in(n_tot:n_tot+1) = MHpinput
n_tot = n_tot + 2 
mass_in(n_tot:n_tot+0) = MG0input
n_tot = n_tot + 1 
mass_in(n_tot:n_tot+0) = Mhhinput
n_tot = n_tot + 1 
mass_in(n_tot:n_tot+0) = MA0input
n_tot = n_tot + 1 
mass_in(n_tot:n_tot+0) = MH0input
mass_Qerror = 0._dp 
Qsave=sqrt(getRenormalizationScale()) 
Do iupdown=1,2 
If (iupdown.eq.1) Then 
  Qstep=Qsave/7._dp 
Else 
  Qstep=-0.5_dp*Qsave/7._dp 
End if 
Do i1=1,7 
Q=Qsave+i1*Qstep 
Qt = SetRenormalizationScale(Q**2) 
g1 = g1input
g2 = g2input
g3 = g3input
lam5 = lam5input
lam1 = lam1input
lam4 = lam4input
lam3 = lam3input
lam2 = lam2input
Ye = Yeinput
Yd = Ydinput
Yu = Yuinput
MHD2 = MHD2input
MHU2 = MHU2input
v = vinput

 
 ! --- GUT normalize gauge couplings --- 
g1 = Sqrt(5._dp/3._dp)*g1 
! ----------------------- 
 
Call ParametersToG70(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v,gD)

If (iupdown.eq.1) Then 
 tz=Log(Q/Qsave)
 dt=-tz/50._dp
 Call odeint(gD,70,0._dp,tz,0.1_dp*delta,dt,0._dp,rge70,kont)
Else 
 tz=-Log(Q/Qsave)
 dt=tz/50._dp
 Call odeint(gD,70,tz,0._dp,0.1_dp*delta,dt,0._dp,rge70,kont)
End if 
Call GToParameters70(gD,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,v)


 
 ! --- Remove GUT-normalization of gauge couplings --- 
g1 = Sqrt(3._dp/5._dp)*g1 
! ----------------------- 
 
Call SolveTadpoleEquations(g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,           & 
& MHU2,v,(/ ZeroC, ZeroC /))

Call OneLoopMasses(MA0,MA02,MFd,MFd2,MFe,MFe2,MFu,MFu2,MG0,MG02,MH0,MH02,             & 
& Mhh,Mhh2,MHp,MHp2,MVWp,MVWp2,MVZ,MVZ2,TW,ZDL,ZDR,ZEL,ZER,ZP,ZUL,ZUR,ZW,ZZ,             & 
& betaH,v,g1,g2,g3,lam5,lam1,lam4,lam3,lam2,Ye,Yd,Yu,MHD2,MHU2,kont)

If (Calculate_mh_within_SM) Then
g_SM=g_SM_save 
tz=0.5_dp*Log(mZ2/Q**2)
dt=tz/100._dp
g_SM(1)=Sqrt(5._dp/3._dp)*g_SM(1) 
Call odeint(g_SM,62,tz,0._dp,delta,dt,0._dp,rge62_SM,kont) 
g_SM(1)=Sqrt(3._dp/5._dp)*g_SM(1) 
Call Get_mh_pole_SM(g_SM,Q**2,delta,Mhh2,mh_SM)
Mhh2 = mh_SM**2 
Mhh = mh_SM 
End if
n_tot =1
mass_new(n_tot:n_tot+1) = MHp
n_tot = n_tot + 2 
mass_new(n_tot:n_tot+0) = MG0
n_tot = n_tot + 1 
mass_new(n_tot:n_tot+0) = Mhh
n_tot = n_tot + 1 
mass_new(n_tot:n_tot+0) = MA0
n_tot = n_tot + 1 
mass_new(n_tot:n_tot+0) = MH0
  Do i2=1,15 
    If (Abs(mass_new(i2)-mass_in(i2)).gt.mass_Qerror(i2)) mass_Qerror(i2) = Abs(mass_new(i2)-mass_in(i2)) 
  End Do 
End Do 
End Do 
  Do i2=1,15  
    mass_uncertainty_Yt(i2) = Abs(mass_uncertainty_Yt(i2)-mass_in(i2)) 
  End Do 
If (kont.ne.0) Then 
 Write(*,*) "Error appeared in check of scale uncertainty "
 
 Call TerminateProgram 
End If 
 
Qt = SetRenormalizationScale(Qsave**2) 
End Subroutine GetScaleUncertainty 
 

 
End Program SPhenoInert2 
