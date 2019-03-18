! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.8.1 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 15:03 on 22.11.2017   
! ----------------------------------------------------------------------  
 
 
Program SPhenoMSSM 
 
Use Control
Use InputOutput_MSSM
Use LoopFunctions
Use RunSM_MSSM
Use LowEnergy_MSSM
Use FlavorKit_LFV_MSSM
Use FlavorKit_QFV_MSSM
Use FlavorKit_Observables_MSSM
Use Mathematics
Use Model_Data_MSSM
Use Tadpoles_MSSM 
 Use RGEs_MSSM
!Use StandardModel
Use SugraRuns_MSSM
 Use FineTuning_MSSM
Use HiggsCS_MSSM
Use LoopMasses_MSSM
 
Use BranchingRatios_MSSM
 
Implicit None
 
Real(dp) :: epsI=0.00001_dp, deltaM = 0.000001_dp 
Real(dp) :: mGut = -1._dp, ratioWoM = 0._dp
Integer :: kont 
 
Integer,Parameter :: p_max=100
Real(dp) :: Ecms(p_max),Pm(p_max),Pp(p_max), dt, tz, Qin, gSM(11) 
Real(dp) :: vev, sinw2
Logical :: ISR(p_max)=.False.
Logical :: CalcTBD
Real(dp) :: ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,         & 
& BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,               & 
& ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,          & 
& CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,    & 
& BRtauTomuee,BRtauToemumu2,BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,         & 
& BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,         & 
& BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,               & 
& ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,           & 
& BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,            & 
& BrBtoSMuMu,ratioBtoSMuMu,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,            & 
& BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,  & 
& DelMK,ratioDelMK,epsK,ratioepsK

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
DelMK = 0._dp 
ratioDelMK = 0._dp 
epsK = 0._dp 
ratioepsK = 0._dp 
Call get_command_argument(1,inputFileName)
If (len_trim(inputFileName)==0) Then
  inputFileName="LesHouches.in.MSSM"
Else
  inputFileName=trim(inputFileName)
End if
Call get_command_argument(2,outputFileName)
If (len_trim(outputFileName)==0) Then
  outputFileName="SPheno.spc.MSSM"
Else
  outputFileName=trim(outputFileName)
End if 
Call Set_All_Parameters_0() 
 
Qin = SetRenormalizationScale(1.0E3_dp**2)  
kont = 0 
delta_Mass = 0.0001_dp 
CalcTBD = .false. 
Call ReadingData(kont) 
 
If ((HighScaleModel.Eq."LOW").and.(.not.SUSYrunningFromMZ)) Then ! No longer used by default 
 ! Setting values 
 vd = vdIN 
 vu = vuIN 
 Mu = MuIN 
 Td = TdIN 
 Te = TeIN 
 Tu = TuIN 
 Bmu = BmuIN 
 mq2 = mq2IN 
 ml2 = ml2IN 
 mHd2 = mHd2IN 
 mHu2 = mHu2IN 
 md2 = md2IN 
 mu2 = mu2IN 
 me2 = me2IN 
 M1 = M1IN 
 M2 = M2IN 
 M3 = M3IN 
 g1 = g1IN 
 g2 = g2IN 
 g3 = g3IN 
 Yd = YdIN 
 Ye = YeIN 
 Yu = YuIN 
 M1 = M1input
M2 = M2input
M3 = M3input
Mu = Muinput
Bmu = MA2input/(1/TanBeta + TanBeta)
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
tanbetaMZ = tanbeta 

 
 ! Setting VEVs used for low energy constraints 
 vdMZ = vd 
 vuMZ = vu 
 
 
 ! RGE running for gauge and Yukawa couplings from M_Z to M_SUSY 
 Qin=sqrt(getRenormalizationScale()) 
If (SMrunningLowScaleInput) Then 
Call RunSM(Qin,deltaM,tanbeta,g1,g2,g3,Yu,Yd,Ye,vd,vu) 
End if 

 ! Setting Boundary conditions 
 M1 = M1input
M2 = M2input
M3 = M3input
Mu = Muinput
Bmu = MA2input/(1/TanBeta + TanBeta)
vd = (2*Sqrt(mz2/(g1**2 + g2**2)))/Sqrt(1 + TanBeta**2)
vu = (2*Sqrt(mz2/(g1**2 + g2**2))*TanBeta)/Sqrt(1 + TanBeta**2)
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

Call OneLoopMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,              & 
& MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,               & 
& MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,            & 
& ZUR,ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,             & 
& mHd2,mHu2,md2,mu2,me2,M1,M2,M3,kont)


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
 Call CalculateSpectrum(n_run,delta_mass,WriteOut,kont,MAh,MAh2,MCha,MCha2,            & 
& MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,              & 
& MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,               & 
& ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,              & 
& g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,mGUT)

End If 
 ! Save correct Higgs masses for calculation of L -> 3 L' 
MhhL = Mhh
Mhh2L = MhhL**2 
MAhL = MAh
MAh2L = MAhL**2 
 
v = Sqrt(vd**2 + vu**2)
betaH = ASin(Abs(ZP(1,2)))
alphaH = ACos(ZH(1,2))
TW = ACos(Abs(ZZ(1,1)))
If ((L_BR).And.(kont.Eq.0)) Then 
 sinW2=1._dp-mW2/mZ2 
vev=Sqrt(mZ2*(1._dp-sinW2)*SinW2/(pi*alpha_mZ))
vdMZ=vev/Sqrt(1._dp+tanbetaMZ**2)
vuMZ=tanbetaMZ*vdMZ 
Call CalculateBR(CalcTBD,ratioWoM,epsI,deltaM,kont,MAh,MAh2,MCha,MCha2,               & 
& MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,              & 
& MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,               & 
& ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,vdMZ,vuMZ,g1,             & 
& g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,gPSd,            & 
& gTSd,BRSd,gPSu,gTSu,BRSu,gPSe,gTSe,BRSe,gPSv,gTSv,BRSv,gPhh,gThh,BRhh,gPAh,            & 
& gTAh,BRAh,gPHpm,gTHpm,BRHpm,gPGlu,gTGlu,BRGlu,gPChi,gTChi,BRChi,gPCha,gTCha,           & 
& BRCha,gPFu,gTFu,BRFu)

Call HiggsCrossSections(Mhh,ratioGG,ratioPP,rHB_S_VWm,rHB_S_VZ,rHB_S_S_Fu(:,3)        & 
& ,CS_Higgs_LHC,kont)

Call HiggsCrossSections(MAh,ratioPGG,ratioPPP,0._dp*rHB_S_VWm,0._dp*rHB_S_VZ,         & 
& rHB_P_S_Fu(:,3),CS_PHiggs_LHC,kont)

End If 
 
 If (CalculateLowEnergy) then 
Call CalculateLowEnergyConstraints(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,             & 
& ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,           & 
& BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,              & 
& ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,               & 
& RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,         & 
& CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,BRtauTomuee,BRtauToemumu2,          & 
& BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,BrhtoTauE,BrhtoTauMu,              & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,BrTautoEEta,BrTautoEEtap,     & 
& BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,          & 
& BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,              & 
& BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu,              & 
& BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu,            & 
& BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,DelMK,ratioDelMK,          & 
& epsK,ratioepsK)

MVZ = mz 
MVZ2 = mz2 
MVWm = mW 
MVWm2 = mW2 
If (WriteParametersAtQ) Then 
Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,GenerationMixing,kont)

End If 
 
End if 
 
If (HighScaleModel.ne."LOW") Then 
  If (calcFT) Then 
Call FineTuning(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,              & 
& mu2,me2,M1,M2,M3,vd,vu,mGut,kont)

 End If 
End If 
If ((FoundIterativeSolution).or.(WriteOutputForNonConvergence)) Then 
Write(*,*) "Writing output files" 
Call LesHouches_Out(67,11,kont,MGUT,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,               & 
& BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,              & 
& ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,               & 
& RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,         & 
& CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,BRtauTomuee,BRtauToemumu2,          & 
& BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,BrhtoTauE,BrhtoTauMu,              & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,BrTautoEEta,BrTautoEEtap,     & 
& BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,          & 
& BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,              & 
& BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu,              & 
& BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu,            & 
& BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,DelMK,ratioDelMK,          & 
& epsK,ratioepsK,GenerationMixing)

End if 
Write(*,*) "Finished!" 
Contains 
 
Subroutine CalculateSpectrum(n_run,delta,WriteOut,kont,MAh,MAh2,MCha,MCha2,           & 
& MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,              & 
& MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,               & 
& ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,              & 
& g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,mGUT)

Implicit None 
Integer, Intent(in) :: n_run 
Integer, Intent(inout) :: kont 
Logical, Intent(in) :: WriteOut 
Real(dp), Intent(in) :: delta 
Real(dp), Intent(inout) :: mGUT 
Real(dp),Intent(inout) :: g1,g2,g3,mHd2,mHu2

Complex(dp),Intent(inout) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Real(dp),Intent(inout) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp),Intent(inout) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp),Intent(inout) :: vd,vu

kont = 0 
Select Case(BoundaryCondition) 
Case (1) 
  ! Free GUT scale 
Case (2) 
  Call SetGUTscale(MessengerScale) 
End Select 

Call FirstGuess(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,kont)

!If (kont.ne.0) Call TerminateProgram 
 
If (SPA_Convention) Call SetRGEScale(1.e3_dp**2) 
 
Call Sugra(delta,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,           & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,             & 
& md2,mu2,me2,M1,M2,M3,mGut,kont,WriteOut,n_run)

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

 
Subroutine CalculateLowEnergyConstraints(g1input,g2input,g3input,Ydinput,             & 
& Yeinput,Yuinput,Muinput,Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,            & 
& mHd2input,mHu2input,md2input,mu2input,me2input,M1input,M2input,M3input,vdinput,        & 
& vuinput,ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,ratioBsGamma,BrDmunu,             & 
& ratioDmunu,BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,             & 
& BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,tauEgamma,tauMuGamma,         & 
& CRmuEAl,CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,         & 
& BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,     & 
& BrhtoMuE,BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,           & 
& BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,            & 
& BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,   & 
& BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,            & 
& BrBtoSMuMu,ratioBtoSMuMu,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,            & 
& BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,  & 
& DelMK,ratioDelMK,epsK,ratioepsK)

Real(dp),Intent(inout) :: g1input,g2input,g3input,mHd2input,mHu2input,vdinput,vuinput

Complex(dp),Intent(inout) :: Ydinput(3,3),Yeinput(3,3),Yuinput(3,3),Muinput,Tdinput(3,3),Teinput(3,3),             & 
& Tuinput(3,3),Bmuinput,mq2input(3,3),ml2input(3,3),md2input(3,3),mu2input(3,3),         & 
& me2input(3,3),M1input,M2input,M3input

Real(dp) :: MAh(2),MAh2(2),MCha(2),MCha2(2),MChi(4),MChi2(4),MFd(3),MFd2(3),MFe(3),               & 
& MFe2(3),MFu(3),MFu2(3),MGlu,MGlu2,Mhh(2),Mhh2(2),MHpm(2),MHpm2(2),MSd(6),              & 
& MSd2(6),MSe(6),MSe2(6),MSu(6),MSu2(6),MSv(3),MSv2(3),MVWm,MVWm2,MVZ,MVZ2,              & 
& TW,v,ZA(2,2),ZH(2,2),ZP(2,2),ZZ(2,2),alphaH,betaH

Complex(dp) :: pG,UM(2,2),UP(2,2),ZD(6,6),ZDL(3,3),ZDR(3,3),ZE(6,6),ZEL(3,3),ZER(3,3),               & 
& ZN(4,4),ZU(6,6),ZUL(3,3),ZUR(3,3),ZV(3,3),ZW(2,2)

Real(dp) :: g1,g2,g3,mHd2,mHu2,vd,vu

Complex(dp) :: Yd(3,3),Ye(3,3),Yu(3,3),Mu,Td(3,3),Te(3,3),Tu(3,3),Bmu,mq2(3,3),ml2(3,3),             & 
& md2(3,3),mu2(3,3),me2(3,3),M1,M2,M3

Complex(dp) :: cplAhAhcVWmVWm(2,2),cplAhAhhh(2,2,2),cplAhAhVZVZ(2,2),cplAhcHpmVWm(2,2),              & 
& cplAhhhVZ(2,2),cplAhHpmcHpm(2,2,2),cplAhHpmcVWm(2,2),cplAhSdcSd(2,6,6),cplAhSecSe(2,6,6),& 
& cplAhSucSu(2,6,6),cplcChacFuSdL(2,3,6),cplcChacFuSdR(2,3,6),cplcChacFvSeL(2,3,6),      & 
& cplcChacFvSeR(2,3,6),cplcChaChaAhL(2,2,2),cplcChaChaAhR(2,2,2),cplcChaChahhL(2,2,2),   & 
& cplcChaChahhR(2,2,2),cplcChaChaVPL(2,2),cplcChaChaVPR(2,2),cplcChaChaVZL(2,2),         & 
& cplcChaChaVZR(2,2),cplcChaChiHpmL(2,4,2),cplcChaChiHpmR(2,4,2),cplcChaChiVWmL(2,4),    & 
& cplcChaChiVWmR(2,4),cplcChaFdcSuL(2,3,6),cplcChaFdcSuR(2,3,6),cplcChaFecSvL(2,3,3),    & 
& cplcChaFecSvR(2,3,3),cplcFdChaSuL(3,2,6),cplcFdChaSuR(3,2,6),cplcFdChiSdL(3,4,6),      & 
& cplcFdChiSdR(3,4,6),cplcFdFdAhL(3,3,2),cplcFdFdAhR(3,3,2),cplcFdFdhhL(3,3,2),          & 
& cplcFdFdhhR(3,3,2),cplcFdFdVGL(3,3),cplcFdFdVGR(3,3),cplcFdFdVPL(3,3),cplcFdFdVPR(3,3),& 
& cplcFdFdVZL(3,3),cplcFdFdVZR(3,3),cplcFdFuHpmL(3,3,2),cplcFdFuHpmR(3,3,2),             & 
& cplcFdFuVWmL(3,3),cplcFdFuVWmR(3,3),cplcFdGluSdL(3,6),cplcFdGluSdR(3,6),               & 
& cplcFeChaSvL(3,2,3),cplcFeChaSvR(3,2,3),cplcFeChiSeL(3,4,6),cplcFeChiSeR(3,4,6),       & 
& cplcFeFeAhL(3,3,2),cplcFeFeAhR(3,3,2),cplcFeFehhL(3,3,2),cplcFeFehhR(3,3,2),           & 
& cplcFeFeVPL(3,3),cplcFeFeVPR(3,3),cplcFeFeVZL(3,3),cplcFeFeVZR(3,3),cplcFeFvHpmL(3,3,2),& 
& cplcFeFvHpmR(3,3,2),cplcFeFvVWmL(3,3),cplcFeFvVWmR(3,3),cplcFuChiSuL(3,4,6),           & 
& cplcFuChiSuR(3,4,6),cplcFuFdcHpmL(3,3,2),cplcFuFdcHpmR(3,3,2),cplcFuFdcVWmL(3,3),      & 
& cplcFuFdcVWmR(3,3),cplcFuFuAhL(3,3,2),cplcFuFuAhR(3,3,2),cplcFuFuhhL(3,3,2),           & 
& cplcFuFuhhR(3,3,2),cplcFuFuVGL(3,3),cplcFuFuVGR(3,3),cplcFuFuVPL(3,3),cplcFuFuVPR(3,3),& 
& cplcFuFuVZL(3,3),cplcFuFuVZR(3,3),cplcFuGluSuL(3,6),cplcFuGluSuR(3,6),cplcFvChiSvL(3,4,3),& 
& cplcFvChiSvR(3,4,3),cplcFvFecHpmL(3,3,2),cplcFvFecHpmR(3,3,2),cplcFvFecVWmL(3,3),      & 
& cplcFvFecVWmR(3,3),cplcFvFvVZL(3,3),cplcFvFvVZR(3,3),cplcgAgWmcVWm,cplcgWmgWmVZ,       & 
& cplcgWpCgAcVWm,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,cplcgZgWmcVWm,cplChaFucSdL(2,3,6),        & 
& cplChaFucSdR(2,3,6),cplChaFvcSeL(2,3,6),cplChaFvcSeR(2,3,6),cplChiChacHpmL(4,2,2),     & 
& cplChiChacHpmR(4,2,2),cplChiChacVWmL(4,2),cplChiChacVWmR(4,2),cplChiChiAhL(4,4,2),     & 
& cplChiChiAhR(4,4,2),cplChiChihhL(4,4,2),cplChiChihhR(4,4,2),cplChiChiVZL(4,4),         & 
& cplChiChiVZR(4,4),cplChiFdcSdL(4,3,6),cplChiFdcSdR(4,3,6),cplChiFecSeL(4,3,6),         & 
& cplChiFecSeR(4,3,6),cplChiFucSuL(4,3,6),cplChiFucSuR(4,3,6),cplChiFvcSvL(4,3,3),       & 
& cplChiFvcSvR(4,3,3),cplcHpmVPVWm(2),cplcHpmVWmVZ(2),cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,& 
& cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmVPVWm,       & 
& cplcVWmVWmVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplGluFdcSdL(3,6),        & 
& cplGluFdcSdR(3,6),cplGluFucSuL(3,6),cplGluFucSuR(3,6),cplGluGluVGL,cplGluGluVGR,       & 
& cplhhcHpmVWm(2,2),cplhhcVWmVWm(2),cplhhhhcVWmVWm(2,2),cplhhhhhh(2,2,2),cplhhhhVZVZ(2,2),& 
& cplhhHpmcHpm(2,2,2),cplhhHpmcVWm(2,2),cplhhSdcSd(2,6,6),cplhhSecSe(2,6,6),             & 
& cplhhSucSu(2,6,6),cplhhSvcSv(2,3,3),cplhhVZVZ(2),cplHpmcHpmcVWmVWm(2,2),               & 
& cplHpmcHpmVP(2,2),cplHpmcHpmVZ(2,2),cplHpmcHpmVZVZ(2,2),cplHpmcVWmVP(2),               & 
& cplHpmcVWmVZ(2),cplHpmSucSd(2,6,6),cplHpmSvcSe(2,3,6),cplSdcHpmcSu(6,2,6)

Complex(dp) :: cplSdcSdcVWmVWm(6,6),cplSdcSdVG(6,6),cplSdcSdVP(6,6),cplSdcSdVZ(6,6),cplSdcSdVZVZ(6,6),& 
& cplSdcSucVWm(6,6),cplSecHpmcSv(6,2,3),cplSecSecVWmVWm(6,6),cplSecSeVP(6,6),            & 
& cplSecSeVZ(6,6),cplSecSeVZVZ(6,6),cplSecSvcVWm(6,3),cplSucSdVWm(6,6),cplSucSucVWmVWm(6,6),& 
& cplSucSuVG(6,6),cplSucSuVP(6,6),cplSucSuVZ(6,6),cplSucSuVZVZ(6,6),cplSvcSeVWm(3,6),    & 
& cplSvcSvcVWmVWm(3,3),cplSvcSvVZ(3,3),cplSvcSvVZVZ(3,3),cplVGVGVG

Real(dp),Intent(out) :: ae,amu,atau,EDMe,EDMmu,EDMtau,dRho,BrBsGamma,ratioBsGamma,BrDmunu,ratioDmunu,         & 
& BrDsmunu,ratioDsmunu,BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,               & 
& ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM,muEgamma,tauEgamma,tauMuGamma,CRmuEAl,          & 
& CRmuETi,CRmuESr,CRmuESb,CRmuEAu,CRmuEPb,BRmuTo3e,BRtauTo3e,BRtauTo3mu,BRtauToemumu,    & 
& BRtauTomuee,BRtauToemumu2,BRtauTomuee2,BrZtoMuE,BrZtoTauE,BrZtoTauMu,BrhtoMuE,         & 
& BrhtoTauE,BrhtoTauMu,DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq,BrTautoEPi,         & 
& BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,BrTautoMuEtap,BrB0dEE,               & 
& ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,           & 
& BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,ratioB0sTauTau,BrBtoSEE,ratioBtoSEE,            & 
& BrBtoSMuMu,ratioBtoSMuMu,BrBtoKmumu,ratioBtoKmumu,BrBtoSnunu,ratioBtoSnunu,            & 
& BrBtoDnunu,ratioBtoDnunu,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,ratioKltoPinunu,  & 
& DelMK,ratioDelMK,epsK,ratioepsK

Complex(dp) :: c7,c7p,c8,c8p 
Real(dp) :: ResultMuE(6), ResultTauMeson(3), ResultTemp(99) 
Complex(dp), Dimension(3,3) :: Yu_save, Yd_save, Ye_save, CKMsave 
Real(dp) :: g1D(215), tz, dt 
Real(dp) ::Qin,vev2,sinw2, mzsave, scalein, scale_save, gSM(11),Qinsave, maxdiff =0._dp 
Integer :: i1, i2, i3, gt1, gt2, gt3, gt4,iQTEST, iQFinal 
Integer :: IndexArray4(99,4), IndexArray3(99,3), IndexArray2(99,2)   
Complex(dp) :: BOllddSLL(3,3,3,3),BOllddSRR(3,3,3,3),BOllddSRL(3,3,3,3),BOllddSLR(3,3,3,3),          & 
& BOllddVRR(3,3,3,3),BOllddVLL(3,3,3,3),BOllddVRL(3,3,3,3),BOllddVLR(3,3,3,3),           & 
& BOllddTLL(3,3,3,3),BOllddTLR(3,3,3,3),BOllddTRL(3,3,3,3),BOllddTRR(3,3,3,3),           & 
& PSOllddSLL(3,3,3,3),PSOllddSRR(3,3,3,3),PSOllddSRL(3,3,3,3),PSOllddSLR(3,3,3,3),       & 
& PSOllddVRR(3,3,3,3),PSOllddVLL(3,3,3,3),PSOllddVRL(3,3,3,3),PSOllddVLR(3,3,3,3),       & 
& PSOllddTLL(3,3,3,3),PSOllddTLR(3,3,3,3),PSOllddTRL(3,3,3,3),PSOllddTRR(3,3,3,3),       & 
& PVOllddSLL(3,3,3,3),PVOllddSRR(3,3,3,3),PVOllddSRL(3,3,3,3),PVOllddSLR(3,3,3,3),       & 
& PVOllddVRR(3,3,3,3),PVOllddVLL(3,3,3,3),PVOllddVRL(3,3,3,3),PVOllddVLR(3,3,3,3),       & 
& PVOllddTLL(3,3,3,3),PVOllddTLR(3,3,3,3),PVOllddTRL(3,3,3,3),PVOllddTRR(3,3,3,3),       & 
& TSOllddSLL(3,3,3,3),TSOllddSRR(3,3,3,3),TSOllddSRL(3,3,3,3),TSOllddSLR(3,3,3,3),       & 
& TSOllddVRR(3,3,3,3),TSOllddVLL(3,3,3,3),TSOllddVRL(3,3,3,3),TSOllddVLR(3,3,3,3),       & 
& TSOllddTLL(3,3,3,3),TSOllddTLR(3,3,3,3),TSOllddTRL(3,3,3,3),TSOllddTRR(3,3,3,3),       & 
& TVOllddSLL(3,3,3,3),TVOllddSRR(3,3,3,3),TVOllddSRL(3,3,3,3),TVOllddSLR(3,3,3,3),       & 
& TVOllddVRR(3,3,3,3),TVOllddVLL(3,3,3,3),TVOllddVRL(3,3,3,3),TVOllddVLR(3,3,3,3),       & 
& TVOllddTLL(3,3,3,3),TVOllddTLR(3,3,3,3),TVOllddTRL(3,3,3,3),TVOllddTRR(3,3,3,3),       & 
& BOlluuSLL(3,3,3,3),BOlluuSRR(3,3,3,3),BOlluuSRL(3,3,3,3),BOlluuSLR(3,3,3,3),           & 
& BOlluuVRR(3,3,3,3),BOlluuVLL(3,3,3,3),BOlluuVRL(3,3,3,3),BOlluuVLR(3,3,3,3),           & 
& BOlluuTLL(3,3,3,3),BOlluuTLR(3,3,3,3),BOlluuTRL(3,3,3,3),BOlluuTRR(3,3,3,3),           & 
& PSOlluuSLL(3,3,3,3),PSOlluuSRR(3,3,3,3),PSOlluuSRL(3,3,3,3),PSOlluuSLR(3,3,3,3),       & 
& PSOlluuVRR(3,3,3,3),PSOlluuVLL(3,3,3,3),PSOlluuVRL(3,3,3,3),PSOlluuVLR(3,3,3,3),       & 
& PSOlluuTLL(3,3,3,3),PSOlluuTLR(3,3,3,3),PSOlluuTRL(3,3,3,3),PSOlluuTRR(3,3,3,3),       & 
& PVOlluuSLL(3,3,3,3),PVOlluuSRR(3,3,3,3),PVOlluuSRL(3,3,3,3),PVOlluuSLR(3,3,3,3),       & 
& PVOlluuVRR(3,3,3,3),PVOlluuVLL(3,3,3,3),PVOlluuVRL(3,3,3,3),PVOlluuVLR(3,3,3,3),       & 
& PVOlluuTLL(3,3,3,3),PVOlluuTLR(3,3,3,3),PVOlluuTRL(3,3,3,3),PVOlluuTRR(3,3,3,3),       & 
& TSOlluuSLL(3,3,3,3),TSOlluuSRR(3,3,3,3),TSOlluuSRL(3,3,3,3),TSOlluuSLR(3,3,3,3),       & 
& TSOlluuVRR(3,3,3,3),TSOlluuVLL(3,3,3,3),TSOlluuVRL(3,3,3,3),TSOlluuVLR(3,3,3,3),       & 
& TSOlluuTLL(3,3,3,3),TSOlluuTLR(3,3,3,3),TSOlluuTRL(3,3,3,3),TSOlluuTRR(3,3,3,3),       & 
& TVOlluuSLL(3,3,3,3),TVOlluuSRR(3,3,3,3),TVOlluuSRL(3,3,3,3),TVOlluuSLR(3,3,3,3),       & 
& TVOlluuVRR(3,3,3,3),TVOlluuVLL(3,3,3,3),TVOlluuVRL(3,3,3,3),TVOlluuVLR(3,3,3,3),       & 
& TVOlluuTLL(3,3,3,3),TVOlluuTLR(3,3,3,3),TVOlluuTRL(3,3,3,3),TVOlluuTRR(3,3,3,3),       & 
& BO4lSLL(3,3,3,3),BO4lSRR(3,3,3,3),BO4lSRL(3,3,3,3),BO4lSLR(3,3,3,3),BO4lVRR(3,3,3,3),  & 
& BO4lVLL(3,3,3,3),BO4lVRL(3,3,3,3),BO4lVLR(3,3,3,3),BO4lTLL(3,3,3,3),BO4lTLR(3,3,3,3),  & 
& BO4lTRL(3,3,3,3),BO4lTRR(3,3,3,3),PSO4lSLL(3,3,3,3),PSO4lSRR(3,3,3,3),PSO4lSRL(3,3,3,3),& 
& PSO4lSLR(3,3,3,3),PSO4lVRR(3,3,3,3),PSO4lVLL(3,3,3,3),PSO4lVRL(3,3,3,3),               & 
& PSO4lVLR(3,3,3,3),PSO4lTLL(3,3,3,3),PSO4lTLR(3,3,3,3),PSO4lTRL(3,3,3,3),               & 
& PSO4lTRR(3,3,3,3),PVO4lSLL(3,3,3,3),PVO4lSRR(3,3,3,3),PVO4lSRL(3,3,3,3),               & 
& PVO4lSLR(3,3,3,3),PVO4lVRR(3,3,3,3),PVO4lVLL(3,3,3,3),PVO4lVRL(3,3,3,3)

Complex(dp) :: PVO4lVLR(3,3,3,3),PVO4lTLL(3,3,3,3),PVO4lTLR(3,3,3,3),PVO4lTRL(3,3,3,3),               & 
& PVO4lTRR(3,3,3,3),TSO4lSLL(3,3,3,3),TSO4lSRR(3,3,3,3),TSO4lSRL(3,3,3,3),               & 
& TSO4lSLR(3,3,3,3),TSO4lVRR(3,3,3,3),TSO4lVLL(3,3,3,3),TSO4lVRL(3,3,3,3),               & 
& TSO4lVLR(3,3,3,3),TSO4lTLL(3,3,3,3),TSO4lTLR(3,3,3,3),TSO4lTRL(3,3,3,3),               & 
& TSO4lTRR(3,3,3,3),TVO4lSLL(3,3,3,3),TVO4lSRR(3,3,3,3),TVO4lSRL(3,3,3,3),               & 
& TVO4lSLR(3,3,3,3),TVO4lVRR(3,3,3,3),TVO4lVLL(3,3,3,3),TVO4lVRL(3,3,3,3),               & 
& TVO4lVLR(3,3,3,3),TVO4lTLL(3,3,3,3),TVO4lTLR(3,3,3,3),TVO4lTRL(3,3,3,3),               & 
& TVO4lTRR(3,3,3,3),BO4lSLLcross(3,3,3,3),BO4lSRRcross(3,3,3,3),BO4lSRLcross(3,3,3,3),   & 
& BO4lSLRcross(3,3,3,3),BO4lVRRcross(3,3,3,3),BO4lVLLcross(3,3,3,3),BO4lVRLcross(3,3,3,3),& 
& BO4lVLRcross(3,3,3,3),BO4lTLLcross(3,3,3,3),BO4lTLRcross(3,3,3,3),BO4lTRLcross(3,3,3,3),& 
& BO4lTRRcross(3,3,3,3),PSO4lSLLcross(3,3,3,3),PSO4lSRRcross(3,3,3,3),PSO4lSRLcross(3,3,3,3),& 
& PSO4lSLRcross(3,3,3,3),PSO4lVRRcross(3,3,3,3),PSO4lVLLcross(3,3,3,3),PSO4lVRLcross(3,3,3,3),& 
& PSO4lVLRcross(3,3,3,3),PSO4lTLLcross(3,3,3,3),PSO4lTLRcross(3,3,3,3),PSO4lTRLcross(3,3,3,3),& 
& PSO4lTRRcross(3,3,3,3),PVO4lSLLcross(3,3,3,3),PVO4lSRRcross(3,3,3,3),PVO4lSRLcross(3,3,3,3),& 
& PVO4lSLRcross(3,3,3,3),PVO4lVRRcross(3,3,3,3),PVO4lVLLcross(3,3,3,3),PVO4lVRLcross(3,3,3,3),& 
& PVO4lVLRcross(3,3,3,3),PVO4lTLLcross(3,3,3,3),PVO4lTLRcross(3,3,3,3),PVO4lTRLcross(3,3,3,3),& 
& PVO4lTRRcross(3,3,3,3),TSO4lSLLcross(3,3,3,3),TSO4lSRRcross(3,3,3,3),TSO4lSRLcross(3,3,3,3),& 
& TSO4lSLRcross(3,3,3,3),TSO4lVRRcross(3,3,3,3),TSO4lVLLcross(3,3,3,3),TSO4lVRLcross(3,3,3,3),& 
& TSO4lVLRcross(3,3,3,3),TSO4lTLLcross(3,3,3,3),TSO4lTLRcross(3,3,3,3),TSO4lTRLcross(3,3,3,3),& 
& TSO4lTRRcross(3,3,3,3),TVO4lSLLcross(3,3,3,3),TVO4lSRRcross(3,3,3,3),TVO4lSRLcross(3,3,3,3),& 
& TVO4lSLRcross(3,3,3,3),TVO4lVRRcross(3,3,3,3),TVO4lVLLcross(3,3,3,3),TVO4lVRLcross(3,3,3,3),& 
& TVO4lVLRcross(3,3,3,3),TVO4lTLLcross(3,3,3,3),TVO4lTLRcross(3,3,3,3),TVO4lTRLcross(3,3,3,3),& 
& TVO4lTRRcross(3,3,3,3),OA2lSL(3,3),OA2lSR(3,3),OA1L(3,3),OA1R(3,3),OH2lSL(3,3,2),      & 
& OH2lSR(3,3,2),OZ2lSL(3,3),OZ2lSR(3,3),OZ2lVL(3,3),OZ2lVR(3,3)

Complex(dp) :: BOddllSLLSM(3,3,3,3),BOddllSRRSM(3,3,3,3),BOddllSRLSM(3,3,3,3),BOddllSLRSM(3,3,3,3),  & 
& BOddllVRRSM(3,3,3,3),BOddllVLLSM(3,3,3,3),BOddllVRLSM(3,3,3,3),BOddllVLRSM(3,3,3,3),   & 
& BOddllTLLSM(3,3,3,3),BOddllTLRSM(3,3,3,3),BOddllTRLSM(3,3,3,3),BOddllTRRSM(3,3,3,3),   & 
& PSOddllSLLSM(3,3,3,3),PSOddllSRRSM(3,3,3,3),PSOddllSRLSM(3,3,3,3),PSOddllSLRSM(3,3,3,3),& 
& PSOddllVRRSM(3,3,3,3),PSOddllVLLSM(3,3,3,3),PSOddllVRLSM(3,3,3,3),PSOddllVLRSM(3,3,3,3),& 
& PSOddllTLLSM(3,3,3,3),PSOddllTLRSM(3,3,3,3),PSOddllTRLSM(3,3,3,3),PSOddllTRRSM(3,3,3,3),& 
& PVOddllSLLSM(3,3,3,3),PVOddllSRRSM(3,3,3,3),PVOddllSRLSM(3,3,3,3),PVOddllSLRSM(3,3,3,3),& 
& PVOddllVRRSM(3,3,3,3),PVOddllVLLSM(3,3,3,3),PVOddllVRLSM(3,3,3,3),PVOddllVLRSM(3,3,3,3),& 
& PVOddllTLLSM(3,3,3,3),PVOddllTLRSM(3,3,3,3),PVOddllTRLSM(3,3,3,3),PVOddllTRRSM(3,3,3,3),& 
& TSOddllSLLSM(3,3,3,3),TSOddllSRRSM(3,3,3,3),TSOddllSRLSM(3,3,3,3),TSOddllSLRSM(3,3,3,3),& 
& TSOddllVRRSM(3,3,3,3),TSOddllVLLSM(3,3,3,3),TSOddllVRLSM(3,3,3,3),TSOddllVLRSM(3,3,3,3),& 
& TSOddllTLLSM(3,3,3,3),TSOddllTLRSM(3,3,3,3),TSOddllTRLSM(3,3,3,3),TSOddllTRRSM(3,3,3,3),& 
& TVOddllSLLSM(3,3,3,3),TVOddllSRRSM(3,3,3,3),TVOddllSRLSM(3,3,3,3),TVOddllSLRSM(3,3,3,3),& 
& TVOddllVRRSM(3,3,3,3),TVOddllVLLSM(3,3,3,3),TVOddllVRLSM(3,3,3,3),TVOddllVLRSM(3,3,3,3),& 
& TVOddllTLLSM(3,3,3,3),TVOddllTLRSM(3,3,3,3),TVOddllTRLSM(3,3,3,3),TVOddllTRRSM(3,3,3,3),& 
& BOddvvVRRSM(3,3,3,3),BOddvvVLLSM(3,3,3,3),BOddvvVRLSM(3,3,3,3),BOddvvVLRSM(3,3,3,3),   & 
& PSOddvvVRRSM(3,3,3,3),PSOddvvVLLSM(3,3,3,3),PSOddvvVRLSM(3,3,3,3),PSOddvvVLRSM(3,3,3,3),& 
& PVOddvvVRRSM(3,3,3,3),PVOddvvVLLSM(3,3,3,3),PVOddvvVRLSM(3,3,3,3),PVOddvvVLRSM(3,3,3,3),& 
& TSOddvvVRRSM(3,3,3,3),TSOddvvVLLSM(3,3,3,3),TSOddvvVRLSM(3,3,3,3),TSOddvvVLRSM(3,3,3,3),& 
& TVOddvvVRRSM(3,3,3,3),TVOddvvVLLSM(3,3,3,3),TVOddvvVRLSM(3,3,3,3),TVOddvvVLRSM(3,3,3,3),& 
& BO4dSLLSM(3,3,3,3),BO4dSRRSM(3,3,3,3),BO4dSRLSM(3,3,3,3),BO4dSLRSM(3,3,3,3),           & 
& BO4dVRRSM(3,3,3,3),BO4dVLLSM(3,3,3,3),BO4dVRLSM(3,3,3,3),BO4dVLRSM(3,3,3,3),           & 
& BO4dTLLSM(3,3,3,3),BO4dTLRSM(3,3,3,3),BO4dTRLSM(3,3,3,3),BO4dTRRSM(3,3,3,3),           & 
& TSO4dSLLSM(3,3,3,3),TSO4dSRRSM(3,3,3,3),TSO4dSRLSM(3,3,3,3),TSO4dSLRSM(3,3,3,3),       & 
& TSO4dVRRSM(3,3,3,3),TSO4dVLLSM(3,3,3,3),TSO4dVRLSM(3,3,3,3),TSO4dVLRSM(3,3,3,3),       & 
& TSO4dTLLSM(3,3,3,3),TSO4dTLRSM(3,3,3,3),TSO4dTRLSM(3,3,3,3),TSO4dTRRSM(3,3,3,3),       & 
& TVO4dSLLSM(3,3,3,3),TVO4dSRRSM(3,3,3,3),TVO4dSRLSM(3,3,3,3),TVO4dSLRSM(3,3,3,3),       & 
& TVO4dVRRSM(3,3,3,3),TVO4dVLLSM(3,3,3,3),TVO4dVRLSM(3,3,3,3),TVO4dVLRSM(3,3,3,3),       & 
& TVO4dTLLSM(3,3,3,3),TVO4dTLRSM(3,3,3,3),TVO4dTRLSM(3,3,3,3),TVO4dTRRSM(3,3,3,3),       & 
& OAh2qSLSM(3,3,2),OAh2qSRSM(3,3,2),TSOdulvSLLSM(3,3,3,3),TSOdulvSRRSM(3,3,3,3),         & 
& TSOdulvSRLSM(3,3,3,3),TSOdulvSLRSM(3,3,3,3),TSOdulvVRRSM(3,3,3,3),TSOdulvVLLSM(3,3,3,3),& 
& TSOdulvVRLSM(3,3,3,3),TSOdulvVLRSM(3,3,3,3),TVOdulvSLLSM(3,3,3,3),TVOdulvSRRSM(3,3,3,3),& 
& TVOdulvSRLSM(3,3,3,3),TVOdulvSLRSM(3,3,3,3),TVOdulvVRRSM(3,3,3,3),TVOdulvVLLSM(3,3,3,3),& 
& TVOdulvVRLSM(3,3,3,3),TVOdulvVLRSM(3,3,3,3),OA2qSLSM(3,3),OA2qSRSM(3,3),               & 
& OA2qVLSM(3,3),OA2qVRSM(3,3),OG2qSLSM(3,3),OG2qSRSM(3,3),OH2qSLSM(3,3,2),               & 
& OH2qSRSM(3,3,2)

Complex(dp) :: BOddllSLL(3,3,3,3),BOddllSRR(3,3,3,3),BOddllSRL(3,3,3,3),BOddllSLR(3,3,3,3),          & 
& BOddllVRR(3,3,3,3),BOddllVLL(3,3,3,3),BOddllVRL(3,3,3,3),BOddllVLR(3,3,3,3),           & 
& BOddllTLL(3,3,3,3),BOddllTLR(3,3,3,3),BOddllTRL(3,3,3,3),BOddllTRR(3,3,3,3),           & 
& PSOddllSLL(3,3,3,3),PSOddllSRR(3,3,3,3),PSOddllSRL(3,3,3,3),PSOddllSLR(3,3,3,3),       & 
& PSOddllVRR(3,3,3,3),PSOddllVLL(3,3,3,3),PSOddllVRL(3,3,3,3),PSOddllVLR(3,3,3,3),       & 
& PSOddllTLL(3,3,3,3),PSOddllTLR(3,3,3,3),PSOddllTRL(3,3,3,3),PSOddllTRR(3,3,3,3),       & 
& PVOddllSLL(3,3,3,3),PVOddllSRR(3,3,3,3),PVOddllSRL(3,3,3,3),PVOddllSLR(3,3,3,3),       & 
& PVOddllVRR(3,3,3,3),PVOddllVLL(3,3,3,3),PVOddllVRL(3,3,3,3),PVOddllVLR(3,3,3,3),       & 
& PVOddllTLL(3,3,3,3),PVOddllTLR(3,3,3,3),PVOddllTRL(3,3,3,3),PVOddllTRR(3,3,3,3),       & 
& TSOddllSLL(3,3,3,3),TSOddllSRR(3,3,3,3),TSOddllSRL(3,3,3,3),TSOddllSLR(3,3,3,3),       & 
& TSOddllVRR(3,3,3,3),TSOddllVLL(3,3,3,3),TSOddllVRL(3,3,3,3),TSOddllVLR(3,3,3,3),       & 
& TSOddllTLL(3,3,3,3),TSOddllTLR(3,3,3,3),TSOddllTRL(3,3,3,3),TSOddllTRR(3,3,3,3),       & 
& TVOddllSLL(3,3,3,3),TVOddllSRR(3,3,3,3),TVOddllSRL(3,3,3,3),TVOddllSLR(3,3,3,3),       & 
& TVOddllVRR(3,3,3,3),TVOddllVLL(3,3,3,3),TVOddllVRL(3,3,3,3),TVOddllVLR(3,3,3,3),       & 
& TVOddllTLL(3,3,3,3),TVOddllTLR(3,3,3,3),TVOddllTRL(3,3,3,3),TVOddllTRR(3,3,3,3),       & 
& BOddvvVRR(3,3,3,3),BOddvvVLL(3,3,3,3),BOddvvVRL(3,3,3,3),BOddvvVLR(3,3,3,3),           & 
& PSOddvvVRR(3,3,3,3),PSOddvvVLL(3,3,3,3),PSOddvvVRL(3,3,3,3),PSOddvvVLR(3,3,3,3),       & 
& PVOddvvVRR(3,3,3,3),PVOddvvVLL(3,3,3,3),PVOddvvVRL(3,3,3,3),PVOddvvVLR(3,3,3,3),       & 
& TSOddvvVRR(3,3,3,3),TSOddvvVLL(3,3,3,3),TSOddvvVRL(3,3,3,3),TSOddvvVLR(3,3,3,3),       & 
& TVOddvvVRR(3,3,3,3),TVOddvvVLL(3,3,3,3),TVOddvvVRL(3,3,3,3),TVOddvvVLR(3,3,3,3),       & 
& BO4dSLL(3,3,3,3),BO4dSRR(3,3,3,3),BO4dSRL(3,3,3,3),BO4dSLR(3,3,3,3),BO4dVRR(3,3,3,3),  & 
& BO4dVLL(3,3,3,3),BO4dVRL(3,3,3,3),BO4dVLR(3,3,3,3),BO4dTLL(3,3,3,3),BO4dTLR(3,3,3,3),  & 
& BO4dTRL(3,3,3,3),BO4dTRR(3,3,3,3),TSO4dSLL(3,3,3,3),TSO4dSRR(3,3,3,3),TSO4dSRL(3,3,3,3),& 
& TSO4dSLR(3,3,3,3),TSO4dVRR(3,3,3,3),TSO4dVLL(3,3,3,3),TSO4dVRL(3,3,3,3),               & 
& TSO4dVLR(3,3,3,3),TSO4dTLL(3,3,3,3),TSO4dTLR(3,3,3,3),TSO4dTRL(3,3,3,3),               & 
& TSO4dTRR(3,3,3,3),TVO4dSLL(3,3,3,3),TVO4dSRR(3,3,3,3),TVO4dSRL(3,3,3,3),               & 
& TVO4dSLR(3,3,3,3),TVO4dVRR(3,3,3,3),TVO4dVLL(3,3,3,3),TVO4dVRL(3,3,3,3),               & 
& TVO4dVLR(3,3,3,3),TVO4dTLL(3,3,3,3),TVO4dTLR(3,3,3,3),TVO4dTRL(3,3,3,3),               & 
& TVO4dTRR(3,3,3,3),OAh2qSL(3,3,2),OAh2qSR(3,3,2),TSOdulvSLL(3,3,3,3),TSOdulvSRR(3,3,3,3),& 
& TSOdulvSRL(3,3,3,3),TSOdulvSLR(3,3,3,3),TSOdulvVRR(3,3,3,3),TSOdulvVLL(3,3,3,3),       & 
& TSOdulvVRL(3,3,3,3),TSOdulvVLR(3,3,3,3),TVOdulvSLL(3,3,3,3),TVOdulvSRR(3,3,3,3),       & 
& TVOdulvSRL(3,3,3,3),TVOdulvSLR(3,3,3,3),TVOdulvVRR(3,3,3,3),TVOdulvVLL(3,3,3,3),       & 
& TVOdulvVRL(3,3,3,3),TVOdulvVLR(3,3,3,3),OA2qSL(3,3),OA2qSR(3,3),OA2qVL(3,3),           & 
& OA2qVR(3,3),OG2qSL(3,3),OG2qSR(3,3),OH2qSL(3,3,2),OH2qSR(3,3,2)

Complex(dp) :: BOllddSLLcheck(3,3,3,3),BOllddSRRcheck(3,3,3,3),BOllddSRLcheck(3,3,3,3),              & 
& BOllddSLRcheck(3,3,3,3),BOllddVRRcheck(3,3,3,3),BOllddVLLcheck(3,3,3,3),               & 
& BOllddVRLcheck(3,3,3,3),BOllddVLRcheck(3,3,3,3),BOllddTLLcheck(3,3,3,3),               & 
& BOllddTLRcheck(3,3,3,3),BOllddTRLcheck(3,3,3,3),BOllddTRRcheck(3,3,3,3),               & 
& PSOllddSLLcheck(3,3,3,3),PSOllddSRRcheck(3,3,3,3),PSOllddSRLcheck(3,3,3,3),            & 
& PSOllddSLRcheck(3,3,3,3),PSOllddVRRcheck(3,3,3,3),PSOllddVLLcheck(3,3,3,3),            & 
& PSOllddVRLcheck(3,3,3,3),PSOllddVLRcheck(3,3,3,3),PSOllddTLLcheck(3,3,3,3),            & 
& PSOllddTLRcheck(3,3,3,3),PSOllddTRLcheck(3,3,3,3),PSOllddTRRcheck(3,3,3,3),            & 
& PVOllddSLLcheck(3,3,3,3),PVOllddSRRcheck(3,3,3,3),PVOllddSRLcheck(3,3,3,3),            & 
& PVOllddSLRcheck(3,3,3,3),PVOllddVRRcheck(3,3,3,3),PVOllddVLLcheck(3,3,3,3),            & 
& PVOllddVRLcheck(3,3,3,3),PVOllddVLRcheck(3,3,3,3),PVOllddTLLcheck(3,3,3,3),            & 
& PVOllddTLRcheck(3,3,3,3),PVOllddTRLcheck(3,3,3,3),PVOllddTRRcheck(3,3,3,3),            & 
& TSOllddSLLcheck(3,3,3,3),TSOllddSRRcheck(3,3,3,3),TSOllddSRLcheck(3,3,3,3),            & 
& TSOllddSLRcheck(3,3,3,3),TSOllddVRRcheck(3,3,3,3),TSOllddVLLcheck(3,3,3,3),            & 
& TSOllddVRLcheck(3,3,3,3),TSOllddVLRcheck(3,3,3,3),TSOllddTLLcheck(3,3,3,3),            & 
& TSOllddTLRcheck(3,3,3,3),TSOllddTRLcheck(3,3,3,3),TSOllddTRRcheck(3,3,3,3),            & 
& TVOllddSLLcheck(3,3,3,3),TVOllddSRRcheck(3,3,3,3),TVOllddSRLcheck(3,3,3,3),            & 
& TVOllddSLRcheck(3,3,3,3),TVOllddVRRcheck(3,3,3,3),TVOllddVLLcheck(3,3,3,3),            & 
& TVOllddVRLcheck(3,3,3,3),TVOllddVLRcheck(3,3,3,3),TVOllddTLLcheck(3,3,3,3),            & 
& TVOllddTLRcheck(3,3,3,3),TVOllddTRLcheck(3,3,3,3),TVOllddTRRcheck(3,3,3,3),            & 
& BOlluuSLLcheck(3,3,3,3),BOlluuSRRcheck(3,3,3,3),BOlluuSRLcheck(3,3,3,3),               & 
& BOlluuSLRcheck(3,3,3,3),BOlluuVRRcheck(3,3,3,3),BOlluuVLLcheck(3,3,3,3),               & 
& BOlluuVRLcheck(3,3,3,3),BOlluuVLRcheck(3,3,3,3),BOlluuTLLcheck(3,3,3,3),               & 
& BOlluuTLRcheck(3,3,3,3),BOlluuTRLcheck(3,3,3,3),BOlluuTRRcheck(3,3,3,3),               & 
& PSOlluuSLLcheck(3,3,3,3),PSOlluuSRRcheck(3,3,3,3),PSOlluuSRLcheck(3,3,3,3),            & 
& PSOlluuSLRcheck(3,3,3,3),PSOlluuVRRcheck(3,3,3,3),PSOlluuVLLcheck(3,3,3,3),            & 
& PSOlluuVRLcheck(3,3,3,3),PSOlluuVLRcheck(3,3,3,3),PSOlluuTLLcheck(3,3,3,3),            & 
& PSOlluuTLRcheck(3,3,3,3),PSOlluuTRLcheck(3,3,3,3),PSOlluuTRRcheck(3,3,3,3),            & 
& PVOlluuSLLcheck(3,3,3,3),PVOlluuSRRcheck(3,3,3,3),PVOlluuSRLcheck(3,3,3,3),            & 
& PVOlluuSLRcheck(3,3,3,3),PVOlluuVRRcheck(3,3,3,3),PVOlluuVLLcheck(3,3,3,3),            & 
& PVOlluuVRLcheck(3,3,3,3),PVOlluuVLRcheck(3,3,3,3),PVOlluuTLLcheck(3,3,3,3),            & 
& PVOlluuTLRcheck(3,3,3,3),PVOlluuTRLcheck(3,3,3,3),PVOlluuTRRcheck(3,3,3,3),            & 
& TSOlluuSLLcheck(3,3,3,3),TSOlluuSRRcheck(3,3,3,3),TSOlluuSRLcheck(3,3,3,3),            & 
& TSOlluuSLRcheck(3,3,3,3),TSOlluuVRRcheck(3,3,3,3),TSOlluuVLLcheck(3,3,3,3),            & 
& TSOlluuVRLcheck(3,3,3,3),TSOlluuVLRcheck(3,3,3,3),TSOlluuTLLcheck(3,3,3,3),            & 
& TSOlluuTLRcheck(3,3,3,3),TSOlluuTRLcheck(3,3,3,3),TSOlluuTRRcheck(3,3,3,3),            & 
& TVOlluuSLLcheck(3,3,3,3),TVOlluuSRRcheck(3,3,3,3),TVOlluuSRLcheck(3,3,3,3)

Complex(dp) :: TVOlluuSLRcheck(3,3,3,3),TVOlluuVRRcheck(3,3,3,3),TVOlluuVLLcheck(3,3,3,3),            & 
& TVOlluuVRLcheck(3,3,3,3),TVOlluuVLRcheck(3,3,3,3),TVOlluuTLLcheck(3,3,3,3),            & 
& TVOlluuTLRcheck(3,3,3,3),TVOlluuTRLcheck(3,3,3,3),TVOlluuTRRcheck(3,3,3,3),            & 
& BO4lSLLcheck(3,3,3,3),BO4lSRRcheck(3,3,3,3),BO4lSRLcheck(3,3,3,3),BO4lSLRcheck(3,3,3,3),& 
& BO4lVRRcheck(3,3,3,3),BO4lVLLcheck(3,3,3,3),BO4lVRLcheck(3,3,3,3),BO4lVLRcheck(3,3,3,3),& 
& BO4lTLLcheck(3,3,3,3),BO4lTLRcheck(3,3,3,3),BO4lTRLcheck(3,3,3,3),BO4lTRRcheck(3,3,3,3),& 
& PSO4lSLLcheck(3,3,3,3),PSO4lSRRcheck(3,3,3,3),PSO4lSRLcheck(3,3,3,3),PSO4lSLRcheck(3,3,3,3),& 
& PSO4lVRRcheck(3,3,3,3),PSO4lVLLcheck(3,3,3,3),PSO4lVRLcheck(3,3,3,3),PSO4lVLRcheck(3,3,3,3),& 
& PSO4lTLLcheck(3,3,3,3),PSO4lTLRcheck(3,3,3,3),PSO4lTRLcheck(3,3,3,3),PSO4lTRRcheck(3,3,3,3),& 
& PVO4lSLLcheck(3,3,3,3),PVO4lSRRcheck(3,3,3,3),PVO4lSRLcheck(3,3,3,3),PVO4lSLRcheck(3,3,3,3),& 
& PVO4lVRRcheck(3,3,3,3),PVO4lVLLcheck(3,3,3,3),PVO4lVRLcheck(3,3,3,3),PVO4lVLRcheck(3,3,3,3),& 
& PVO4lTLLcheck(3,3,3,3),PVO4lTLRcheck(3,3,3,3),PVO4lTRLcheck(3,3,3,3),PVO4lTRRcheck(3,3,3,3),& 
& TSO4lSLLcheck(3,3,3,3),TSO4lSRRcheck(3,3,3,3),TSO4lSRLcheck(3,3,3,3),TSO4lSLRcheck(3,3,3,3),& 
& TSO4lVRRcheck(3,3,3,3),TSO4lVLLcheck(3,3,3,3),TSO4lVRLcheck(3,3,3,3),TSO4lVLRcheck(3,3,3,3),& 
& TSO4lTLLcheck(3,3,3,3),TSO4lTLRcheck(3,3,3,3),TSO4lTRLcheck(3,3,3,3),TSO4lTRRcheck(3,3,3,3),& 
& TVO4lSLLcheck(3,3,3,3),TVO4lSRRcheck(3,3,3,3),TVO4lSRLcheck(3,3,3,3),TVO4lSLRcheck(3,3,3,3),& 
& TVO4lVRRcheck(3,3,3,3),TVO4lVLLcheck(3,3,3,3),TVO4lVRLcheck(3,3,3,3),TVO4lVLRcheck(3,3,3,3),& 
& TVO4lTLLcheck(3,3,3,3),TVO4lTLRcheck(3,3,3,3),TVO4lTRLcheck(3,3,3,3),TVO4lTRRcheck(3,3,3,3),& 
& BO4lSLLcrosscheck(3,3,3,3),BO4lSRRcrosscheck(3,3,3,3),BO4lSRLcrosscheck(3,3,3,3),      & 
& BO4lSLRcrosscheck(3,3,3,3),BO4lVRRcrosscheck(3,3,3,3),BO4lVLLcrosscheck(3,3,3,3),      & 
& BO4lVRLcrosscheck(3,3,3,3),BO4lVLRcrosscheck(3,3,3,3),BO4lTLLcrosscheck(3,3,3,3),      & 
& BO4lTLRcrosscheck(3,3,3,3),BO4lTRLcrosscheck(3,3,3,3),BO4lTRRcrosscheck(3,3,3,3),      & 
& PSO4lSLLcrosscheck(3,3,3,3),PSO4lSRRcrosscheck(3,3,3,3),PSO4lSRLcrosscheck(3,3,3,3),   & 
& PSO4lSLRcrosscheck(3,3,3,3),PSO4lVRRcrosscheck(3,3,3,3),PSO4lVLLcrosscheck(3,3,3,3),   & 
& PSO4lVRLcrosscheck(3,3,3,3),PSO4lVLRcrosscheck(3,3,3,3),PSO4lTLLcrosscheck(3,3,3,3),   & 
& PSO4lTLRcrosscheck(3,3,3,3),PSO4lTRLcrosscheck(3,3,3,3),PSO4lTRRcrosscheck(3,3,3,3),   & 
& PVO4lSLLcrosscheck(3,3,3,3),PVO4lSRRcrosscheck(3,3,3,3),PVO4lSRLcrosscheck(3,3,3,3),   & 
& PVO4lSLRcrosscheck(3,3,3,3),PVO4lVRRcrosscheck(3,3,3,3),PVO4lVLLcrosscheck(3,3,3,3),   & 
& PVO4lVRLcrosscheck(3,3,3,3),PVO4lVLRcrosscheck(3,3,3,3),PVO4lTLLcrosscheck(3,3,3,3),   & 
& PVO4lTLRcrosscheck(3,3,3,3),PVO4lTRLcrosscheck(3,3,3,3),PVO4lTRRcrosscheck(3,3,3,3),   & 
& TSO4lSLLcrosscheck(3,3,3,3),TSO4lSRRcrosscheck(3,3,3,3),TSO4lSRLcrosscheck(3,3,3,3),   & 
& TSO4lSLRcrosscheck(3,3,3,3),TSO4lVRRcrosscheck(3,3,3,3),TSO4lVLLcrosscheck(3,3,3,3),   & 
& TSO4lVRLcrosscheck(3,3,3,3),TSO4lVLRcrosscheck(3,3,3,3),TSO4lTLLcrosscheck(3,3,3,3),   & 
& TSO4lTLRcrosscheck(3,3,3,3),TSO4lTRLcrosscheck(3,3,3,3),TSO4lTRRcrosscheck(3,3,3,3),   & 
& TVO4lSLLcrosscheck(3,3,3,3),TVO4lSRRcrosscheck(3,3,3,3),TVO4lSRLcrosscheck(3,3,3,3),   & 
& TVO4lSLRcrosscheck(3,3,3,3),TVO4lVRRcrosscheck(3,3,3,3),TVO4lVLLcrosscheck(3,3,3,3),   & 
& TVO4lVRLcrosscheck(3,3,3,3),TVO4lVLRcrosscheck(3,3,3,3),TVO4lTLLcrosscheck(3,3,3,3)

Complex(dp) :: TVO4lTLRcrosscheck(3,3,3,3),TVO4lTRLcrosscheck(3,3,3,3),TVO4lTRRcrosscheck(3,3,3,3),   & 
& OA2lSLcheck(3,3),OA2lSRcheck(3,3),OA1Lcheck(3,3),OA1Rcheck(3,3),OH2lSLcheck(3,3,2),    & 
& OH2lSRcheck(3,3,2),OZ2lSLcheck(3,3),OZ2lSRcheck(3,3),OZ2lVLcheck(3,3),OZ2lVRcheck(3,3)

Complex(dp) :: BOddllSLLcheck(3,3,3,3),BOddllSRRcheck(3,3,3,3),BOddllSRLcheck(3,3,3,3),              & 
& BOddllSLRcheck(3,3,3,3),BOddllVRRcheck(3,3,3,3),BOddllVLLcheck(3,3,3,3),               & 
& BOddllVRLcheck(3,3,3,3),BOddllVLRcheck(3,3,3,3),BOddllTLLcheck(3,3,3,3),               & 
& BOddllTLRcheck(3,3,3,3),BOddllTRLcheck(3,3,3,3),BOddllTRRcheck(3,3,3,3),               & 
& PSOddllSLLcheck(3,3,3,3),PSOddllSRRcheck(3,3,3,3),PSOddllSRLcheck(3,3,3,3),            & 
& PSOddllSLRcheck(3,3,3,3),PSOddllVRRcheck(3,3,3,3),PSOddllVLLcheck(3,3,3,3),            & 
& PSOddllVRLcheck(3,3,3,3),PSOddllVLRcheck(3,3,3,3),PSOddllTLLcheck(3,3,3,3),            & 
& PSOddllTLRcheck(3,3,3,3),PSOddllTRLcheck(3,3,3,3),PSOddllTRRcheck(3,3,3,3),            & 
& PVOddllSLLcheck(3,3,3,3),PVOddllSRRcheck(3,3,3,3),PVOddllSRLcheck(3,3,3,3),            & 
& PVOddllSLRcheck(3,3,3,3),PVOddllVRRcheck(3,3,3,3),PVOddllVLLcheck(3,3,3,3),            & 
& PVOddllVRLcheck(3,3,3,3),PVOddllVLRcheck(3,3,3,3),PVOddllTLLcheck(3,3,3,3),            & 
& PVOddllTLRcheck(3,3,3,3),PVOddllTRLcheck(3,3,3,3),PVOddllTRRcheck(3,3,3,3),            & 
& TSOddllSLLcheck(3,3,3,3),TSOddllSRRcheck(3,3,3,3),TSOddllSRLcheck(3,3,3,3),            & 
& TSOddllSLRcheck(3,3,3,3),TSOddllVRRcheck(3,3,3,3),TSOddllVLLcheck(3,3,3,3),            & 
& TSOddllVRLcheck(3,3,3,3),TSOddllVLRcheck(3,3,3,3),TSOddllTLLcheck(3,3,3,3),            & 
& TSOddllTLRcheck(3,3,3,3),TSOddllTRLcheck(3,3,3,3),TSOddllTRRcheck(3,3,3,3),            & 
& TVOddllSLLcheck(3,3,3,3),TVOddllSRRcheck(3,3,3,3),TVOddllSRLcheck(3,3,3,3),            & 
& TVOddllSLRcheck(3,3,3,3),TVOddllVRRcheck(3,3,3,3),TVOddllVLLcheck(3,3,3,3),            & 
& TVOddllVRLcheck(3,3,3,3),TVOddllVLRcheck(3,3,3,3),TVOddllTLLcheck(3,3,3,3),            & 
& TVOddllTLRcheck(3,3,3,3),TVOddllTRLcheck(3,3,3,3),TVOddllTRRcheck(3,3,3,3),            & 
& BOddvvVRRcheck(3,3,3,3),BOddvvVLLcheck(3,3,3,3),BOddvvVRLcheck(3,3,3,3),               & 
& BOddvvVLRcheck(3,3,3,3),PSOddvvVRRcheck(3,3,3,3),PSOddvvVLLcheck(3,3,3,3),             & 
& PSOddvvVRLcheck(3,3,3,3),PSOddvvVLRcheck(3,3,3,3),PVOddvvVRRcheck(3,3,3,3),            & 
& PVOddvvVLLcheck(3,3,3,3),PVOddvvVRLcheck(3,3,3,3),PVOddvvVLRcheck(3,3,3,3),            & 
& TSOddvvVRRcheck(3,3,3,3),TSOddvvVLLcheck(3,3,3,3),TSOddvvVRLcheck(3,3,3,3),            & 
& TSOddvvVLRcheck(3,3,3,3),TVOddvvVRRcheck(3,3,3,3),TVOddvvVLLcheck(3,3,3,3),            & 
& TVOddvvVRLcheck(3,3,3,3),TVOddvvVLRcheck(3,3,3,3),BO4dSLLcheck(3,3,3,3),               & 
& BO4dSRRcheck(3,3,3,3),BO4dSRLcheck(3,3,3,3),BO4dSLRcheck(3,3,3,3),BO4dVRRcheck(3,3,3,3),& 
& BO4dVLLcheck(3,3,3,3),BO4dVRLcheck(3,3,3,3),BO4dVLRcheck(3,3,3,3),BO4dTLLcheck(3,3,3,3),& 
& BO4dTLRcheck(3,3,3,3),BO4dTRLcheck(3,3,3,3),BO4dTRRcheck(3,3,3,3),TSO4dSLLcheck(3,3,3,3),& 
& TSO4dSRRcheck(3,3,3,3),TSO4dSRLcheck(3,3,3,3),TSO4dSLRcheck(3,3,3,3),TSO4dVRRcheck(3,3,3,3),& 
& TSO4dVLLcheck(3,3,3,3),TSO4dVRLcheck(3,3,3,3),TSO4dVLRcheck(3,3,3,3),TSO4dTLLcheck(3,3,3,3),& 
& TSO4dTLRcheck(3,3,3,3),TSO4dTRLcheck(3,3,3,3),TSO4dTRRcheck(3,3,3,3),TVO4dSLLcheck(3,3,3,3),& 
& TVO4dSRRcheck(3,3,3,3),TVO4dSRLcheck(3,3,3,3),TVO4dSLRcheck(3,3,3,3),TVO4dVRRcheck(3,3,3,3),& 
& TVO4dVLLcheck(3,3,3,3),TVO4dVRLcheck(3,3,3,3),TVO4dVLRcheck(3,3,3,3),TVO4dTLLcheck(3,3,3,3),& 
& TVO4dTLRcheck(3,3,3,3),TVO4dTRLcheck(3,3,3,3),TVO4dTRRcheck(3,3,3,3),OAh2qSLcheck(3,3,2),& 
& OAh2qSRcheck(3,3,2),TSOdulvSLLcheck(3,3,3,3),TSOdulvSRRcheck(3,3,3,3),TSOdulvSRLcheck(3,3,3,3)

Complex(dp) :: TSOdulvSLRcheck(3,3,3,3),TSOdulvVRRcheck(3,3,3,3),TSOdulvVLLcheck(3,3,3,3),            & 
& TSOdulvVRLcheck(3,3,3,3),TSOdulvVLRcheck(3,3,3,3),TVOdulvSLLcheck(3,3,3,3),            & 
& TVOdulvSRRcheck(3,3,3,3),TVOdulvSRLcheck(3,3,3,3),TVOdulvSLRcheck(3,3,3,3),            & 
& TVOdulvVRRcheck(3,3,3,3),TVOdulvVLLcheck(3,3,3,3),TVOdulvVRLcheck(3,3,3,3),            & 
& TVOdulvVLRcheck(3,3,3,3),OA2qSLcheck(3,3),OA2qSRcheck(3,3),OA2qVLcheck(3,3),           & 
& OA2qVRcheck(3,3),OG2qSLcheck(3,3),OG2qSRcheck(3,3),OH2qSLcheck(3,3,2),OH2qSRcheck(3,3,2)

Complex(dp) :: OllddSLL(3,3,3,3),OllddSRR(3,3,3,3),OllddSRL(3,3,3,3),OllddSLR(3,3,3,3),              & 
& OllddVRR(3,3,3,3),OllddVLL(3,3,3,3),OllddVRL(3,3,3,3),OllddVLR(3,3,3,3),               & 
& OllddTLL(3,3,3,3),OllddTLR(3,3,3,3),OllddTRL(3,3,3,3),OllddTRR(3,3,3,3),               & 
& OlluuSLL(3,3,3,3),OlluuSRR(3,3,3,3),OlluuSRL(3,3,3,3),OlluuSLR(3,3,3,3),               & 
& OlluuVRR(3,3,3,3),OlluuVLL(3,3,3,3),OlluuVRL(3,3,3,3),OlluuVLR(3,3,3,3),               & 
& OlluuTLL(3,3,3,3),OlluuTLR(3,3,3,3),OlluuTRL(3,3,3,3),OlluuTRR(3,3,3,3),               & 
& O4lSLL(3,3,3,3),O4lSRR(3,3,3,3),O4lSRL(3,3,3,3),O4lSLR(3,3,3,3),O4lVRR(3,3,3,3),       & 
& O4lVLL(3,3,3,3),O4lVRL(3,3,3,3),O4lVLR(3,3,3,3),O4lTLL(3,3,3,3),O4lTLR(3,3,3,3),       & 
& O4lTRL(3,3,3,3),O4lTRR(3,3,3,3),O4lSLLcross(3,3,3,3),O4lSRRcross(3,3,3,3),             & 
& O4lSRLcross(3,3,3,3),O4lSLRcross(3,3,3,3),O4lVRRcross(3,3,3,3),O4lVLLcross(3,3,3,3),   & 
& O4lVRLcross(3,3,3,3),O4lVLRcross(3,3,3,3),O4lTLLcross(3,3,3,3),O4lTLRcross(3,3,3,3),   & 
& O4lTRLcross(3,3,3,3),O4lTRRcross(3,3,3,3),K1L(3,3),K1R(3,3),K2L(3,3),K2R(3,3)

Complex(dp) :: OddllSLLSM(3,3,3,3),OddllSRRSM(3,3,3,3),OddllSRLSM(3,3,3,3),OddllSLRSM(3,3,3,3),      & 
& OddllVRRSM(3,3,3,3),OddllVLLSM(3,3,3,3),OddllVRLSM(3,3,3,3),OddllVLRSM(3,3,3,3),       & 
& OddllTLLSM(3,3,3,3),OddllTLRSM(3,3,3,3),OddllTRLSM(3,3,3,3),OddllTRRSM(3,3,3,3),       & 
& OddvvVRRSM(3,3,3,3),OddvvVLLSM(3,3,3,3),OddvvVRLSM(3,3,3,3),OddvvVLRSM(3,3,3,3),       & 
& O4dSLLSM(3,3,3,3),O4dSRRSM(3,3,3,3),O4dSRLSM(3,3,3,3),O4dSLRSM(3,3,3,3),               & 
& O4dVRRSM(3,3,3,3),O4dVLLSM(3,3,3,3),O4dVRLSM(3,3,3,3),O4dVLRSM(3,3,3,3),               & 
& O4dTLLSM(3,3,3,3),O4dTLRSM(3,3,3,3),O4dTRLSM(3,3,3,3),O4dTRRSM(3,3,3,3),               & 
& OdulvSLLSM(3,3,3,3),OdulvSRRSM(3,3,3,3),OdulvSRLSM(3,3,3,3),OdulvSLRSM(3,3,3,3),       & 
& OdulvVRRSM(3,3,3,3),OdulvVLLSM(3,3,3,3),OdulvVRLSM(3,3,3,3),OdulvVLRSM(3,3,3,3),       & 
& CC8SM(3,3),CC8pSM(3,3),CC7SM(3,3),CC7pSM(3,3)

Complex(dp) :: OddllSLL(3,3,3,3),OddllSRR(3,3,3,3),OddllSRL(3,3,3,3),OddllSLR(3,3,3,3),              & 
& OddllVRR(3,3,3,3),OddllVLL(3,3,3,3),OddllVRL(3,3,3,3),OddllVLR(3,3,3,3),               & 
& OddllTLL(3,3,3,3),OddllTLR(3,3,3,3),OddllTRL(3,3,3,3),OddllTRR(3,3,3,3),               & 
& OddvvVRR(3,3,3,3),OddvvVLL(3,3,3,3),OddvvVRL(3,3,3,3),OddvvVLR(3,3,3,3),               & 
& O4dSLL(3,3,3,3),O4dSRR(3,3,3,3),O4dSRL(3,3,3,3),O4dSLR(3,3,3,3),O4dVRR(3,3,3,3),       & 
& O4dVLL(3,3,3,3),O4dVRL(3,3,3,3),O4dVLR(3,3,3,3),O4dTLL(3,3,3,3),O4dTLR(3,3,3,3),       & 
& O4dTRL(3,3,3,3),O4dTRR(3,3,3,3),OdulvSLL(3,3,3,3),OdulvSRR(3,3,3,3),OdulvSRL(3,3,3,3), & 
& OdulvSLR(3,3,3,3),OdulvVRR(3,3,3,3),OdulvVLL(3,3,3,3),OdulvVRL(3,3,3,3),               & 
& OdulvVLR(3,3,3,3),CC8(3,3),CC8p(3,3),CC7(3,3),CC7p(3,3)

Write(*,*) "Calculating low energy constraints" 
g1input = Sqrt(5._dp/3._dp)*g1input 


!-------------------------------------
! running to 160 GeV for b -> so gamma
!-------------------------------------

Qin=sqrt(getRenormalizationScale()) 
scale_save = Qin 
Call RunSM_and_SUSY_RGEs(160._dp,g1input,g2input,g3input,Ydinput,Yeinput,             & 
& Yuinput,Muinput,Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,mHd2input,          & 
& mHu2input,md2input,mu2input,me2input,M1input,M2input,M3input,vdinput,vuinput,          & 
& g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,              & 
& vd,vu,CKM_160,sinW2_160,Alpha_160,AlphaS_160,.false.)


! ## All contributions ## 

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,GenerationMixing,kont)

 mf_d_160 = MFd(1:3) 
 mf_d2_160 = MFd(1:3)**2 
 mf_u_160 = MFu(1:3) 
 mf_u2_160 = MFu(1:3)**2 
 mf_l_160 = MFe(1:3) 
 mf_l2_160 = MFe(1:3)**2 
If (WriteParametersAtQ) Then 
! Write running parameters at Q=160 GeV in output file 
g1input = g1
g2input = g2
g3input = g3
Ydinput = Yd
Yeinput = Ye
Yuinput = Yu
Muinput = Mu
Tdinput = Td
Teinput = Te
Tuinput = Tu
Bmuinput = Bmu
mq2input = mq2
ml2input = ml2
mHd2input = mHd2
mHu2input = mHu2
md2input = md2
mu2input = mu2
me2input = me2
M1input = M1
M2input = M2
M3input = M3
vdinput = vd
vuinput = vu
End If 
 
Mhh= MhhL 
Mhh2 = Mhh2L 
MAh= MAhL 
MAh2 = MAh2L 
MAh(1)=MVZ
MAh2(1)=MVZ2
MHpm(1)=MVWm
MHpm2(1)=MVWm2
Call AllCouplings(g1,g2,vd,vu,ZH,ZA,ZP,Mu,Yd,Td,ZD,Ye,Te,ZE,Yu,Tu,ZU,ZV,              & 
& TW,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhhh,cplAhHpmcHpm,cplAhSdcSd,           & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplAhhhVZ,cplAhHpmcVWm,   & 
& cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSucSuVG,      & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplVGVGVG,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,         & 
& cplcFvChiSvR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,          & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,       & 
& cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,      & 
& cplcChacFvSeR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,               & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,   & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,cplGluGluVGR)

iQFinal = 1 
If (MakeQtest) iQFinal=10 
Qinsave=GetRenormalizationScale() 
Do iQTEST=1,iQFinal 
maxdiff=0._dp 
If (MakeQtest) Qin=SetRenormalizationScale(10.0_dp**iQTest) 

 ! **** Box2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& BOddllSLL(gt1,gt2,gt3,gt4),BOddllSRR(gt1,gt2,gt3,gt4),BOddllSRL(gt1,gt2,gt3,gt4)       & 
& ,BOddllSLR(gt1,gt2,gt3,gt4),BOddllVRR(gt1,gt2,gt3,gt4),BOddllVLL(gt1,gt2,gt3,gt4)      & 
& ,BOddllVRL(gt1,gt2,gt3,gt4),BOddllVLR(gt1,gt2,gt3,gt4),BOddllTLL(gt1,gt2,gt3,gt4)      & 
& ,BOddllTLR(gt1,gt2,gt3,gt4),BOddllTRL(gt1,gt2,gt3,gt4),BOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PSOddllSLL(gt1,gt2,gt3,gt4),PSOddllSRR(gt1,gt2,gt3,gt4),PSOddllSRL(gt1,gt2,gt3,gt4)    & 
& ,PSOddllSLR(gt1,gt2,gt3,gt4),PSOddllVRR(gt1,gt2,gt3,gt4),PSOddllVLL(gt1,gt2,gt3,gt4)   & 
& ,PSOddllVRL(gt1,gt2,gt3,gt4),PSOddllVLR(gt1,gt2,gt3,gt4),PSOddllTLL(gt1,gt2,gt3,gt4)   & 
& ,PSOddllTLR(gt1,gt2,gt3,gt4),PSOddllTRL(gt1,gt2,gt3,gt4),PSOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PVOddllSLL(gt1,gt2,gt3,gt4),PVOddllSRR(gt1,gt2,gt3,gt4),PVOddllSRL(gt1,gt2,gt3,gt4)    & 
& ,PVOddllSLR(gt1,gt2,gt3,gt4),PVOddllVRR(gt1,gt2,gt3,gt4),PVOddllVLL(gt1,gt2,gt3,gt4)   & 
& ,PVOddllVRL(gt1,gt2,gt3,gt4),PVOddllVLR(gt1,gt2,gt3,gt4),PVOddllTLL(gt1,gt2,gt3,gt4)   & 
& ,PVOddllTLR(gt1,gt2,gt3,gt4),PVOddllTRL(gt1,gt2,gt3,gt4),PVOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TSOddllSLL(gt1,gt2,gt3,gt4),TSOddllSRR(gt1,gt2,gt3,gt4),TSOddllSRL(gt1,gt2,gt3,gt4)    & 
& ,TSOddllSLR(gt1,gt2,gt3,gt4),TSOddllVRR(gt1,gt2,gt3,gt4),TSOddllVLL(gt1,gt2,gt3,gt4)   & 
& ,TSOddllVRL(gt1,gt2,gt3,gt4),TSOddllVLR(gt1,gt2,gt3,gt4),TSOddllTLL(gt1,gt2,gt3,gt4)   & 
& ,TSOddllTLR(gt1,gt2,gt3,gt4),TSOddllTRL(gt1,gt2,gt3,gt4),TSOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TVOddllSLL(gt1,gt2,gt3,gt4),TVOddllSRR(gt1,gt2,gt3,gt4),TVOddllSRL(gt1,gt2,gt3,gt4)    & 
& ,TVOddllSLR(gt1,gt2,gt3,gt4),TVOddllVRR(gt1,gt2,gt3,gt4),TVOddllVLL(gt1,gt2,gt3,gt4)   & 
& ,TVOddllVRL(gt1,gt2,gt3,gt4),TVOddllVLR(gt1,gt2,gt3,gt4),TVOddllTLL(gt1,gt2,gt3,gt4)   & 
& ,TVOddllTLR(gt1,gt2,gt3,gt4),TVOddllTRL(gt1,gt2,gt3,gt4),TVOddllTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** Box2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,BOddvvVRR(gt1,gt2,gt3,gt4)    & 
& ,BOddvvVLL(gt1,gt2,gt3,gt4),BOddvvVRL(gt1,gt2,gt3,gt4),BOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,            & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,PSOddvvVRR(gt1,gt2,gt3,gt4)   & 
& ,PSOddvvVLL(gt1,gt2,gt3,gt4),PSOddvvVRL(gt1,gt2,gt3,gt4),PSOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,            & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,PVOddvvVRR(gt1,gt2,gt3,gt4)   & 
& ,PVOddvvVLL(gt1,gt2,gt3,gt4),PVOddvvVRL(gt1,gt2,gt3,gt4),PVOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,            & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,TSOddvvVRR(gt1,gt2,gt3,gt4)   & 
& ,TSOddvvVLL(gt1,gt2,gt3,gt4),TSOddvvVRL(gt1,gt2,gt3,gt4),TSOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2nu(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,            & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,TVOddvvVRR(gt1,gt2,gt3,gt4)   & 
& ,TVOddvvVLL(gt1,gt2,gt3,gt4),TVOddvvVRL(gt1,gt2,gt3,gt4),TVOddvvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** Box4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,           & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& BO4dSLL(gt1,gt2,gt3,gt4),BO4dSRR(gt1,gt2,gt3,gt4),BO4dSRL(gt1,gt2,gt3,gt4)             & 
& ,BO4dSLR(gt1,gt2,gt3,gt4),BO4dVRR(gt1,gt2,gt3,gt4),BO4dVLL(gt1,gt2,gt3,gt4)            & 
& ,BO4dVRL(gt1,gt2,gt3,gt4),BO4dVLR(gt1,gt2,gt3,gt4),BO4dTLL(gt1,gt2,gt3,gt4)            & 
& ,BO4dTLR(gt1,gt2,gt3,gt4),BO4dTRL(gt1,gt2,gt3,gt4),BO4dTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,              & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,        & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& TSO4dSLL(gt1,gt2,gt3,gt4),TSO4dSRR(gt1,gt2,gt3,gt4),TSO4dSRL(gt1,gt2,gt3,gt4)          & 
& ,TSO4dSLR(gt1,gt2,gt3,gt4),TSO4dVRR(gt1,gt2,gt3,gt4),TSO4dVLL(gt1,gt2,gt3,gt4)         & 
& ,TSO4dVRL(gt1,gt2,gt3,gt4),TSO4dVLR(gt1,gt2,gt3,gt4),TSO4dTLL(gt1,gt2,gt3,gt4)         & 
& ,TSO4dTLR(gt1,gt2,gt3,gt4),TSO4dTRL(gt1,gt2,gt3,gt4),TSO4dTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,              & 
& MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,        & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& TVO4dSLL(gt1,gt2,gt3,gt4),TVO4dSRR(gt1,gt2,gt3,gt4),TVO4dSRL(gt1,gt2,gt3,gt4)          & 
& ,TVO4dSLR(gt1,gt2,gt3,gt4),TVO4dVRR(gt1,gt2,gt3,gt4),TVO4dVLL(gt1,gt2,gt3,gt4)         & 
& ,TVO4dVRL(gt1,gt2,gt3,gt4),TVO4dVLR(gt1,gt2,gt3,gt4),TVO4dTLL(gt1,gt2,gt3,gt4)         & 
& ,TVO4dTLR(gt1,gt2,gt3,gt4),TVO4dTRL(gt1,gt2,gt3,gt4),TVO4dTRR(gt1,gt2,gt3,gt4))

End do 



 ! **** A2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateA2q(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,             & 
& MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,MVWm2,             & 
& MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,        & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplChiChiAhL,cplChiChiAhR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,          & 
& cplGluFdcSdR,OAh2qSL(gt1,gt2,gt3),OAh2qSR(gt1,gt2,gt3))

 End Do  
End do 



 ! **** TreeSdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeSdulv(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,     & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,         & 
& cplHpmcVWmVZ,cplHpmSvcSe,cplSdcHpmcSu,cplSdcSucVWm,cplSvcSeVWm,TSOdulvSLL(gt1,gt2,gt3,gt4)& 
& ,TSOdulvSRR(gt1,gt2,gt3,gt4),TSOdulvSRL(gt1,gt2,gt3,gt4),TSOdulvSLR(gt1,gt2,gt3,gt4)   & 
& ,TSOdulvVRR(gt1,gt2,gt3,gt4),TSOdulvVLL(gt1,gt2,gt3,gt4),TSOdulvVRL(gt1,gt2,gt3,gt4)   & 
& ,TSOdulvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeVdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeVdulv(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,     & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,         & 
& cplHpmcVWmVZ,cplHpmSvcSe,cplSdcHpmcSu,cplSdcSucVWm,cplSvcSeVWm,TVOdulvSLL(gt1,gt2,gt3,gt4)& 
& ,TVOdulvSRR(gt1,gt2,gt3,gt4),TVOdulvSRL(gt1,gt2,gt3,gt4),TVOdulvSLR(gt1,gt2,gt3,gt4)   & 
& ,TVOdulvVRR(gt1,gt2,gt3,gt4),TVOdulvVLL(gt1,gt2,gt3,gt4),TVOdulvVRL(gt1,gt2,gt3,gt4)   & 
& ,TVOdulvVLR(gt1,gt2,gt3,gt4))

End do 



 ! **** Gamma2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2Q(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,             & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplcChaChaVPL,cplcChaChaVPR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVPL,      & 
& cplcFuFuVPR,cplChiFdcSdL,cplChiFdcSdR,cplcHpmVPVWm,cplcVWmVPVWm,cplGluFdcSdL,          & 
& cplGluFdcSdR,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSucSuVP,OA2qSL(gt1,gt2)           & 
& ,OA2qSR(gt1,gt2),OA2qVL(gt1,gt2),OA2qVR(gt1,gt2))

End do 



 ! **** Gluon2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGluon2Q(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,             & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVGL,cplcFuFuVGR,cplChiFdcSdL,        & 
& cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplGluGluVGL,cplGluGluVGR,cplSdcSdVG,           & 
& cplSucSuVG,OG2qSL(gt1,gt2),OG2qSR(gt1,gt2))

End do 



 ! **** H2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2q(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,             & 
& MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,MVWm2,             & 
& MVZ,MVZ2,cplAhAhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaFdcSuL,cplcChaFdcSuR,  & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,OH2qSL(gt1,gt2,gt3),OH2qSR(gt1,gt2,gt3))

 End Do  
End do 


If (MakeQTEST) Then  
where (Abs(BOddllSLLcheck).ne.0._dp) BOddllSLLcheck = (BOddllSLLcheck-BOddllSLL)/BOddllSLLcheck
If(MaxVal(Abs(BOddllSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllSLLcheck))
BOddllSLLcheck=BOddllSLL
where (Abs(BOddllSRRcheck).ne.0._dp) BOddllSRRcheck = (BOddllSRRcheck-BOddllSRR)/BOddllSRRcheck
If(MaxVal(Abs(BOddllSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllSRRcheck))
BOddllSRRcheck=BOddllSRR
where (Abs(BOddllSRLcheck).ne.0._dp) BOddllSRLcheck = (BOddllSRLcheck-BOddllSRL)/BOddllSRLcheck
If(MaxVal(Abs(BOddllSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllSRLcheck))
BOddllSRLcheck=BOddllSRL
where (Abs(BOddllSLRcheck).ne.0._dp) BOddllSLRcheck = (BOddllSLRcheck-BOddllSLR)/BOddllSLRcheck
If(MaxVal(Abs(BOddllSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllSLRcheck))
BOddllSLRcheck=BOddllSLR
where (Abs(BOddllVRRcheck).ne.0._dp) BOddllVRRcheck = (BOddllVRRcheck-BOddllVRR)/BOddllVRRcheck
If(MaxVal(Abs(BOddllVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllVRRcheck))
BOddllVRRcheck=BOddllVRR
where (Abs(BOddllVLLcheck).ne.0._dp) BOddllVLLcheck = (BOddllVLLcheck-BOddllVLL)/BOddllVLLcheck
If(MaxVal(Abs(BOddllVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllVLLcheck))
BOddllVLLcheck=BOddllVLL
where (Abs(BOddllVRLcheck).ne.0._dp) BOddllVRLcheck = (BOddllVRLcheck-BOddllVRL)/BOddllVRLcheck
If(MaxVal(Abs(BOddllVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllVRLcheck))
BOddllVRLcheck=BOddllVRL
where (Abs(BOddllVLRcheck).ne.0._dp) BOddllVLRcheck = (BOddllVLRcheck-BOddllVLR)/BOddllVLRcheck
If(MaxVal(Abs(BOddllVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllVLRcheck))
BOddllVLRcheck=BOddllVLR
where (Abs(BOddllTLLcheck).ne.0._dp) BOddllTLLcheck = (BOddllTLLcheck-BOddllTLL)/BOddllTLLcheck
If(MaxVal(Abs(BOddllTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllTLLcheck))
BOddllTLLcheck=BOddllTLL
where (Abs(BOddllTLRcheck).ne.0._dp) BOddllTLRcheck = (BOddllTLRcheck-BOddllTLR)/BOddllTLRcheck
If(MaxVal(Abs(BOddllTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllTLRcheck))
BOddllTLRcheck=BOddllTLR
where (Abs(BOddllTRLcheck).ne.0._dp) BOddllTRLcheck = (BOddllTRLcheck-BOddllTRL)/BOddllTRLcheck
If(MaxVal(Abs(BOddllTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllTRLcheck))
BOddllTRLcheck=BOddllTRL
where (Abs(BOddllTRRcheck).ne.0._dp) BOddllTRRcheck = (BOddllTRRcheck-BOddllTRR)/BOddllTRRcheck
If(MaxVal(Abs(BOddllTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddllTRRcheck))
BOddllTRRcheck=BOddllTRR
where (Abs(PSOddllSLLcheck).ne.0._dp) PSOddllSLLcheck = (PSOddllSLLcheck-PSOddllSLL)/PSOddllSLLcheck
If(MaxVal(Abs(PSOddllSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllSLLcheck))
PSOddllSLLcheck=PSOddllSLL
where (Abs(PSOddllSRRcheck).ne.0._dp) PSOddllSRRcheck = (PSOddllSRRcheck-PSOddllSRR)/PSOddllSRRcheck
If(MaxVal(Abs(PSOddllSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllSRRcheck))
PSOddllSRRcheck=PSOddllSRR
where (Abs(PSOddllSRLcheck).ne.0._dp) PSOddllSRLcheck = (PSOddllSRLcheck-PSOddllSRL)/PSOddllSRLcheck
If(MaxVal(Abs(PSOddllSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllSRLcheck))
PSOddllSRLcheck=PSOddllSRL
where (Abs(PSOddllSLRcheck).ne.0._dp) PSOddllSLRcheck = (PSOddllSLRcheck-PSOddllSLR)/PSOddllSLRcheck
If(MaxVal(Abs(PSOddllSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllSLRcheck))
PSOddllSLRcheck=PSOddllSLR
where (Abs(PSOddllVRRcheck).ne.0._dp) PSOddllVRRcheck = (PSOddllVRRcheck-PSOddllVRR)/PSOddllVRRcheck
If(MaxVal(Abs(PSOddllVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllVRRcheck))
PSOddllVRRcheck=PSOddllVRR
where (Abs(PSOddllVLLcheck).ne.0._dp) PSOddllVLLcheck = (PSOddllVLLcheck-PSOddllVLL)/PSOddllVLLcheck
If(MaxVal(Abs(PSOddllVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllVLLcheck))
PSOddllVLLcheck=PSOddllVLL
where (Abs(PSOddllVRLcheck).ne.0._dp) PSOddllVRLcheck = (PSOddllVRLcheck-PSOddllVRL)/PSOddllVRLcheck
If(MaxVal(Abs(PSOddllVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllVRLcheck))
PSOddllVRLcheck=PSOddllVRL
where (Abs(PSOddllVLRcheck).ne.0._dp) PSOddllVLRcheck = (PSOddllVLRcheck-PSOddllVLR)/PSOddllVLRcheck
If(MaxVal(Abs(PSOddllVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllVLRcheck))
PSOddllVLRcheck=PSOddllVLR
where (Abs(PSOddllTLLcheck).ne.0._dp) PSOddllTLLcheck = (PSOddllTLLcheck-PSOddllTLL)/PSOddllTLLcheck
If(MaxVal(Abs(PSOddllTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllTLLcheck))
PSOddllTLLcheck=PSOddllTLL
where (Abs(PSOddllTLRcheck).ne.0._dp) PSOddllTLRcheck = (PSOddllTLRcheck-PSOddllTLR)/PSOddllTLRcheck
If(MaxVal(Abs(PSOddllTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllTLRcheck))
PSOddllTLRcheck=PSOddllTLR
where (Abs(PSOddllTRLcheck).ne.0._dp) PSOddllTRLcheck = (PSOddllTRLcheck-PSOddllTRL)/PSOddllTRLcheck
If(MaxVal(Abs(PSOddllTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllTRLcheck))
PSOddllTRLcheck=PSOddllTRL
where (Abs(PSOddllTRRcheck).ne.0._dp) PSOddllTRRcheck = (PSOddllTRRcheck-PSOddllTRR)/PSOddllTRRcheck
If(MaxVal(Abs(PSOddllTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddllTRRcheck))
PSOddllTRRcheck=PSOddllTRR
where (Abs(PVOddllSLLcheck).ne.0._dp) PVOddllSLLcheck = (PVOddllSLLcheck-PVOddllSLL)/PVOddllSLLcheck
If(MaxVal(Abs(PVOddllSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllSLLcheck))
PVOddllSLLcheck=PVOddllSLL
where (Abs(PVOddllSRRcheck).ne.0._dp) PVOddllSRRcheck = (PVOddllSRRcheck-PVOddllSRR)/PVOddllSRRcheck
If(MaxVal(Abs(PVOddllSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllSRRcheck))
PVOddllSRRcheck=PVOddllSRR
where (Abs(PVOddllSRLcheck).ne.0._dp) PVOddllSRLcheck = (PVOddllSRLcheck-PVOddllSRL)/PVOddllSRLcheck
If(MaxVal(Abs(PVOddllSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllSRLcheck))
PVOddllSRLcheck=PVOddllSRL
where (Abs(PVOddllSLRcheck).ne.0._dp) PVOddllSLRcheck = (PVOddllSLRcheck-PVOddllSLR)/PVOddllSLRcheck
If(MaxVal(Abs(PVOddllSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllSLRcheck))
PVOddllSLRcheck=PVOddllSLR
where (Abs(PVOddllVRRcheck).ne.0._dp) PVOddllVRRcheck = (PVOddllVRRcheck-PVOddllVRR)/PVOddllVRRcheck
If(MaxVal(Abs(PVOddllVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllVRRcheck))
PVOddllVRRcheck=PVOddllVRR
where (Abs(PVOddllVLLcheck).ne.0._dp) PVOddllVLLcheck = (PVOddllVLLcheck-PVOddllVLL)/PVOddllVLLcheck
If(MaxVal(Abs(PVOddllVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllVLLcheck))
PVOddllVLLcheck=PVOddllVLL
where (Abs(PVOddllVRLcheck).ne.0._dp) PVOddllVRLcheck = (PVOddllVRLcheck-PVOddllVRL)/PVOddllVRLcheck
If(MaxVal(Abs(PVOddllVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllVRLcheck))
PVOddllVRLcheck=PVOddllVRL
where (Abs(PVOddllVLRcheck).ne.0._dp) PVOddllVLRcheck = (PVOddllVLRcheck-PVOddllVLR)/PVOddllVLRcheck
If(MaxVal(Abs(PVOddllVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllVLRcheck))
PVOddllVLRcheck=PVOddllVLR
where (Abs(PVOddllTLLcheck).ne.0._dp) PVOddllTLLcheck = (PVOddllTLLcheck-PVOddllTLL)/PVOddllTLLcheck
If(MaxVal(Abs(PVOddllTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllTLLcheck))
PVOddllTLLcheck=PVOddllTLL
where (Abs(PVOddllTLRcheck).ne.0._dp) PVOddllTLRcheck = (PVOddllTLRcheck-PVOddllTLR)/PVOddllTLRcheck
If(MaxVal(Abs(PVOddllTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllTLRcheck))
PVOddllTLRcheck=PVOddllTLR
where (Abs(PVOddllTRLcheck).ne.0._dp) PVOddllTRLcheck = (PVOddllTRLcheck-PVOddllTRL)/PVOddllTRLcheck
If(MaxVal(Abs(PVOddllTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllTRLcheck))
PVOddllTRLcheck=PVOddllTRL
where (Abs(PVOddllTRRcheck).ne.0._dp) PVOddllTRRcheck = (PVOddllTRRcheck-PVOddllTRR)/PVOddllTRRcheck
If(MaxVal(Abs(PVOddllTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddllTRRcheck))
PVOddllTRRcheck=PVOddllTRR
where (Abs(TSOddllSLLcheck).ne.0._dp) TSOddllSLLcheck = (TSOddllSLLcheck-TSOddllSLL)/TSOddllSLLcheck
If(MaxVal(Abs(TSOddllSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllSLLcheck))
TSOddllSLLcheck=TSOddllSLL
where (Abs(TSOddllSRRcheck).ne.0._dp) TSOddllSRRcheck = (TSOddllSRRcheck-TSOddllSRR)/TSOddllSRRcheck
If(MaxVal(Abs(TSOddllSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllSRRcheck))
TSOddllSRRcheck=TSOddllSRR
where (Abs(TSOddllSRLcheck).ne.0._dp) TSOddllSRLcheck = (TSOddllSRLcheck-TSOddllSRL)/TSOddllSRLcheck
If(MaxVal(Abs(TSOddllSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllSRLcheck))
TSOddllSRLcheck=TSOddllSRL
where (Abs(TSOddllSLRcheck).ne.0._dp) TSOddllSLRcheck = (TSOddllSLRcheck-TSOddllSLR)/TSOddllSLRcheck
If(MaxVal(Abs(TSOddllSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllSLRcheck))
TSOddllSLRcheck=TSOddllSLR
where (Abs(TSOddllVRRcheck).ne.0._dp) TSOddllVRRcheck = (TSOddllVRRcheck-TSOddllVRR)/TSOddllVRRcheck
If(MaxVal(Abs(TSOddllVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllVRRcheck))
TSOddllVRRcheck=TSOddllVRR
where (Abs(TSOddllVLLcheck).ne.0._dp) TSOddllVLLcheck = (TSOddllVLLcheck-TSOddllVLL)/TSOddllVLLcheck
If(MaxVal(Abs(TSOddllVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllVLLcheck))
TSOddllVLLcheck=TSOddllVLL
where (Abs(TSOddllVRLcheck).ne.0._dp) TSOddllVRLcheck = (TSOddllVRLcheck-TSOddllVRL)/TSOddllVRLcheck
If(MaxVal(Abs(TSOddllVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllVRLcheck))
TSOddllVRLcheck=TSOddllVRL
where (Abs(TSOddllVLRcheck).ne.0._dp) TSOddllVLRcheck = (TSOddllVLRcheck-TSOddllVLR)/TSOddllVLRcheck
If(MaxVal(Abs(TSOddllVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllVLRcheck))
TSOddllVLRcheck=TSOddllVLR
where (Abs(TSOddllTLLcheck).ne.0._dp) TSOddllTLLcheck = (TSOddllTLLcheck-TSOddllTLL)/TSOddllTLLcheck
If(MaxVal(Abs(TSOddllTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllTLLcheck))
TSOddllTLLcheck=TSOddllTLL
where (Abs(TSOddllTLRcheck).ne.0._dp) TSOddllTLRcheck = (TSOddllTLRcheck-TSOddllTLR)/TSOddllTLRcheck
If(MaxVal(Abs(TSOddllTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllTLRcheck))
TSOddllTLRcheck=TSOddllTLR
where (Abs(TSOddllTRLcheck).ne.0._dp) TSOddllTRLcheck = (TSOddllTRLcheck-TSOddllTRL)/TSOddllTRLcheck
If(MaxVal(Abs(TSOddllTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllTRLcheck))
TSOddllTRLcheck=TSOddllTRL
where (Abs(TSOddllTRRcheck).ne.0._dp) TSOddllTRRcheck = (TSOddllTRRcheck-TSOddllTRR)/TSOddllTRRcheck
If(MaxVal(Abs(TSOddllTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddllTRRcheck))
TSOddllTRRcheck=TSOddllTRR
where (Abs(TVOddllSLLcheck).ne.0._dp) TVOddllSLLcheck = (TVOddllSLLcheck-TVOddllSLL)/TVOddllSLLcheck
If(MaxVal(Abs(TVOddllSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllSLLcheck))
TVOddllSLLcheck=TVOddllSLL
where (Abs(TVOddllSRRcheck).ne.0._dp) TVOddllSRRcheck = (TVOddllSRRcheck-TVOddllSRR)/TVOddllSRRcheck
If(MaxVal(Abs(TVOddllSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllSRRcheck))
TVOddllSRRcheck=TVOddllSRR
where (Abs(TVOddllSRLcheck).ne.0._dp) TVOddllSRLcheck = (TVOddllSRLcheck-TVOddllSRL)/TVOddllSRLcheck
If(MaxVal(Abs(TVOddllSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllSRLcheck))
TVOddllSRLcheck=TVOddllSRL
where (Abs(TVOddllSLRcheck).ne.0._dp) TVOddllSLRcheck = (TVOddllSLRcheck-TVOddllSLR)/TVOddllSLRcheck
If(MaxVal(Abs(TVOddllSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllSLRcheck))
TVOddllSLRcheck=TVOddllSLR
where (Abs(TVOddllVRRcheck).ne.0._dp) TVOddllVRRcheck = (TVOddllVRRcheck-TVOddllVRR)/TVOddllVRRcheck
If(MaxVal(Abs(TVOddllVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllVRRcheck))
TVOddllVRRcheck=TVOddllVRR
where (Abs(TVOddllVLLcheck).ne.0._dp) TVOddllVLLcheck = (TVOddllVLLcheck-TVOddllVLL)/TVOddllVLLcheck
If(MaxVal(Abs(TVOddllVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllVLLcheck))
TVOddllVLLcheck=TVOddllVLL
where (Abs(TVOddllVRLcheck).ne.0._dp) TVOddllVRLcheck = (TVOddllVRLcheck-TVOddllVRL)/TVOddllVRLcheck
If(MaxVal(Abs(TVOddllVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllVRLcheck))
TVOddllVRLcheck=TVOddllVRL
where (Abs(TVOddllVLRcheck).ne.0._dp) TVOddllVLRcheck = (TVOddllVLRcheck-TVOddllVLR)/TVOddllVLRcheck
If(MaxVal(Abs(TVOddllVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllVLRcheck))
TVOddllVLRcheck=TVOddllVLR
where (Abs(TVOddllTLLcheck).ne.0._dp) TVOddllTLLcheck = (TVOddllTLLcheck-TVOddllTLL)/TVOddllTLLcheck
If(MaxVal(Abs(TVOddllTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllTLLcheck))
TVOddllTLLcheck=TVOddllTLL
where (Abs(TVOddllTLRcheck).ne.0._dp) TVOddllTLRcheck = (TVOddllTLRcheck-TVOddllTLR)/TVOddllTLRcheck
If(MaxVal(Abs(TVOddllTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllTLRcheck))
TVOddllTLRcheck=TVOddllTLR
where (Abs(TVOddllTRLcheck).ne.0._dp) TVOddllTRLcheck = (TVOddllTRLcheck-TVOddllTRL)/TVOddllTRLcheck
If(MaxVal(Abs(TVOddllTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllTRLcheck))
TVOddllTRLcheck=TVOddllTRL
where (Abs(TVOddllTRRcheck).ne.0._dp) TVOddllTRRcheck = (TVOddllTRRcheck-TVOddllTRR)/TVOddllTRRcheck
If(MaxVal(Abs(TVOddllTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddllTRRcheck))
TVOddllTRRcheck=TVOddllTRR
where (Abs(BOddvvVRRcheck).ne.0._dp) BOddvvVRRcheck = (BOddvvVRRcheck-BOddvvVRR)/BOddvvVRRcheck
If(MaxVal(Abs(BOddvvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddvvVRRcheck))
BOddvvVRRcheck=BOddvvVRR
where (Abs(BOddvvVLLcheck).ne.0._dp) BOddvvVLLcheck = (BOddvvVLLcheck-BOddvvVLL)/BOddvvVLLcheck
If(MaxVal(Abs(BOddvvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddvvVLLcheck))
BOddvvVLLcheck=BOddvvVLL
where (Abs(BOddvvVRLcheck).ne.0._dp) BOddvvVRLcheck = (BOddvvVRLcheck-BOddvvVRL)/BOddvvVRLcheck
If(MaxVal(Abs(BOddvvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddvvVRLcheck))
BOddvvVRLcheck=BOddvvVRL
where (Abs(BOddvvVLRcheck).ne.0._dp) BOddvvVLRcheck = (BOddvvVLRcheck-BOddvvVLR)/BOddvvVLRcheck
If(MaxVal(Abs(BOddvvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOddvvVLRcheck))
BOddvvVLRcheck=BOddvvVLR
where (Abs(PSOddvvVRRcheck).ne.0._dp) PSOddvvVRRcheck = (PSOddvvVRRcheck-PSOddvvVRR)/PSOddvvVRRcheck
If(MaxVal(Abs(PSOddvvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddvvVRRcheck))
PSOddvvVRRcheck=PSOddvvVRR
where (Abs(PSOddvvVLLcheck).ne.0._dp) PSOddvvVLLcheck = (PSOddvvVLLcheck-PSOddvvVLL)/PSOddvvVLLcheck
If(MaxVal(Abs(PSOddvvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddvvVLLcheck))
PSOddvvVLLcheck=PSOddvvVLL
where (Abs(PSOddvvVRLcheck).ne.0._dp) PSOddvvVRLcheck = (PSOddvvVRLcheck-PSOddvvVRL)/PSOddvvVRLcheck
If(MaxVal(Abs(PSOddvvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddvvVRLcheck))
PSOddvvVRLcheck=PSOddvvVRL
where (Abs(PSOddvvVLRcheck).ne.0._dp) PSOddvvVLRcheck = (PSOddvvVLRcheck-PSOddvvVLR)/PSOddvvVLRcheck
If(MaxVal(Abs(PSOddvvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOddvvVLRcheck))
PSOddvvVLRcheck=PSOddvvVLR
where (Abs(PVOddvvVRRcheck).ne.0._dp) PVOddvvVRRcheck = (PVOddvvVRRcheck-PVOddvvVRR)/PVOddvvVRRcheck
If(MaxVal(Abs(PVOddvvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddvvVRRcheck))
PVOddvvVRRcheck=PVOddvvVRR
where (Abs(PVOddvvVLLcheck).ne.0._dp) PVOddvvVLLcheck = (PVOddvvVLLcheck-PVOddvvVLL)/PVOddvvVLLcheck
If(MaxVal(Abs(PVOddvvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddvvVLLcheck))
PVOddvvVLLcheck=PVOddvvVLL
where (Abs(PVOddvvVRLcheck).ne.0._dp) PVOddvvVRLcheck = (PVOddvvVRLcheck-PVOddvvVRL)/PVOddvvVRLcheck
If(MaxVal(Abs(PVOddvvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddvvVRLcheck))
PVOddvvVRLcheck=PVOddvvVRL
where (Abs(PVOddvvVLRcheck).ne.0._dp) PVOddvvVLRcheck = (PVOddvvVLRcheck-PVOddvvVLR)/PVOddvvVLRcheck
If(MaxVal(Abs(PVOddvvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOddvvVLRcheck))
PVOddvvVLRcheck=PVOddvvVLR
where (Abs(TSOddvvVRRcheck).ne.0._dp) TSOddvvVRRcheck = (TSOddvvVRRcheck-TSOddvvVRR)/TSOddvvVRRcheck
If(MaxVal(Abs(TSOddvvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddvvVRRcheck))
TSOddvvVRRcheck=TSOddvvVRR
where (Abs(TSOddvvVLLcheck).ne.0._dp) TSOddvvVLLcheck = (TSOddvvVLLcheck-TSOddvvVLL)/TSOddvvVLLcheck
If(MaxVal(Abs(TSOddvvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddvvVLLcheck))
TSOddvvVLLcheck=TSOddvvVLL
where (Abs(TSOddvvVRLcheck).ne.0._dp) TSOddvvVRLcheck = (TSOddvvVRLcheck-TSOddvvVRL)/TSOddvvVRLcheck
If(MaxVal(Abs(TSOddvvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddvvVRLcheck))
TSOddvvVRLcheck=TSOddvvVRL
where (Abs(TSOddvvVLRcheck).ne.0._dp) TSOddvvVLRcheck = (TSOddvvVLRcheck-TSOddvvVLR)/TSOddvvVLRcheck
If(MaxVal(Abs(TSOddvvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOddvvVLRcheck))
TSOddvvVLRcheck=TSOddvvVLR
where (Abs(TVOddvvVRRcheck).ne.0._dp) TVOddvvVRRcheck = (TVOddvvVRRcheck-TVOddvvVRR)/TVOddvvVRRcheck
If(MaxVal(Abs(TVOddvvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddvvVRRcheck))
TVOddvvVRRcheck=TVOddvvVRR
where (Abs(TVOddvvVLLcheck).ne.0._dp) TVOddvvVLLcheck = (TVOddvvVLLcheck-TVOddvvVLL)/TVOddvvVLLcheck
If(MaxVal(Abs(TVOddvvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddvvVLLcheck))
TVOddvvVLLcheck=TVOddvvVLL
where (Abs(TVOddvvVRLcheck).ne.0._dp) TVOddvvVRLcheck = (TVOddvvVRLcheck-TVOddvvVRL)/TVOddvvVRLcheck
If(MaxVal(Abs(TVOddvvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddvvVRLcheck))
TVOddvvVRLcheck=TVOddvvVRL
where (Abs(TVOddvvVLRcheck).ne.0._dp) TVOddvvVLRcheck = (TVOddvvVLRcheck-TVOddvvVLR)/TVOddvvVLRcheck
If(MaxVal(Abs(TVOddvvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOddvvVLRcheck))
TVOddvvVLRcheck=TVOddvvVLR
where (Abs(BO4dSLLcheck).ne.0._dp) BO4dSLLcheck = (BO4dSLLcheck-BO4dSLL)/BO4dSLLcheck
If(MaxVal(Abs(BO4dSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dSLLcheck))
BO4dSLLcheck=BO4dSLL
where (Abs(BO4dSRRcheck).ne.0._dp) BO4dSRRcheck = (BO4dSRRcheck-BO4dSRR)/BO4dSRRcheck
If(MaxVal(Abs(BO4dSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dSRRcheck))
BO4dSRRcheck=BO4dSRR
where (Abs(BO4dSRLcheck).ne.0._dp) BO4dSRLcheck = (BO4dSRLcheck-BO4dSRL)/BO4dSRLcheck
If(MaxVal(Abs(BO4dSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dSRLcheck))
BO4dSRLcheck=BO4dSRL
where (Abs(BO4dSLRcheck).ne.0._dp) BO4dSLRcheck = (BO4dSLRcheck-BO4dSLR)/BO4dSLRcheck
If(MaxVal(Abs(BO4dSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dSLRcheck))
BO4dSLRcheck=BO4dSLR
where (Abs(BO4dVRRcheck).ne.0._dp) BO4dVRRcheck = (BO4dVRRcheck-BO4dVRR)/BO4dVRRcheck
If(MaxVal(Abs(BO4dVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dVRRcheck))
BO4dVRRcheck=BO4dVRR
where (Abs(BO4dVLLcheck).ne.0._dp) BO4dVLLcheck = (BO4dVLLcheck-BO4dVLL)/BO4dVLLcheck
If(MaxVal(Abs(BO4dVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dVLLcheck))
BO4dVLLcheck=BO4dVLL
where (Abs(BO4dVRLcheck).ne.0._dp) BO4dVRLcheck = (BO4dVRLcheck-BO4dVRL)/BO4dVRLcheck
If(MaxVal(Abs(BO4dVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dVRLcheck))
BO4dVRLcheck=BO4dVRL
where (Abs(BO4dVLRcheck).ne.0._dp) BO4dVLRcheck = (BO4dVLRcheck-BO4dVLR)/BO4dVLRcheck
If(MaxVal(Abs(BO4dVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dVLRcheck))
BO4dVLRcheck=BO4dVLR
where (Abs(BO4dTLLcheck).ne.0._dp) BO4dTLLcheck = (BO4dTLLcheck-BO4dTLL)/BO4dTLLcheck
If(MaxVal(Abs(BO4dTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dTLLcheck))
BO4dTLLcheck=BO4dTLL
where (Abs(BO4dTLRcheck).ne.0._dp) BO4dTLRcheck = (BO4dTLRcheck-BO4dTLR)/BO4dTLRcheck
If(MaxVal(Abs(BO4dTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dTLRcheck))
BO4dTLRcheck=BO4dTLR
where (Abs(BO4dTRLcheck).ne.0._dp) BO4dTRLcheck = (BO4dTRLcheck-BO4dTRL)/BO4dTRLcheck
If(MaxVal(Abs(BO4dTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dTRLcheck))
BO4dTRLcheck=BO4dTRL
where (Abs(BO4dTRRcheck).ne.0._dp) BO4dTRRcheck = (BO4dTRRcheck-BO4dTRR)/BO4dTRRcheck
If(MaxVal(Abs(BO4dTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4dTRRcheck))
BO4dTRRcheck=BO4dTRR
where (Abs(TSO4dSLLcheck).ne.0._dp) TSO4dSLLcheck = (TSO4dSLLcheck-TSO4dSLL)/TSO4dSLLcheck
If(MaxVal(Abs(TSO4dSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dSLLcheck))
TSO4dSLLcheck=TSO4dSLL
where (Abs(TSO4dSRRcheck).ne.0._dp) TSO4dSRRcheck = (TSO4dSRRcheck-TSO4dSRR)/TSO4dSRRcheck
If(MaxVal(Abs(TSO4dSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dSRRcheck))
TSO4dSRRcheck=TSO4dSRR
where (Abs(TSO4dSRLcheck).ne.0._dp) TSO4dSRLcheck = (TSO4dSRLcheck-TSO4dSRL)/TSO4dSRLcheck
If(MaxVal(Abs(TSO4dSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dSRLcheck))
TSO4dSRLcheck=TSO4dSRL
where (Abs(TSO4dSLRcheck).ne.0._dp) TSO4dSLRcheck = (TSO4dSLRcheck-TSO4dSLR)/TSO4dSLRcheck
If(MaxVal(Abs(TSO4dSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dSLRcheck))
TSO4dSLRcheck=TSO4dSLR
where (Abs(TSO4dVRRcheck).ne.0._dp) TSO4dVRRcheck = (TSO4dVRRcheck-TSO4dVRR)/TSO4dVRRcheck
If(MaxVal(Abs(TSO4dVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dVRRcheck))
TSO4dVRRcheck=TSO4dVRR
where (Abs(TSO4dVLLcheck).ne.0._dp) TSO4dVLLcheck = (TSO4dVLLcheck-TSO4dVLL)/TSO4dVLLcheck
If(MaxVal(Abs(TSO4dVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dVLLcheck))
TSO4dVLLcheck=TSO4dVLL
where (Abs(TSO4dVRLcheck).ne.0._dp) TSO4dVRLcheck = (TSO4dVRLcheck-TSO4dVRL)/TSO4dVRLcheck
If(MaxVal(Abs(TSO4dVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dVRLcheck))
TSO4dVRLcheck=TSO4dVRL
where (Abs(TSO4dVLRcheck).ne.0._dp) TSO4dVLRcheck = (TSO4dVLRcheck-TSO4dVLR)/TSO4dVLRcheck
If(MaxVal(Abs(TSO4dVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dVLRcheck))
TSO4dVLRcheck=TSO4dVLR
where (Abs(TSO4dTLLcheck).ne.0._dp) TSO4dTLLcheck = (TSO4dTLLcheck-TSO4dTLL)/TSO4dTLLcheck
If(MaxVal(Abs(TSO4dTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dTLLcheck))
TSO4dTLLcheck=TSO4dTLL
where (Abs(TSO4dTLRcheck).ne.0._dp) TSO4dTLRcheck = (TSO4dTLRcheck-TSO4dTLR)/TSO4dTLRcheck
If(MaxVal(Abs(TSO4dTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dTLRcheck))
TSO4dTLRcheck=TSO4dTLR
where (Abs(TSO4dTRLcheck).ne.0._dp) TSO4dTRLcheck = (TSO4dTRLcheck-TSO4dTRL)/TSO4dTRLcheck
If(MaxVal(Abs(TSO4dTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dTRLcheck))
TSO4dTRLcheck=TSO4dTRL
where (Abs(TSO4dTRRcheck).ne.0._dp) TSO4dTRRcheck = (TSO4dTRRcheck-TSO4dTRR)/TSO4dTRRcheck
If(MaxVal(Abs(TSO4dTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4dTRRcheck))
TSO4dTRRcheck=TSO4dTRR
where (Abs(TVO4dSLLcheck).ne.0._dp) TVO4dSLLcheck = (TVO4dSLLcheck-TVO4dSLL)/TVO4dSLLcheck
If(MaxVal(Abs(TVO4dSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dSLLcheck))
TVO4dSLLcheck=TVO4dSLL
where (Abs(TVO4dSRRcheck).ne.0._dp) TVO4dSRRcheck = (TVO4dSRRcheck-TVO4dSRR)/TVO4dSRRcheck
If(MaxVal(Abs(TVO4dSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dSRRcheck))
TVO4dSRRcheck=TVO4dSRR
where (Abs(TVO4dSRLcheck).ne.0._dp) TVO4dSRLcheck = (TVO4dSRLcheck-TVO4dSRL)/TVO4dSRLcheck
If(MaxVal(Abs(TVO4dSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dSRLcheck))
TVO4dSRLcheck=TVO4dSRL
where (Abs(TVO4dSLRcheck).ne.0._dp) TVO4dSLRcheck = (TVO4dSLRcheck-TVO4dSLR)/TVO4dSLRcheck
If(MaxVal(Abs(TVO4dSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dSLRcheck))
TVO4dSLRcheck=TVO4dSLR
where (Abs(TVO4dVRRcheck).ne.0._dp) TVO4dVRRcheck = (TVO4dVRRcheck-TVO4dVRR)/TVO4dVRRcheck
If(MaxVal(Abs(TVO4dVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dVRRcheck))
TVO4dVRRcheck=TVO4dVRR
where (Abs(TVO4dVLLcheck).ne.0._dp) TVO4dVLLcheck = (TVO4dVLLcheck-TVO4dVLL)/TVO4dVLLcheck
If(MaxVal(Abs(TVO4dVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dVLLcheck))
TVO4dVLLcheck=TVO4dVLL
where (Abs(TVO4dVRLcheck).ne.0._dp) TVO4dVRLcheck = (TVO4dVRLcheck-TVO4dVRL)/TVO4dVRLcheck
If(MaxVal(Abs(TVO4dVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dVRLcheck))
TVO4dVRLcheck=TVO4dVRL
where (Abs(TVO4dVLRcheck).ne.0._dp) TVO4dVLRcheck = (TVO4dVLRcheck-TVO4dVLR)/TVO4dVLRcheck
If(MaxVal(Abs(TVO4dVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dVLRcheck))
TVO4dVLRcheck=TVO4dVLR
where (Abs(TVO4dTLLcheck).ne.0._dp) TVO4dTLLcheck = (TVO4dTLLcheck-TVO4dTLL)/TVO4dTLLcheck
If(MaxVal(Abs(TVO4dTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dTLLcheck))
TVO4dTLLcheck=TVO4dTLL
where (Abs(TVO4dTLRcheck).ne.0._dp) TVO4dTLRcheck = (TVO4dTLRcheck-TVO4dTLR)/TVO4dTLRcheck
If(MaxVal(Abs(TVO4dTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dTLRcheck))
TVO4dTLRcheck=TVO4dTLR
where (Abs(TVO4dTRLcheck).ne.0._dp) TVO4dTRLcheck = (TVO4dTRLcheck-TVO4dTRL)/TVO4dTRLcheck
If(MaxVal(Abs(TVO4dTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dTRLcheck))
TVO4dTRLcheck=TVO4dTRL
where (Abs(TVO4dTRRcheck).ne.0._dp) TVO4dTRRcheck = (TVO4dTRRcheck-TVO4dTRR)/TVO4dTRRcheck
If(MaxVal(Abs(TVO4dTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4dTRRcheck))
TVO4dTRRcheck=TVO4dTRR
where (Abs(OAh2qSLcheck).ne.0._dp) OAh2qSLcheck = (OAh2qSLcheck-OAh2qSL)/OAh2qSLcheck
If(MaxVal(Abs(OAh2qSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OAh2qSLcheck))
OAh2qSLcheck=OAh2qSL
where (Abs(OAh2qSRcheck).ne.0._dp) OAh2qSRcheck = (OAh2qSRcheck-OAh2qSR)/OAh2qSRcheck
If(MaxVal(Abs(OAh2qSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OAh2qSRcheck))
OAh2qSRcheck=OAh2qSR
where (Abs(TSOdulvSLLcheck).ne.0._dp) TSOdulvSLLcheck = (TSOdulvSLLcheck-TSOdulvSLL)/TSOdulvSLLcheck
If(MaxVal(Abs(TSOdulvSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvSLLcheck))
TSOdulvSLLcheck=TSOdulvSLL
where (Abs(TSOdulvSRRcheck).ne.0._dp) TSOdulvSRRcheck = (TSOdulvSRRcheck-TSOdulvSRR)/TSOdulvSRRcheck
If(MaxVal(Abs(TSOdulvSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvSRRcheck))
TSOdulvSRRcheck=TSOdulvSRR
where (Abs(TSOdulvSRLcheck).ne.0._dp) TSOdulvSRLcheck = (TSOdulvSRLcheck-TSOdulvSRL)/TSOdulvSRLcheck
If(MaxVal(Abs(TSOdulvSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvSRLcheck))
TSOdulvSRLcheck=TSOdulvSRL
where (Abs(TSOdulvSLRcheck).ne.0._dp) TSOdulvSLRcheck = (TSOdulvSLRcheck-TSOdulvSLR)/TSOdulvSLRcheck
If(MaxVal(Abs(TSOdulvSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvSLRcheck))
TSOdulvSLRcheck=TSOdulvSLR
where (Abs(TSOdulvVRRcheck).ne.0._dp) TSOdulvVRRcheck = (TSOdulvVRRcheck-TSOdulvVRR)/TSOdulvVRRcheck
If(MaxVal(Abs(TSOdulvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvVRRcheck))
TSOdulvVRRcheck=TSOdulvVRR
where (Abs(TSOdulvVLLcheck).ne.0._dp) TSOdulvVLLcheck = (TSOdulvVLLcheck-TSOdulvVLL)/TSOdulvVLLcheck
If(MaxVal(Abs(TSOdulvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvVLLcheck))
TSOdulvVLLcheck=TSOdulvVLL
where (Abs(TSOdulvVRLcheck).ne.0._dp) TSOdulvVRLcheck = (TSOdulvVRLcheck-TSOdulvVRL)/TSOdulvVRLcheck
If(MaxVal(Abs(TSOdulvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvVRLcheck))
TSOdulvVRLcheck=TSOdulvVRL
where (Abs(TSOdulvVLRcheck).ne.0._dp) TSOdulvVLRcheck = (TSOdulvVLRcheck-TSOdulvVLR)/TSOdulvVLRcheck
If(MaxVal(Abs(TSOdulvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOdulvVLRcheck))
TSOdulvVLRcheck=TSOdulvVLR
where (Abs(TVOdulvSLLcheck).ne.0._dp) TVOdulvSLLcheck = (TVOdulvSLLcheck-TVOdulvSLL)/TVOdulvSLLcheck
If(MaxVal(Abs(TVOdulvSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvSLLcheck))
TVOdulvSLLcheck=TVOdulvSLL
where (Abs(TVOdulvSRRcheck).ne.0._dp) TVOdulvSRRcheck = (TVOdulvSRRcheck-TVOdulvSRR)/TVOdulvSRRcheck
If(MaxVal(Abs(TVOdulvSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvSRRcheck))
TVOdulvSRRcheck=TVOdulvSRR
where (Abs(TVOdulvSRLcheck).ne.0._dp) TVOdulvSRLcheck = (TVOdulvSRLcheck-TVOdulvSRL)/TVOdulvSRLcheck
If(MaxVal(Abs(TVOdulvSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvSRLcheck))
TVOdulvSRLcheck=TVOdulvSRL
where (Abs(TVOdulvSLRcheck).ne.0._dp) TVOdulvSLRcheck = (TVOdulvSLRcheck-TVOdulvSLR)/TVOdulvSLRcheck
If(MaxVal(Abs(TVOdulvSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvSLRcheck))
TVOdulvSLRcheck=TVOdulvSLR
where (Abs(TVOdulvVRRcheck).ne.0._dp) TVOdulvVRRcheck = (TVOdulvVRRcheck-TVOdulvVRR)/TVOdulvVRRcheck
If(MaxVal(Abs(TVOdulvVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvVRRcheck))
TVOdulvVRRcheck=TVOdulvVRR
where (Abs(TVOdulvVLLcheck).ne.0._dp) TVOdulvVLLcheck = (TVOdulvVLLcheck-TVOdulvVLL)/TVOdulvVLLcheck
If(MaxVal(Abs(TVOdulvVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvVLLcheck))
TVOdulvVLLcheck=TVOdulvVLL
where (Abs(TVOdulvVRLcheck).ne.0._dp) TVOdulvVRLcheck = (TVOdulvVRLcheck-TVOdulvVRL)/TVOdulvVRLcheck
If(MaxVal(Abs(TVOdulvVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvVRLcheck))
TVOdulvVRLcheck=TVOdulvVRL
where (Abs(TVOdulvVLRcheck).ne.0._dp) TVOdulvVLRcheck = (TVOdulvVLRcheck-TVOdulvVLR)/TVOdulvVLRcheck
If(MaxVal(Abs(TVOdulvVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOdulvVLRcheck))
TVOdulvVLRcheck=TVOdulvVLR
where (Abs(OA2qSLcheck).ne.0._dp) OA2qSLcheck = (OA2qSLcheck-OA2qSL)/OA2qSLcheck
If(MaxVal(Abs(OA2qSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2qSLcheck))
OA2qSLcheck=OA2qSL
where (Abs(OA2qSRcheck).ne.0._dp) OA2qSRcheck = (OA2qSRcheck-OA2qSR)/OA2qSRcheck
If(MaxVal(Abs(OA2qSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2qSRcheck))
OA2qSRcheck=OA2qSR
where (Abs(OA2qVLcheck).ne.0._dp) OA2qVLcheck = (OA2qVLcheck-OA2qVL)/OA2qVLcheck
If(MaxVal(Abs(OA2qVLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2qVLcheck))
OA2qVLcheck=OA2qVL
where (Abs(OA2qVRcheck).ne.0._dp) OA2qVRcheck = (OA2qVRcheck-OA2qVR)/OA2qVRcheck
If(MaxVal(Abs(OA2qVRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2qVRcheck))
OA2qVRcheck=OA2qVR
where (Abs(OG2qSLcheck).ne.0._dp) OG2qSLcheck = (OG2qSLcheck-OG2qSL)/OG2qSLcheck
If(MaxVal(Abs(OG2qSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OG2qSLcheck))
OG2qSLcheck=OG2qSL
where (Abs(OG2qSRcheck).ne.0._dp) OG2qSRcheck = (OG2qSRcheck-OG2qSR)/OG2qSRcheck
If(MaxVal(Abs(OG2qSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OG2qSRcheck))
OG2qSRcheck=OG2qSR
where (Abs(OH2qSLcheck).ne.0._dp) OH2qSLcheck = (OH2qSLcheck-OH2qSL)/OH2qSLcheck
If(MaxVal(Abs(OH2qSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OH2qSLcheck))
OH2qSLcheck=OH2qSL
where (Abs(OH2qSRcheck).ne.0._dp) OH2qSRcheck = (OH2qSRcheck-OH2qSR)/OH2qSRcheck
If(MaxVal(Abs(OH2qSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OH2qSRcheck))
OH2qSRcheck=OH2qSR
If (iQTEST.gt.1) Write(*,*) "Q=",10.0_dp**iQTest," max change=",maxdiff  
If (iQTEST.eq.10) Qin=SetRenormalizationScale(Qinsave) 
End If  
End Do  

! ## SM only ##


 ! **** Box2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,          & 
& MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,           & 
& MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,   & 
& cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,             & 
& cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,   & 
& cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,             & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,         & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,       & 
& cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,         & 
& cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,cplhhcVWmVWm,         & 
& cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,cplhhSvcSv,       & 
& cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSdVP,              & 
& cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,BOddllSLLSM(gt1,gt2,gt3,gt4)& 
& ,BOddllSRRSM(gt1,gt2,gt3,gt4),BOddllSRLSM(gt1,gt2,gt3,gt4),BOddllSLRSM(gt1,gt2,gt3,gt4)& 
& ,BOddllVRRSM(gt1,gt2,gt3,gt4),BOddllVLLSM(gt1,gt2,gt3,gt4),BOddllVRLSM(gt1,gt2,gt3,gt4)& 
& ,BOddllVLRSM(gt1,gt2,gt3,gt4),BOddllTLLSM(gt1,gt2,gt3,gt4),BOddllTLRSM(gt1,gt2,gt3,gt4)& 
& ,BOddllTRLSM(gt1,gt2,gt3,gt4),BOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PSOddllSLLSM(gt1,gt2,gt3,gt4),PSOddllSRRSM(gt1,gt2,gt3,gt4),PSOddllSRLSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllSLRSM(gt1,gt2,gt3,gt4),PSOddllVRRSM(gt1,gt2,gt3,gt4),PSOddllVLLSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllVRLSM(gt1,gt2,gt3,gt4),PSOddllVLRSM(gt1,gt2,gt3,gt4),PSOddllTLLSM(gt1,gt2,gt3,gt4)& 
& ,PSOddllTLRSM(gt1,gt2,gt3,gt4),PSOddllTRLSM(gt1,gt2,gt3,gt4),PSOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PVOddllSLLSM(gt1,gt2,gt3,gt4),PVOddllSRRSM(gt1,gt2,gt3,gt4),PVOddllSRLSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllSLRSM(gt1,gt2,gt3,gt4),PVOddllVRRSM(gt1,gt2,gt3,gt4),PVOddllVLLSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllVRLSM(gt1,gt2,gt3,gt4),PVOddllVLRSM(gt1,gt2,gt3,gt4),PVOddllTLLSM(gt1,gt2,gt3,gt4)& 
& ,PVOddllTLRSM(gt1,gt2,gt3,gt4),PVOddllTRLSM(gt1,gt2,gt3,gt4),PVOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TSOddllSLLSM(gt1,gt2,gt3,gt4),TSOddllSRRSM(gt1,gt2,gt3,gt4),TSOddllSRLSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllSLRSM(gt1,gt2,gt3,gt4),TSOddllVRRSM(gt1,gt2,gt3,gt4),TSOddllVLLSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllVRLSM(gt1,gt2,gt3,gt4),TSOddllVLRSM(gt1,gt2,gt3,gt4),TSOddllTLLSM(gt1,gt2,gt3,gt4)& 
& ,TSOddllTLRSM(gt1,gt2,gt3,gt4),TSOddllTRLSM(gt1,gt2,gt3,gt4),TSOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2L **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,1,2,2/) 
IndexArray4(3,:) = (/3,1,3,3/) 
IndexArray4(4,:) = (/3,2,1,1/) 
IndexArray4(5,:) = (/3,2,2,2/) 
IndexArray4(6,:) = (/3,2,3,3/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2L(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TVOddllSLLSM(gt1,gt2,gt3,gt4),TVOddllSRRSM(gt1,gt2,gt3,gt4),TVOddllSRLSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllSLRSM(gt1,gt2,gt3,gt4),TVOddllVRRSM(gt1,gt2,gt3,gt4),TVOddllVLLSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllVRLSM(gt1,gt2,gt3,gt4),TVOddllVLRSM(gt1,gt2,gt3,gt4),TVOddllTLLSM(gt1,gt2,gt3,gt4)& 
& ,TVOddllTLRSM(gt1,gt2,gt3,gt4),TVOddllTRLSM(gt1,gt2,gt3,gt4),TVOddllTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Box2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,BOddvvVRRSM(gt1,gt2,gt3,gt4)  & 
& ,BOddvvVLLSM(gt1,gt2,gt3,gt4),BOddvvVRLSM(gt1,gt2,gt3,gt4),BOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,PSOddvvVRRSM(gt1,gt2,gt3,gt4) & 
& ,PSOddvvVLLSM(gt1,gt2,gt3,gt4),PSOddvvVRLSM(gt1,gt2,gt3,gt4),PSOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** PengV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,PVOddvvVRRSM(gt1,gt2,gt3,gt4) & 
& ,PVOddvvVLLSM(gt1,gt2,gt3,gt4),PVOddvvVRLSM(gt1,gt2,gt3,gt4),PVOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,TSOddvvVRRSM(gt1,gt2,gt3,gt4) & 
& ,TSOddvvVLLSM(gt1,gt2,gt3,gt4),TSOddvvVRLSM(gt1,gt2,gt3,gt4),TSOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV2d2nu **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,2/) 
IndexArray4(5,:) = (/3,1,1,2/) 
IndexArray4(6,:) = (/3,2,1,2/) 
IndexArray4(7,:) = (/2,1,1,3/) 
IndexArray4(8,:) = (/3,1,1,3/) 
IndexArray4(9,:) = (/3,2,1,3/) 
IndexArray4(10,:) = (/2,1,2,1/) 
IndexArray4(11,:) = (/3,1,2,1/) 
IndexArray4(12,:) = (/3,2,2,1/) 
IndexArray4(13,:) = (/2,1,2,2/) 
IndexArray4(14,:) = (/3,1,2,2/) 
IndexArray4(15,:) = (/3,2,2,2/) 
IndexArray4(16,:) = (/2,1,2,3/) 
IndexArray4(17,:) = (/3,1,2,3/) 
IndexArray4(18,:) = (/3,2,2,3/) 
IndexArray4(19,:) = (/2,1,3,1/) 
IndexArray4(20,:) = (/3,1,3,1/) 
IndexArray4(21,:) = (/3,2,3,1/) 
IndexArray4(22,:) = (/2,1,3,2/) 
IndexArray4(23,:) = (/3,1,3,2/) 
IndexArray4(24,:) = (/3,2,3,2/) 
IndexArray4(25,:) = (/2,1,3,3/) 
IndexArray4(26,:) = (/3,1,3,3/) 
IndexArray4(27,:) = (/3,2,3,3/) 
Do i1=1,27 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2d2nu(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,cplcChacFvSeL,cplcChacFvSeR,  & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,     & 
& cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,             & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,           & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvChiSvL,cplcFvChiSvR,cplcFvFecHpmL,cplcFvFecHpmR,         & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,cplChaFvcSeL,cplChaFvcSeR,         & 
& cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFvcSvL,cplChiFvcSvR,         & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,TVOddvvVRRSM(gt1,gt2,gt3,gt4) & 
& ,TVOddvvVLLSM(gt1,gt2,gt3,gt4),TVOddvvVRLSM(gt1,gt2,gt3,gt4),TVOddvvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Box4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,            & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& BO4dSLLSM(gt1,gt2,gt3,gt4),BO4dSRRSM(gt1,gt2,gt3,gt4),BO4dSRLSM(gt1,gt2,gt3,gt4)       & 
& ,BO4dSLRSM(gt1,gt2,gt3,gt4),BO4dVRRSM(gt1,gt2,gt3,gt4),BO4dVLLSM(gt1,gt2,gt3,gt4)      & 
& ,BO4dVRLSM(gt1,gt2,gt3,gt4),BO4dVLRSM(gt1,gt2,gt3,gt4),BO4dTLLSM(gt1,gt2,gt3,gt4)      & 
& ,BO4dTLRSM(gt1,gt2,gt3,gt4),BO4dTRLSM(gt1,gt2,gt3,gt4),BO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeS4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,          & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& TSO4dSLLSM(gt1,gt2,gt3,gt4),TSO4dSRRSM(gt1,gt2,gt3,gt4),TSO4dSRLSM(gt1,gt2,gt3,gt4)    & 
& ,TSO4dSLRSM(gt1,gt2,gt3,gt4),TSO4dVRRSM(gt1,gt2,gt3,gt4),TSO4dVLLSM(gt1,gt2,gt3,gt4)   & 
& ,TSO4dVRLSM(gt1,gt2,gt3,gt4),TSO4dVLRSM(gt1,gt2,gt3,gt4),TSO4dTLLSM(gt1,gt2,gt3,gt4)   & 
& ,TSO4dTLRSM(gt1,gt2,gt3,gt4),TSO4dTRLSM(gt1,gt2,gt3,gt4),TSO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeV4d **** 
 
IndexArray4(1,:) = (/3,1,3,1/) 
IndexArray4(2,:) = (/3,2,3,2/) 
IndexArray4(3,:) = (/2,1,2,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4d(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,          & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,             & 
& cplAhSdcSd,cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,         & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,   & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVGL,cplcFuFuVGR,               & 
& cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplChiChiAhL,cplChiChiAhR,             & 
& cplChiChihhL,cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,         & 
& cplcHpmVPVWm,cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,         & 
& cplGluGluVGL,cplGluGluVGR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,   & 
& cplHpmcVWmVZ,cplSdcSdVG,cplSdcSdVP,cplSdcSdVZ,cplSucSuVG,cplSucSuVP,cplSucSuVZ,        & 
& TVO4dSLLSM(gt1,gt2,gt3,gt4),TVO4dSRRSM(gt1,gt2,gt3,gt4),TVO4dSRLSM(gt1,gt2,gt3,gt4)    & 
& ,TVO4dSLRSM(gt1,gt2,gt3,gt4),TVO4dVRRSM(gt1,gt2,gt3,gt4),TVO4dVLLSM(gt1,gt2,gt3,gt4)   & 
& ,TVO4dVRLSM(gt1,gt2,gt3,gt4),TVO4dVLRSM(gt1,gt2,gt3,gt4),TVO4dTLLSM(gt1,gt2,gt3,gt4)   & 
& ,TVO4dTLRSM(gt1,gt2,gt3,gt4),TVO4dTRLSM(gt1,gt2,gt3,gt4),TVO4dTRRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** A2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateA2q(gt1,gt2,gt3,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,              & 
& MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,MVWm2,             & 
& MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,        & 
& cplAhSucSu,cplcChaChaAhL,cplcChaChaAhR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,       & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,      & 
& cplcFuFuAhR,cplChiChiAhL,cplChiChiAhR,cplChiFdcSdL,cplChiFdcSdR,cplGluFdcSdL,          & 
& cplGluFdcSdR,OAh2qSLSM(gt1,gt2,gt3),OAh2qSRSM(gt1,gt2,gt3))

 End Do  
End do 



 ! **** TreeSdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeSdulv(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,     & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,         & 
& cplHpmcVWmVZ,cplHpmSvcSe,cplSdcHpmcSu,cplSdcSucVWm,cplSvcSeVWm,TSOdulvSLLSM(gt1,gt2,gt3,gt4)& 
& ,TSOdulvSRRSM(gt1,gt2,gt3,gt4),TSOdulvSRLSM(gt1,gt2,gt3,gt4),TSOdulvSLRSM(gt1,gt2,gt3,gt4)& 
& ,TSOdulvVRRSM(gt1,gt2,gt3,gt4),TSOdulvVLLSM(gt1,gt2,gt3,gt4),TSOdulvVRLSM(gt1,gt2,gt3,gt4)& 
& ,TSOdulvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** TreeVdulv **** 
 
IndexArray4(1,:) = (/3,1,1,1/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/2,2,1,1/) 
IndexArray4(4,:) = (/2,1,1,1/) 
IndexArray4(5,:) = (/1,2,1,1/) 
IndexArray4(6,:) = (/3,1,1,2/) 
IndexArray4(7,:) = (/3,2,1,2/) 
IndexArray4(8,:) = (/2,2,1,2/) 
IndexArray4(9,:) = (/2,1,1,2/) 
IndexArray4(10,:) = (/1,2,1,2/) 
IndexArray4(11,:) = (/3,1,1,3/) 
IndexArray4(12,:) = (/3,2,1,3/) 
IndexArray4(13,:) = (/2,2,1,3/) 
IndexArray4(14,:) = (/2,1,1,3/) 
IndexArray4(15,:) = (/1,2,1,3/) 
IndexArray4(16,:) = (/3,1,2,1/) 
IndexArray4(17,:) = (/3,2,2,1/) 
IndexArray4(18,:) = (/2,2,2,1/) 
IndexArray4(19,:) = (/2,1,2,1/) 
IndexArray4(20,:) = (/1,2,2,1/) 
IndexArray4(21,:) = (/3,1,2,2/) 
IndexArray4(22,:) = (/3,2,2,2/) 
IndexArray4(23,:) = (/2,2,2,2/) 
IndexArray4(24,:) = (/2,1,2,2/) 
IndexArray4(25,:) = (/1,2,2,2/) 
IndexArray4(26,:) = (/3,1,2,3/) 
IndexArray4(27,:) = (/3,2,2,3/) 
IndexArray4(28,:) = (/2,2,2,3/) 
IndexArray4(29,:) = (/2,1,2,3/) 
IndexArray4(30,:) = (/1,2,2,3/) 
IndexArray4(31,:) = (/3,1,3,1/) 
IndexArray4(32,:) = (/3,2,3,1/) 
IndexArray4(33,:) = (/2,2,3,1/) 
IndexArray4(34,:) = (/2,1,3,1/) 
IndexArray4(35,:) = (/1,2,3,1/) 
IndexArray4(36,:) = (/3,1,3,2/) 
IndexArray4(37,:) = (/3,2,3,2/) 
IndexArray4(38,:) = (/2,2,3,2/) 
IndexArray4(39,:) = (/2,1,3,2/) 
IndexArray4(40,:) = (/1,2,3,2/) 
IndexArray4(41,:) = (/3,1,3,3/) 
IndexArray4(42,:) = (/3,2,3,3/) 
IndexArray4(43,:) = (/2,2,3,3/) 
IndexArray4(44,:) = (/2,1,3,3/) 
IndexArray4(45,:) = (/1,2,3,3/) 
Do i1=1,45 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeVdulv(gt1,gt2,gt3,gt4,.true.,MAh,MAh2,MCha,MCha2,MChi,              & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhcHpmVWm,cplAhHpmcHpm,              & 
& cplAhHpmcVWm,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,cplcChacFvSeR,cplcChaChiHpmL,   & 
& cplcChaChiHpmR,cplcChaChiVWmL,cplcChaChiVWmR,cplcChaFdcSuL,cplcChaFdcSuR,              & 
& cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,       & 
& cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,         & 
& cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,               & 
& cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,               & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,cplcFuGluSuR,cplcFvChiSvL,cplcFvChiSvR,           & 
& cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,       & 
& cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplChiChacHpmL,cplChiChacHpmR,     & 
& cplChiChacVWmL,cplChiChacVWmR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,     & 
& cplChiFucSuL,cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcHpmVPVWm,cplcHpmVWmVZ,         & 
& cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhHpmcHpm,cplhhHpmcVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,         & 
& cplHpmcVWmVZ,cplHpmSvcSe,cplSdcHpmcSu,cplSdcSucVWm,cplSvcSeVWm,TVOdulvSLLSM(gt1,gt2,gt3,gt4)& 
& ,TVOdulvSRRSM(gt1,gt2,gt3,gt4),TVOdulvSRLSM(gt1,gt2,gt3,gt4),TVOdulvSLRSM(gt1,gt2,gt3,gt4)& 
& ,TVOdulvVRRSM(gt1,gt2,gt3,gt4),TVOdulvVLLSM(gt1,gt2,gt3,gt4),TVOdulvVRLSM(gt1,gt2,gt3,gt4)& 
& ,TVOdulvVLRSM(gt1,gt2,gt3,gt4))

End do 



 ! **** Gamma2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2Q(gt1,gt2,gt3,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,              & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplcChaChaVPL,cplcChaChaVPR,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,   & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVPL,      & 
& cplcFuFuVPR,cplChiFdcSdL,cplChiFdcSdR,cplcHpmVPVWm,cplcVWmVPVWm,cplGluFdcSdL,          & 
& cplGluFdcSdR,cplHpmcHpmVP,cplHpmcVWmVP,cplSdcSdVP,cplSucSuVP,OA2qSLSM(gt1,gt2)         & 
& ,OA2qSRSM(gt1,gt2),OA2qVLSM(gt1,gt2),OA2qVRSM(gt1,gt2))

End do 



 ! **** Gluon2Q **** 
 
IndexArray2(1,:) = (/3,2/) 
Do i1=1,1 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGluon2Q(gt1,gt2,gt3,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,              & 
& MFd,MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,               & 
& MVWm2,MVZ,MVZ2,cplcChaFdcSuL,cplcChaFdcSuR,cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,              & 
& cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuVGL,cplcFuFuVGR,cplChiFdcSdL,        & 
& cplChiFdcSdR,cplGluFdcSdL,cplGluFdcSdR,cplGluGluVGL,cplGluGluVGR,cplSdcSdVG,           & 
& cplSucSuVG,OG2qSLSM(gt1,gt2),OG2qSRSM(gt1,gt2))

End do 



 ! **** H2q **** 
 
IndexArray3(1,:) = (/2,1,1/) 
IndexArray3(2,:) = (/3,1,1/) 
IndexArray3(3,:) = (/3,2,1/) 
Do i1=1,3 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2q(gt1,gt2,gt3,.true.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,              & 
& MFd2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSu,MSu2,MVWm,MVWm2,             & 
& MVZ,MVZ2,cplAhAhhh,cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaFdcSuL,cplcChaFdcSuR,  & 
& cplcFdChaSuL,cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,           & 
& cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,               & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,           & 
& cplcFdGluSdL,cplcFdGluSdR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,     & 
& cplcFuFuhhL,cplcFuFuhhR,cplChiChihhL,cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,           & 
& cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,            & 
& cplhhHpmcVWm,cplhhSdcSd,cplhhSucSu,cplhhVZVZ,OH2qSLSM(gt1,gt2,gt3),OH2qSRSM(gt1,gt2,gt3))

 End Do  
End do 



 ! ***** Combine operators for 2d2L
OddllSLL = BOddllSLL + PSOddllSLL + PVOddllSLL + TSOddllSLL + TVOddllSLL
OddllSLLSM = BOddllSLLSM + PSOddllSLLSM + PVOddllSLLSM + TSOddllSLLSM + TVOddllSLLSM
OddllSRR = BOddllSRR + PSOddllSRR + PVOddllSRR + TSOddllSRR + TVOddllSRR
OddllSRRSM = BOddllSRRSM + PSOddllSRRSM + PVOddllSRRSM + TSOddllSRRSM + TVOddllSRRSM
OddllSRL = BOddllSRL + PSOddllSRL + PVOddllSRL + TSOddllSRL + TVOddllSRL
OddllSRLSM = BOddllSRLSM + PSOddllSRLSM + PVOddllSRLSM + TSOddllSRLSM + TVOddllSRLSM
OddllSLR = BOddllSLR + PSOddllSLR + PVOddllSLR + TSOddllSLR + TVOddllSLR
OddllSLRSM = BOddllSLRSM + PSOddllSLRSM + PVOddllSLRSM + TSOddllSLRSM + TVOddllSLRSM
OddllVRR = BOddllVRR + PSOddllVRR + PVOddllVRR + TSOddllVRR + TVOddllVRR
OddllVRRSM = BOddllVRRSM + PSOddllVRRSM + PVOddllVRRSM + TSOddllVRRSM + TVOddllVRRSM
OddllVLL = BOddllVLL + PSOddllVLL + PVOddllVLL + TSOddllVLL + TVOddllVLL
OddllVLLSM = BOddllVLLSM + PSOddllVLLSM + PVOddllVLLSM + TSOddllVLLSM + TVOddllVLLSM
OddllVRL = BOddllVRL + PSOddllVRL + PVOddllVRL + TSOddllVRL + TVOddllVRL
OddllVRLSM = BOddllVRLSM + PSOddllVRLSM + PVOddllVRLSM + TSOddllVRLSM + TVOddllVRLSM
OddllVLR = BOddllVLR + PSOddllVLR + PVOddllVLR + TSOddllVLR + TVOddllVLR
OddllVLRSM = BOddllVLRSM + PSOddllVLRSM + PVOddllVLRSM + TSOddllVLRSM + TVOddllVLRSM
OddllTLL = BOddllTLL + PSOddllTLL + PVOddllTLL + TSOddllTLL + TVOddllTLL
OddllTLLSM = BOddllTLLSM + PSOddllTLLSM + PVOddllTLLSM + TSOddllTLLSM + TVOddllTLLSM
OddllTLR = BOddllTLR + PSOddllTLR + PVOddllTLR + TSOddllTLR + TVOddllTLR
OddllTLRSM = BOddllTLRSM + PSOddllTLRSM + PVOddllTLRSM + TSOddllTLRSM + TVOddllTLRSM
OddllTRL = BOddllTRL + PSOddllTRL + PVOddllTRL + TSOddllTRL + TVOddllTRL
OddllTRLSM = BOddllTRLSM + PSOddllTRLSM + PVOddllTRLSM + TSOddllTRLSM + TVOddllTRLSM
OddllTRR = BOddllTRR + PSOddllTRR + PVOddllTRR + TSOddllTRR + TVOddllTRR
OddllTRRSM = BOddllTRRSM + PSOddllTRRSM + PVOddllTRRSM + TSOddllTRRSM + TVOddllTRRSM

 ! ***** Combine operators for 2d2nu
OddvvVRR = BOddvvVRR + PSOddvvVRR + PVOddvvVRR + TSOddvvVRR + TVOddvvVRR
OddvvVRRSM = BOddvvVRRSM + PSOddvvVRRSM + PVOddvvVRRSM + TSOddvvVRRSM + TVOddvvVRRSM
OddvvVLL = BOddvvVLL + PSOddvvVLL + PVOddvvVLL + TSOddvvVLL + TVOddvvVLL
OddvvVLLSM = BOddvvVLLSM + PSOddvvVLLSM + PVOddvvVLLSM + TSOddvvVLLSM + TVOddvvVLLSM
OddvvVRL = BOddvvVRL + PSOddvvVRL + PVOddvvVRL + TSOddvvVRL + TVOddvvVRL
OddvvVRLSM = BOddvvVRLSM + PSOddvvVRLSM + PVOddvvVRLSM + TSOddvvVRLSM + TVOddvvVRLSM
OddvvVLR = BOddvvVLR + PSOddvvVLR + PVOddvvVLR + TSOddvvVLR + TVOddvvVLR
OddvvVLRSM = BOddvvVLRSM + PSOddvvVLRSM + PVOddvvVLRSM + TSOddvvVLRSM + TVOddvvVLRSM

 ! ***** Combine operators for 4d
O4dSLL = BO4dSLL + TSO4dSLL + TVO4dSLL
O4dSLLSM = BO4dSLLSM + TSO4dSLLSM + TVO4dSLLSM
O4dSRR = BO4dSRR + TSO4dSRR + TVO4dSRR
O4dSRRSM = BO4dSRRSM + TSO4dSRRSM + TVO4dSRRSM
O4dSRL = BO4dSRL + TSO4dSRL + TVO4dSRL
O4dSRLSM = BO4dSRLSM + TSO4dSRLSM + TVO4dSRLSM
O4dSLR = BO4dSLR + TSO4dSLR + TVO4dSLR
O4dSLRSM = BO4dSLRSM + TSO4dSLRSM + TVO4dSLRSM
O4dVRR = BO4dVRR + TSO4dVRR + TVO4dVRR
O4dVRRSM = BO4dVRRSM + TSO4dVRRSM + TVO4dVRRSM
O4dVLL = BO4dVLL + TSO4dVLL + TVO4dVLL
O4dVLLSM = BO4dVLLSM + TSO4dVLLSM + TVO4dVLLSM
O4dVRL = BO4dVRL + TSO4dVRL + TVO4dVRL
O4dVRLSM = BO4dVRLSM + TSO4dVRLSM + TVO4dVRLSM
O4dVLR = BO4dVLR + TSO4dVLR + TVO4dVLR
O4dVLRSM = BO4dVLRSM + TSO4dVLRSM + TVO4dVLRSM
O4dTLL = BO4dTLL + TSO4dTLL + TVO4dTLL
O4dTLLSM = BO4dTLLSM + TSO4dTLLSM + TVO4dTLLSM
O4dTLR = BO4dTLR + TSO4dTLR + TVO4dTLR
O4dTLRSM = BO4dTLRSM + TSO4dTLRSM + TVO4dTLRSM
O4dTRL = BO4dTRL + TSO4dTRL + TVO4dTRL
O4dTRLSM = BO4dTRLSM + TSO4dTRLSM + TVO4dTRLSM
O4dTRR = BO4dTRR + TSO4dTRR + TVO4dTRR
O4dTRRSM = BO4dTRRSM + TSO4dTRRSM + TVO4dTRRSM

 ! ***** Combine operators for dulv
OdulvSLL = TSOdulvSLL + TVOdulvSLL
OdulvSLLSM = TSOdulvSLLSM + TVOdulvSLLSM
OdulvSRR = TSOdulvSRR + TVOdulvSRR
OdulvSRRSM = TSOdulvSRRSM + TVOdulvSRRSM
OdulvSRL = TSOdulvSRL + TVOdulvSRL
OdulvSRLSM = TSOdulvSRLSM + TVOdulvSRLSM
OdulvSLR = TSOdulvSLR + TVOdulvSLR
OdulvSLRSM = TSOdulvSLRSM + TVOdulvSLRSM
OdulvVRR = TSOdulvVRR + TVOdulvVRR
OdulvVRRSM = TSOdulvVRRSM + TVOdulvVRRSM
OdulvVLL = TSOdulvVLL + TVOdulvVLL
OdulvVLLSM = TSOdulvVLLSM + TVOdulvVLLSM
OdulvVRL = TSOdulvVRL + TVOdulvVRL
OdulvVRLSM = TSOdulvVRLSM + TVOdulvVRLSM
OdulvVLR = TSOdulvVLR + TVOdulvVLR
OdulvVLRSM = TSOdulvVLRSM + TVOdulvVLRSM

 ! ***** Combine operators for Gluon2Q
CC8 = OG2qSL
CC8SM = OG2qSLSM 
CC8p = OG2qSR
CC8pSM = OG2qSRSM 
CC8(2,:) = -0.25_dp*CC8(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8(3,:) = -0.25_dp*CC8(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8p(2,:) = -0.25_dp*CC8p(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8p(3,:) = -0.25_dp*CC8p(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8SM(2,:) = -0.25_dp*CC8SM(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8SM(3,:) = -0.25_dp*CC8SM(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)
CC8pSM(2,:) = -0.25_dp*CC8pSM(2,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(2)
CC8pSM(3,:) = -0.25_dp*CC8pSM(3,:)/sqrt(AlphaS_160*4*Pi)/mf_d_160(3)

 ! ***** Combine operators for Gamma2Q
CC7 = OA2qSL
CC7SM = OA2qSLSM 
CC7p = OA2qSR
CC7pSM = OA2qSRSM 
CC7(2,:) = -0.25_dp*CC7(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7(3,:) = -0.25_dp*CC7(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7p(2,:) = -0.25_dp*CC7p(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7p(3,:) = -0.25_dp*CC7p(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7SM(2,:) = -0.25_dp*CC7SM(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7SM(3,:) = -0.25_dp*CC7SM(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)
CC7pSM(2,:) = -0.25_dp*CC7pSM(2,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(2)
CC7pSM(3,:) = -0.25_dp*CC7pSM(3,:)/sqrt(Alpha_160*4*Pi)/mf_d_160(3)

 ! **** B0toLL **** 
 
Call Calculate_B0toLL(OddllSLL,OddllSRR,OddllSRL,OddllSLR,OddllVRR,OddllVLL,          & 
& OddllVRL,OddllVLR,OddllSLLSM,OddllSRRSM,OddllSRLSM,OddllSLRSM,OddllVRRSM,              & 
& OddllVLLSM,OddllVRLSM,OddllVLRSM,BrB0dEE,ratioB0dEE,BrB0sEE,ratioB0sEE,BrB0dMuMu,      & 
& ratioB0dMuMu,BrB0sMuMu,ratioB0sMuMu,BrB0dTauTau,ratioB0dTauTau,BrB0sTauTau,            & 
& ratioB0sTauTau)

If(BrB0dEE.ne.BrB0dEE) BrB0dEE = 0._dp 
If(ratioB0dEE.ne.ratioB0dEE) ratioB0dEE = 0._dp 
If(BrB0sEE.ne.BrB0sEE) BrB0sEE = 0._dp 
If(ratioB0sEE.ne.ratioB0sEE) ratioB0sEE = 0._dp 
If(BrB0dMuMu.ne.BrB0dMuMu) BrB0dMuMu = 0._dp 
If(ratioB0dMuMu.ne.ratioB0dMuMu) ratioB0dMuMu = 0._dp 
If(BrB0sMuMu.ne.BrB0sMuMu) BrB0sMuMu = 0._dp 
If(ratioB0sMuMu.ne.ratioB0sMuMu) ratioB0sMuMu = 0._dp 
If(BrB0dTauTau.ne.BrB0dTauTau) BrB0dTauTau = 0._dp 
If(ratioB0dTauTau.ne.ratioB0dTauTau) ratioB0dTauTau = 0._dp 
If(BrB0sTauTau.ne.BrB0sTauTau) BrB0sTauTau = 0._dp 
If(ratioB0sTauTau.ne.ratioB0sTauTau) ratioB0sTauTau = 0._dp 

 ! **** bsGamma **** 
 
Call Calculate_bsGamma(CC7,CC7p,CC8,CC8p,CC7SM,CC7pSM,CC8SM,CC8pSM,BrBsGamma,         & 
& ratioBsGamma)

If(BrBsGamma.ne.BrBsGamma) BrBsGamma = 0._dp 
If(ratioBsGamma.ne.ratioBsGamma) ratioBsGamma = 0._dp 

 ! **** BtoKLL **** 
 
Call Calculate_BtoKLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,OddllVRRSM,        & 
& OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,BrBtoKmumu,ratioBtoKmumu)

If(BrBtoKmumu.ne.BrBtoKmumu) BrBtoKmumu = 0._dp 
If(ratioBtoKmumu.ne.ratioBtoKmumu) ratioBtoKmumu = 0._dp 

 ! **** BtoQnunu **** 
 
Call Calculate_BtoQnunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,               & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrBtoSnunu,ratioBtoSnunu,BrBtoDnunu,ratioBtoDnunu)

If(BrBtoSnunu.ne.BrBtoSnunu) BrBtoSnunu = 0._dp 
If(ratioBtoSnunu.ne.ratioBtoSnunu) ratioBtoSnunu = 0._dp 
If(BrBtoDnunu.ne.BrBtoDnunu) BrBtoDnunu = 0._dp 
If(ratioBtoDnunu.ne.ratioBtoDnunu) ratioBtoDnunu = 0._dp 

 ! **** BtoSLL **** 
 
Call Calculate_BtoSLL(OddllVRR,OddllVLL,OddllVRL,OddllVLR,CC7,CC7p,CC8,               & 
& CC8p,OddllVRRSM,OddllVLLSM,OddllVRLSM,OddllVLRSM,CC7SM,CC7pSM,CC8SM,CC8pSM,            & 
& BrBtoSEE,ratioBtoSEE,BrBtoSMuMu,ratioBtoSMuMu)

If(BrBtoSEE.ne.BrBtoSEE) BrBtoSEE = 0._dp 
If(ratioBtoSEE.ne.ratioBtoSEE) ratioBtoSEE = 0._dp 
If(BrBtoSMuMu.ne.BrBtoSMuMu) BrBtoSMuMu = 0._dp 
If(ratioBtoSMuMu.ne.ratioBtoSMuMu) ratioBtoSMuMu = 0._dp 

 ! **** DeltaMBq **** 
 
Call Calculate_DeltaMBq(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,O4dVLLSM,           & 
& O4dVRL,O4dVLR,O4dTLL,O4dTLR,O4dTRL,O4dTRR,OH2qSL,OH2qSR,OAh2qSL,OAh2qSR,               & 
& DeltaMBs,ratioDeltaMBs,DeltaMBq,ratioDeltaMBq)

If(DeltaMBs.ne.DeltaMBs) DeltaMBs = 0._dp 
If(ratioDeltaMBs.ne.ratioDeltaMBs) ratioDeltaMBs = 0._dp 
If(DeltaMBq.ne.DeltaMBq) DeltaMBq = 0._dp 
If(ratioDeltaMBq.ne.ratioDeltaMBq) ratioDeltaMBq = 0._dp 

 ! **** KKmix **** 
 
Call Calculate_KKmix(O4dSLL,O4dSRR,O4dSRL,O4dSLR,O4dVRR,O4dVLL,O4dVRL,O4dVLR,         & 
& O4dTLL,O4dTLR,O4dTRL,O4dTRR,O4dSLLSM,O4dSRRSM,O4dSRLSM,O4dSLRSM,O4dVRRSM,              & 
& O4dVLLSM,O4dVRLSM,O4dVLRSM,O4dTLLSM,O4dTLRSM,O4dTRLSM,O4dTRRSM,DelMK,ratioDelMK,       & 
& epsK,ratioepsK)

If(DelMK.ne.DelMK) DelMK = 0._dp 
If(ratioDelMK.ne.ratioDelMK) ratioDelMK = 0._dp 
If(epsK.ne.epsK) epsK = 0._dp 
If(ratioepsK.ne.ratioepsK) ratioepsK = 0._dp 

 ! **** KtoPInunu **** 
 
Call Calculate_KtoPInunu(OddvvVRR,OddvvVLL,OddvvVRL,OddvvVLR,OddvvVRRSM,              & 
& OddvvVLLSM,OddvvVRLSM,OddvvVLRSM,BrKptoPipnunu,ratioKptoPipnunu,BrKltoPinunu,          & 
& ratioKltoPinunu)

If(BrKptoPipnunu.ne.BrKptoPipnunu) BrKptoPipnunu = 0._dp 
If(ratioKptoPipnunu.ne.ratioKptoPipnunu) ratioKptoPipnunu = 0._dp 
If(BrKltoPinunu.ne.BrKltoPinunu) BrKltoPinunu = 0._dp 
If(ratioKltoPinunu.ne.ratioKltoPinunu) ratioKltoPinunu = 0._dp 

 ! **** Plnu **** 
 
Call Calculate_Plnu(OdulvSLL,OdulvSRR,OdulvSRL,OdulvSLR,OdulvVRR,OdulvVLL,            & 
& OdulvVRL,OdulvVLR,OdulvSLLSM,OdulvSRRSM,OdulvSRLSM,OdulvSLRSM,OdulvVRRSM,              & 
& OdulvVLLSM,OdulvVRLSM,OdulvVLRSM,BrDmunu,ratioDmunu,BrDsmunu,ratioDsmunu,              & 
& BrDstaunu,ratioDstaunu,BrBmunu,ratioBmunu,BrBtaunu,ratioBtaunu,BrKmunu,ratioKmunu,RK,RKSM)

If(BrDmunu.ne.BrDmunu) BrDmunu = 0._dp 
If(ratioDmunu.ne.ratioDmunu) ratioDmunu = 0._dp 
If(BrDsmunu.ne.BrDsmunu) BrDsmunu = 0._dp 
If(ratioDsmunu.ne.ratioDsmunu) ratioDsmunu = 0._dp 
If(BrDstaunu.ne.BrDstaunu) BrDstaunu = 0._dp 
If(ratioDstaunu.ne.ratioDstaunu) ratioDstaunu = 0._dp 
If(BrBmunu.ne.BrBmunu) BrBmunu = 0._dp 
If(ratioBmunu.ne.ratioBmunu) ratioBmunu = 0._dp 
If(BrBtaunu.ne.BrBtaunu) BrBtaunu = 0._dp 
If(ratioBtaunu.ne.ratioBtaunu) ratioBtaunu = 0._dp 
If(BrKmunu.ne.BrKmunu) BrKmunu = 0._dp 
If(ratioKmunu.ne.ratioKmunu) ratioKmunu = 0._dp 
If(RK.ne.RK) RK = 0._dp 
If(RKSM.ne.RKSM) RKSM = 0._dp 
coeffC7sm = CC7SM(3,2)
coeffC7 = CC7(3,2)
coeffC7p = CC7p(3,2)
coeffC7NP = CC7(3,2) - CC7SM(3,2)
coeffC7pNP = CC7p(3,2)
coeffC8sm = CC8SM(3,2)
coeffC8 = CC8(3,2)
coeffC8p = CC8p(3,2)
coeffC8NP = CC8(3,2) - CC8SM(3,2)
coeffC8pNP = CC8p(3,2)
coeffC9eeSM = (OddllVLLSM(3,2,1,1) + OddllVLRSM(3,2,1,1))/2._dp
coeffC9ee = (OddllVLL(3,2,1,1) + OddllVLR(3,2,1,1))/2._dp
coeffC9Pee = (OddllVRL(3,2,1,1) + OddllVRR(3,2,1,1))/2._dp
coeffC9eeNP = (OddllVLL(3,2,1,1) - OddllVLLSM(3,2,1,1) + OddllVLR(3,2,1,1) - OddllVLRSM(3,2,1,1))/2._dp
coeffC9PeeNP = (OddllVRL(3,2,1,1) + OddllVRR(3,2,1,1))/2._dp
coeffC10eeSM = (-OddllVLLSM(3,2,1,1) + OddllVLRSM(3,2,1,1))/2._dp
coeffC10ee = (-OddllVLL(3,2,1,1) + OddllVLR(3,2,1,1))/2._dp
coeffC10Pee = (OddllVRL(3,2,1,1) - OddllVRR(3,2,1,1))/2._dp
coeffC10eeNP = (-OddllVLL(3,2,1,1) + OddllVLLSM(3,2,1,1) + OddllVLR(3,2,1,1) - OddllVLRSM(3,2,1,1))/2._dp
coeffC10PeeNP = (OddllVRL(3,2,1,1) - OddllVRR(3,2,1,1))/2._dp
coeffC9mumuSM = (OddllVLLSM(3,2,2,2) + OddllVLRSM(3,2,2,2))/2._dp
coeffC9mumu = (OddllVLL(3,2,2,2) + OddllVLR(3,2,2,2))/2._dp
coeffC9Pmumu = (OddllVRL(3,2,2,2) + OddllVRR(3,2,2,2))/2._dp
coeffC9mumuNP = (OddllVLL(3,2,2,2) - OddllVLLSM(3,2,2,2) + OddllVLR(3,2,2,2) - OddllVLRSM(3,2,2,2))/2._dp
coeffC9PmumuNP = (OddllVRL(3,2,2,2) + OddllVRR(3,2,2,2))/2._dp
coeffC10mumuSM = (-OddllVLLSM(3,2,2,2) + OddllVLRSM(3,2,2,2))/2._dp
coeffC10mumu = (-OddllVLL(3,2,2,2) + OddllVLR(3,2,2,2))/2._dp
coeffC10Pmumu = (OddllVRL(3,2,2,2) - OddllVRR(3,2,2,2))/2._dp
coeffC10mumuNP = (-OddllVLL(3,2,2,2) + OddllVLLSM(3,2,2,2) + OddllVLR(3,2,2,2) - OddllVLRSM(3,2,2,2))/2._dp
coeffC10PmumuNP = (OddllVRL(3,2,2,2) - OddllVRR(3,2,2,2))/2._dp
coeffCLnu1nu1SM = OddvvVLLSM(3,2,1,1)
coeffCLnu1nu1 = OddvvVLL(3,2,1,1)
coeffCLPnu1nu1 = OddvvVRL(3,2,1,1)
coeffCLnu1nu1NP = OddvvVLL(3,2,1,1) - OddvvVLLSM(3,2,1,1)
coeffCLPnu1nu1NP = OddvvVRL(3,2,1,1)
coeffCLnu2nu2SM = OddvvVLLSM(3,2,2,2)
coeffCLnu2nu2 = OddvvVLL(3,2,2,2)
coeffCLPnu2nu2 = OddvvVRL(3,2,2,2)
coeffCLnu2nu2NP = OddvvVLL(3,2,2,2) - OddvvVLLSM(3,2,2,2)
coeffCLPnu2nu2NP = OddvvVRL(3,2,2,2)
coeffCLnu3nu3SM = OddvvVLLSM(3,2,3,3)
coeffCLnu3nu3 = OddvvVLL(3,2,3,3)
coeffCLPnu3nu3 = OddvvVRL(3,2,3,3)
coeffCLnu3nu3NP = OddvvVLL(3,2,3,3) - OddvvVLLSM(3,2,3,3)
coeffCLPnu3nu3NP = OddvvVRL(3,2,3,3)
coeffCRnu1nu1SM = 0
coeffCRnu1nu1 = OddvvVLR(3,2,1,1)
coeffCRPnu1nu1 = OddvvVRR(3,2,1,1)
coeffCRnu1nu1NP = OddvvVLR(3,2,1,1)
coeffCRPnu1nu1NP = OddvvVRR(3,2,1,1)
coeffCRnu2nu2SM = 0
coeffCRnu2nu2 = OddvvVLR(3,2,2,2)
coeffCRPnu2nu2 = OddvvVRR(3,2,2,2)
coeffCRnu2nu2NP = OddvvVLR(3,2,2,2)
coeffCRPnu2nu2NP = OddvvVRR(3,2,2,2)
coeffCRnu3nu3SM = 0
coeffCRnu3nu3 = OddvvVLR(3,2,3,3)
coeffCRPnu3nu3 = OddvvVRR(3,2,3,3)
coeffCRnu3nu3NP = OddvvVLR(3,2,3,3)
coeffCRPnu3nu3NP = OddvvVRR(3,2,3,3)
CKM = CKMsave 
!-------------------------------------
! running to M_Z 
!-------------------------------------

Call RunSM_and_SUSY_RGEs(mz,g1input,g2input,g3input,Ydinput,Yeinput,Yuinput,          & 
& Muinput,Tdinput,Teinput,Tuinput,Bmuinput,mq2input,ml2input,mHd2input,mHu2input,        & 
& md2input,mu2input,me2input,M1input,M2input,M3input,vdinput,vuinput,g1,g2,              & 
& g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,              & 
& CKM_MZ,sinW2_MZ,Alpha_MZ,AlphaS_MZ,.true.)

Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,GenerationMixing,kont)

mzsave  = sqrt(mz2) 
mZ2 = 1._dp/4._dp*(g1**2 + g2**2)*( vd**2 + vu**2) 
mZ = sqrt(mZ2) 
 mf_d_mz = MFd(1:3) 
 mf_d2_mz = MFd(1:3)**2 
 mf_u_mz = MFu(1:3) 
 mf_u2_mz = MFu(1:3)**2 
 mf_l_MZ = MFe(1:3) 
 mf_l2_MZ = MFe(1:3)**2 
Call AllCouplings(g1,g2,vd,vu,ZH,ZA,ZP,Mu,Yd,Td,ZD,Ye,Te,ZE,Yu,Tu,ZU,ZV,              & 
& TW,g3,UM,UP,ZN,ZDL,ZDR,ZEL,ZER,ZUL,ZUR,pG,cplAhAhhh,cplAhHpmcHpm,cplAhSdcSd,           & 
& cplAhSecSe,cplAhSucSu,cplhhhhhh,cplhhHpmcHpm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,         & 
& cplhhSvcSv,cplHpmSucSd,cplHpmSvcSe,cplSdcHpmcSu,cplSecHpmcSv,cplAhhhVZ,cplAhHpmcVWm,   & 
& cplAhcHpmVWm,cplhhHpmcVWm,cplhhcHpmVWm,cplHpmcHpmVP,cplHpmcHpmVZ,cplSdcSdVG,           & 
& cplSdcSdVP,cplSdcSdVZ,cplSdcSucVWm,cplSecSeVP,cplSecSeVZ,cplSecSvcVWm,cplSucSuVG,      & 
& cplSucSuVP,cplSucSdVWm,cplSucSuVZ,cplSvcSeVWm,cplSvcSvVZ,cplhhcVWmVWm,cplhhVZVZ,       & 
& cplHpmcVWmVP,cplHpmcVWmVZ,cplcHpmVPVWm,cplcHpmVWmVZ,cplVGVGVG,cplcVWmVPVWm,            & 
& cplcVWmVWmVZ,cplcChaChaAhL,cplcChaChaAhR,cplChiChiAhL,cplChiChiAhR,cplcFdFdAhL,        & 
& cplcFdFdAhR,cplcFeFeAhL,cplcFeFeAhR,cplcFuFuAhL,cplcFuFuAhR,cplChiChacHpmL,            & 
& cplChiChacHpmR,cplChaFucSdL,cplChaFucSdR,cplChaFvcSeL,cplChaFvcSeR,cplcChaChahhL,      & 
& cplcChaChahhR,cplcFdChaSuL,cplcFdChaSuR,cplcFeChaSvL,cplcFeChaSvR,cplChiChihhL,        & 
& cplChiChihhR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,         & 
& cplChiFucSuR,cplChiFvcSvL,cplChiFvcSvR,cplcChaChiHpmL,cplcChaChiHpmR,cplcFdChiSdL,     & 
& cplcFdChiSdR,cplcFeChiSeL,cplcFeChiSeR,cplcFuChiSuL,cplcFuChiSuR,cplcFvChiSvL,         & 
& cplcFvChiSvR,cplGluFdcSdL,cplGluFdcSdR,cplcFdFdhhL,cplcFdFdhhR,cplcChaFdcSuL,          & 
& cplcChaFdcSuR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFeFehhL,cplcFeFehhR,cplcChaFecSvL,       & 
& cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplGluFucSuL,cplGluFucSuR,cplcFuFuhhL,       & 
& cplcFuFuhhR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFdGluSdL,          & 
& cplcFdGluSdR,cplcFuGluSuL,cplcFuGluSuR,cplcChacFuSdL,cplcChacFuSdR,cplcChacFvSeL,      & 
& cplcChacFvSeR,cplChiChacVWmL,cplChiChacVWmR,cplcChaChaVPL,cplcChaChaVPR,               & 
& cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,cplcChaChiVWmL,cplcChaChiVWmR,   & 
& cplcFdFdVGL,cplcFdFdVGR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,               & 
& cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,           & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplcFuFuVGL,cplcFuFuVGR,cplcFuFuVPL,cplcFuFuVPR,           & 
& cplcFdFuVWmL,cplcFdFuVWmR,cplcFuFuVZL,cplcFuFuVZR,cplcFeFvVWmL,cplcFeFvVWmR,           & 
& cplcFvFvVZL,cplcFvFvVZR,cplGluGluVGL,cplGluGluVGR)

Mhh_s = Mhh 
Mhh2_s  = Mhh2   
MAh_s = MAh 
MAh2_s  = MAh2   
Mhh= MhhL 
Mhh2 = Mhh2L 
MAh= MAhL 
MAh2 = MAh2L 
iQFinal = 1 
If (MakeQtest) iQFinal=10 
Qinsave=GetRenormalizationScale() 
Do iQTEST=1,iQFinal 
maxdiff=0._dp 
If (MakeQtest) Qin=SetRenormalizationScale(10.0_dp**iQTest) 

 ! **** Box2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& BOllddSLL(gt1,gt2,gt3,gt4),BOllddSRR(gt1,gt2,gt3,gt4),BOllddSRL(gt1,gt2,gt3,gt4)       & 
& ,BOllddSLR(gt1,gt2,gt3,gt4),BOllddVRR(gt1,gt2,gt3,gt4),BOllddVLL(gt1,gt2,gt3,gt4)      & 
& ,BOllddVRL(gt1,gt2,gt3,gt4),BOllddVLR(gt1,gt2,gt3,gt4),BOllddTLL(gt1,gt2,gt3,gt4)      & 
& ,BOllddTLR(gt1,gt2,gt3,gt4),BOllddTRL(gt1,gt2,gt3,gt4),BOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PSOllddSLL(gt1,gt2,gt3,gt4),PSOllddSRR(gt1,gt2,gt3,gt4),PSOllddSRL(gt1,gt2,gt3,gt4)    & 
& ,PSOllddSLR(gt1,gt2,gt3,gt4),PSOllddVRR(gt1,gt2,gt3,gt4),PSOllddVLL(gt1,gt2,gt3,gt4)   & 
& ,PSOllddVRL(gt1,gt2,gt3,gt4),PSOllddVLR(gt1,gt2,gt3,gt4),PSOllddTLL(gt1,gt2,gt3,gt4)   & 
& ,PSOllddTLR(gt1,gt2,gt3,gt4),PSOllddTRL(gt1,gt2,gt3,gt4),PSOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PVOllddSLL(gt1,gt2,gt3,gt4),PVOllddSRR(gt1,gt2,gt3,gt4),PVOllddSRL(gt1,gt2,gt3,gt4)    & 
& ,PVOllddSLR(gt1,gt2,gt3,gt4),PVOllddVRR(gt1,gt2,gt3,gt4),PVOllddVLL(gt1,gt2,gt3,gt4)   & 
& ,PVOllddVRL(gt1,gt2,gt3,gt4),PVOllddVLR(gt1,gt2,gt3,gt4),PVOllddTLL(gt1,gt2,gt3,gt4)   & 
& ,PVOllddTLR(gt1,gt2,gt3,gt4),PVOllddTRL(gt1,gt2,gt3,gt4),PVOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TSOllddSLL(gt1,gt2,gt3,gt4),TSOllddSRR(gt1,gt2,gt3,gt4),TSOllddSRL(gt1,gt2,gt3,gt4)    & 
& ,TSOllddSLR(gt1,gt2,gt3,gt4),TSOllddVRR(gt1,gt2,gt3,gt4),TSOllddVLL(gt1,gt2,gt3,gt4)   & 
& ,TSOllddVRL(gt1,gt2,gt3,gt4),TSOllddVLR(gt1,gt2,gt3,gt4),TSOllddTLL(gt1,gt2,gt3,gt4)   & 
& ,TSOllddTLR(gt1,gt2,gt3,gt4),TSOllddTRL(gt1,gt2,gt3,gt4),TSOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV2L2d **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
IndexArray4(4,:) = (/2,1,2,2/) 
IndexArray4(5,:) = (/3,1,2,2/) 
IndexArray4(6,:) = (/3,2,2,2/) 
Do i1=1,6 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2L2d(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChaChaAhL,              & 
& cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,   & 
& cplcChaChaVZR,cplcChaFdcSuL,cplcChaFdcSuR,cplcChaFecSvL,cplcChaFecSvR,cplcFdChaSuL,    & 
& cplcFdChaSuR,cplcFdChiSdL,cplcFdChiSdR,cplcFdFdAhL,cplcFdFdAhR,cplcFdFdhhL,            & 
& cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,cplcFdFdVZR,cplcFdFuHpmL,              & 
& cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFdGluSdL,cplcFdGluSdR,cplcFeChaSvL,         & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuFdcHpmL,cplcFuFdcHpmR,cplcFuFdcVWmL,      & 
& cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,cplcFuFuhhR,cplcFuFuVPL,             & 
& cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,         & 
& cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,        & 
& cplChiChiVZR,cplChiFdcSdL,cplChiFdcSdR,cplChiFecSeL,cplChiFecSeR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFdcSdL,cplGluFdcSdR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TVOllddSLL(gt1,gt2,gt3,gt4),TVOllddSRR(gt1,gt2,gt3,gt4),TVOllddSRL(gt1,gt2,gt3,gt4)    & 
& ,TVOllddSLR(gt1,gt2,gt3,gt4),TVOllddVRR(gt1,gt2,gt3,gt4),TVOllddVLL(gt1,gt2,gt3,gt4)   & 
& ,TVOllddVRL(gt1,gt2,gt3,gt4),TVOllddVLR(gt1,gt2,gt3,gt4),TVOllddTLL(gt1,gt2,gt3,gt4)   & 
& ,TVOllddTLR(gt1,gt2,gt3,gt4),TVOllddTRL(gt1,gt2,gt3,gt4),TVOllddTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,   & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeChaSvL,          & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChaFucSdL,     & 
& cplChaFucSdR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,         & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& BOlluuSLL(gt1,gt2,gt3,gt4),BOlluuSRR(gt1,gt2,gt3,gt4),BOlluuSRL(gt1,gt2,gt3,gt4)       & 
& ,BOlluuSLR(gt1,gt2,gt3,gt4),BOlluuVRR(gt1,gt2,gt3,gt4),BOlluuVLL(gt1,gt2,gt3,gt4)      & 
& ,BOlluuVRL(gt1,gt2,gt3,gt4),BOlluuVLR(gt1,gt2,gt3,gt4),BOlluuTLL(gt1,gt2,gt3,gt4)      & 
& ,BOlluuTLR(gt1,gt2,gt3,gt4),BOlluuTRL(gt1,gt2,gt3,gt4),BOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,   & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeChaSvL,          & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChaFucSdL,     & 
& cplChaFucSdR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,         & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PSOlluuSLL(gt1,gt2,gt3,gt4),PSOlluuSRR(gt1,gt2,gt3,gt4),PSOlluuSRL(gt1,gt2,gt3,gt4)    & 
& ,PSOlluuSLR(gt1,gt2,gt3,gt4),PSOlluuVRR(gt1,gt2,gt3,gt4),PSOlluuVLL(gt1,gt2,gt3,gt4)   & 
& ,PSOlluuVRL(gt1,gt2,gt3,gt4),PSOlluuVLR(gt1,gt2,gt3,gt4),PSOlluuTLL(gt1,gt2,gt3,gt4)   & 
& ,PSOlluuTLR(gt1,gt2,gt3,gt4),PSOlluuTRL(gt1,gt2,gt3,gt4),PSOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,   & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeChaSvL,          & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChaFucSdL,     & 
& cplChaFucSdR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,         & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& PVOlluuSLL(gt1,gt2,gt3,gt4),PVOlluuSRR(gt1,gt2,gt3,gt4),PVOlluuSRL(gt1,gt2,gt3,gt4)    & 
& ,PVOlluuSLR(gt1,gt2,gt3,gt4),PVOlluuVRR(gt1,gt2,gt3,gt4),PVOlluuVLL(gt1,gt2,gt3,gt4)   & 
& ,PVOlluuVRL(gt1,gt2,gt3,gt4),PVOlluuVLR(gt1,gt2,gt3,gt4),PVOlluuTLL(gt1,gt2,gt3,gt4)   & 
& ,PVOlluuTLR(gt1,gt2,gt3,gt4),PVOlluuTRL(gt1,gt2,gt3,gt4),PVOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,   & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeChaSvL,          & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChaFucSdL,     & 
& cplChaFucSdR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,         & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TSOlluuSLL(gt1,gt2,gt3,gt4),TSOlluuSRR(gt1,gt2,gt3,gt4),TSOlluuSRL(gt1,gt2,gt3,gt4)    & 
& ,TSOlluuSLR(gt1,gt2,gt3,gt4),TSOlluuVRR(gt1,gt2,gt3,gt4),TSOlluuVLL(gt1,gt2,gt3,gt4)   & 
& ,TSOlluuVRL(gt1,gt2,gt3,gt4),TSOlluuVLR(gt1,gt2,gt3,gt4),TSOlluuTLL(gt1,gt2,gt3,gt4)   & 
& ,TSOlluuTLR(gt1,gt2,gt3,gt4),TSOlluuTRL(gt1,gt2,gt3,gt4),TSOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV2L2u **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,1,1/) 
Do i1=1,3 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV2L2u(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,             & 
& MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,              & 
& MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,cplAhcHpmVWm,cplAhhhVZ,       & 
& cplAhHpmcHpm,cplAhHpmcVWm,cplAhSdcSd,cplAhSecSe,cplAhSucSu,cplcChacFuSdL,              & 
& cplcChacFuSdR,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,cplcChaChaVPL,   & 
& cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFdFdAhL,     & 
& cplcFdFdAhR,cplcFdFdhhL,cplcFdFdhhR,cplcFdFdVPL,cplcFdFdVPR,cplcFdFdVZL,               & 
& cplcFdFdVZR,cplcFdFuHpmL,cplcFdFuHpmR,cplcFdFuVWmL,cplcFdFuVWmR,cplcFeChaSvL,          & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFuChiSuL,cplcFuChiSuR,cplcFuFdcHpmL,        & 
& cplcFuFdcHpmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFuFuAhL,cplcFuFuAhR,cplcFuFuhhL,         & 
& cplcFuFuhhR,cplcFuFuVPL,cplcFuFuVPR,cplcFuFuVZL,cplcFuFuVZR,cplcFuGluSuL,              & 
& cplcFuGluSuR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChaFucSdL,     & 
& cplChaFucSdR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,cplChiChiVZL,         & 
& cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplChiFucSuL,cplChiFucSuR,cplcHpmVPVWm,         & 
& cplcHpmVWmVZ,cplcVWmVPVWm,cplcVWmVWmVZ,cplGluFucSuL,cplGluFucSuR,cplhhcHpmVWm,         & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSdcSd,cplhhSecSe,cplhhSucSu,     & 
& cplhhSvcSv,cplhhVZVZ,cplHpmcHpmVP,cplHpmcHpmVZ,cplHpmcVWmVP,cplHpmcVWmVZ,              & 
& cplSdcSdVP,cplSdcSdVZ,cplSecSeVP,cplSecSeVZ,cplSucSuVP,cplSucSuVZ,cplSvcSvVZ,          & 
& TVOlluuSLL(gt1,gt2,gt3,gt4),TVOlluuSRR(gt1,gt2,gt3,gt4),TVOlluuSRL(gt1,gt2,gt3,gt4)    & 
& ,TVOlluuSLR(gt1,gt2,gt3,gt4),TVOlluuVRR(gt1,gt2,gt3,gt4),TVOlluuVLL(gt1,gt2,gt3,gt4)   & 
& ,TVOlluuVRL(gt1,gt2,gt3,gt4),TVOlluuVLR(gt1,gt2,gt3,gt4),TVOlluuTLL(gt1,gt2,gt3,gt4)   & 
& ,TVOlluuTLR(gt1,gt2,gt3,gt4),TVOlluuTRL(gt1,gt2,gt3,gt4),TVOlluuTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,           & 
& MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,          & 
& cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,cplcChaChahhR,          & 
& cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,   & 
& cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,           & 
& cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,               & 
& cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,cplcFvFecHpmR,       & 
& cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,cplChiChihhR,       & 
& cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,cplhhSecSe,              & 
& cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,BO4lSLL(gt1,gt2,gt3,gt4)         & 
& ,BO4lSRR(gt1,gt2,gt3,gt4),BO4lSRL(gt1,gt2,gt3,gt4),BO4lSLR(gt1,gt2,gt3,gt4)            & 
& ,BO4lVRR(gt1,gt2,gt3,gt4),BO4lVLL(gt1,gt2,gt3,gt4),BO4lVRL(gt1,gt2,gt3,gt4)            & 
& ,BO4lVLR(gt1,gt2,gt3,gt4),BO4lTLL(gt1,gt2,gt3,gt4),BO4lTLR(gt1,gt2,gt3,gt4)            & 
& ,BO4lTRL(gt1,gt2,gt3,gt4),BO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,              & 
& cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,PSO4lSLL(gt1,gt2,gt3,gt4)& 
& ,PSO4lSRR(gt1,gt2,gt3,gt4),PSO4lSRL(gt1,gt2,gt3,gt4),PSO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,PSO4lVRR(gt1,gt2,gt3,gt4),PSO4lVLL(gt1,gt2,gt3,gt4),PSO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,PSO4lVLR(gt1,gt2,gt3,gt4),PSO4lTLL(gt1,gt2,gt3,gt4),PSO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,PSO4lTRL(gt1,gt2,gt3,gt4),PSO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,              & 
& cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,PVO4lSLL(gt1,gt2,gt3,gt4)& 
& ,PVO4lSRR(gt1,gt2,gt3,gt4),PVO4lSRL(gt1,gt2,gt3,gt4),PVO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,PVO4lVRR(gt1,gt2,gt3,gt4),PVO4lVLL(gt1,gt2,gt3,gt4),PVO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,PVO4lVLR(gt1,gt2,gt3,gt4),PVO4lTLL(gt1,gt2,gt3,gt4),PVO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,PVO4lTRL(gt1,gt2,gt3,gt4),PVO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,              & 
& cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,TSO4lSLL(gt1,gt2,gt3,gt4)& 
& ,TSO4lSRR(gt1,gt2,gt3,gt4),TSO4lSRL(gt1,gt2,gt3,gt4),TSO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,TSO4lVRR(gt1,gt2,gt3,gt4),TSO4lVLL(gt1,gt2,gt3,gt4),TSO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,TSO4lVLR(gt1,gt2,gt3,gt4),TSO4lTLL(gt1,gt2,gt3,gt4),TSO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,TSO4lTRL(gt1,gt2,gt3,gt4),TSO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV4L **** 
 
IndexArray4(1,:) = (/2,1,1,1/) 
IndexArray4(2,:) = (/3,1,1,1/) 
IndexArray4(3,:) = (/3,2,2,2/) 
IndexArray4(4,:) = (/3,2,1,2/) 
IndexArray4(5,:) = (/3,1,2,1/) 
Do i1=1,5 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4L(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,               & 
& MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,              & 
& cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,TVO4lSLL(gt1,gt2,gt3,gt4)& 
& ,TVO4lSRR(gt1,gt2,gt3,gt4),TVO4lSRL(gt1,gt2,gt3,gt4),TVO4lSLR(gt1,gt2,gt3,gt4)         & 
& ,TVO4lVRR(gt1,gt2,gt3,gt4),TVO4lVLL(gt1,gt2,gt3,gt4),TVO4lVRL(gt1,gt2,gt3,gt4)         & 
& ,TVO4lVLR(gt1,gt2,gt3,gt4),TVO4lTLL(gt1,gt2,gt3,gt4),TVO4lTLR(gt1,gt2,gt3,gt4)         & 
& ,TVO4lTRL(gt1,gt2,gt3,gt4),TVO4lTRR(gt1,gt2,gt3,gt4))

End Do 


 ! **** Box4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateBox4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,MChi,            & 
& MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,              & 
& cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,              & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,BO4lSLLcross(gt1,gt2,gt3,gt4)& 
& ,BO4lSRRcross(gt1,gt2,gt3,gt4),BO4lSRLcross(gt1,gt2,gt3,gt4),BO4lSLRcross(gt1,gt2,gt3,gt4)& 
& ,BO4lVRRcross(gt1,gt2,gt3,gt4),BO4lVLLcross(gt1,gt2,gt3,gt4),BO4lVRLcross(gt1,gt2,gt3,gt4)& 
& ,BO4lVLRcross(gt1,gt2,gt3,gt4),BO4lTLLcross(gt1,gt2,gt3,gt4),BO4lTLRcross(gt1,gt2,gt3,gt4)& 
& ,BO4lTRLcross(gt1,gt2,gt3,gt4),BO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengS4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengS4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,               & 
& MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,              & 
& MVZ2,cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,         & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,PSO4lSLLcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lSRRcross(gt1,gt2,gt3,gt4),PSO4lSRLcross(gt1,gt2,gt3,gt4),PSO4lSLRcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lVRRcross(gt1,gt2,gt3,gt4),PSO4lVLLcross(gt1,gt2,gt3,gt4),PSO4lVRLcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lVLRcross(gt1,gt2,gt3,gt4),PSO4lTLLcross(gt1,gt2,gt3,gt4),PSO4lTLRcross(gt1,gt2,gt3,gt4)& 
& ,PSO4lTRLcross(gt1,gt2,gt3,gt4),PSO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** PengV4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculatePengV4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,               & 
& MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,              & 
& MVZ2,cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,         & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,PVO4lSLLcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lSRRcross(gt1,gt2,gt3,gt4),PVO4lSRLcross(gt1,gt2,gt3,gt4),PVO4lSLRcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lVRRcross(gt1,gt2,gt3,gt4),PVO4lVLLcross(gt1,gt2,gt3,gt4),PVO4lVRLcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lVLRcross(gt1,gt2,gt3,gt4),PVO4lTLLcross(gt1,gt2,gt3,gt4),PVO4lTLRcross(gt1,gt2,gt3,gt4)& 
& ,PVO4lTRLcross(gt1,gt2,gt3,gt4),PVO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeS4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeS4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,               & 
& MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,              & 
& MVZ2,cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,         & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,TSO4lSLLcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lSRRcross(gt1,gt2,gt3,gt4),TSO4lSRLcross(gt1,gt2,gt3,gt4),TSO4lSLRcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lVRRcross(gt1,gt2,gt3,gt4),TSO4lVLLcross(gt1,gt2,gt3,gt4),TSO4lVRLcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lVLRcross(gt1,gt2,gt3,gt4),TSO4lTLLcross(gt1,gt2,gt3,gt4),TSO4lTLRcross(gt1,gt2,gt3,gt4)& 
& ,TSO4lTRLcross(gt1,gt2,gt3,gt4),TSO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** TreeV4Lcross **** 
 
IndexArray4(1,:) = (/3,1,2,2/) 
IndexArray4(2,:) = (/3,2,1,1/) 
IndexArray4(3,:) = (/3,2,1,2/) 
IndexArray4(4,:) = (/3,1,2,1/) 
Do i1=1,4 
gt1 = IndexArray4(i1,1) 
gt2 = IndexArray4(i1,2) 
gt3 = IndexArray4(i1,3) 
gt4 = IndexArray4(i1,4) 
Call CalculateTreeV4Lcross(gt1,gt2,gt3,gt4,.False.,MAh,MAh2,MCha,MCha2,               & 
& MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,              & 
& MVZ2,cplAhAhhh,cplAhhhVZ,cplAhSecSe,cplcChaChaAhL,cplcChaChaAhR,cplcChaChahhL,         & 
& cplcChaChahhR,cplcChaChaVPL,cplcChaChaVPR,cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,   & 
& cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,         & 
& cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,               & 
& cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiChiAhL,cplChiChiAhR,cplChiChihhL,      & 
& cplChiChihhR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,cplhhhhhh,            & 
& cplhhSecSe,cplhhSvcSv,cplhhVZVZ,cplSecSeVP,cplSecSeVZ,cplSvcSvVZ,TVO4lSLLcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lSRRcross(gt1,gt2,gt3,gt4),TVO4lSRLcross(gt1,gt2,gt3,gt4),TVO4lSLRcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lVRRcross(gt1,gt2,gt3,gt4),TVO4lVLLcross(gt1,gt2,gt3,gt4),TVO4lVRLcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lVLRcross(gt1,gt2,gt3,gt4),TVO4lTLLcross(gt1,gt2,gt3,gt4),TVO4lTLRcross(gt1,gt2,gt3,gt4)& 
& ,TVO4lTRLcross(gt1,gt2,gt3,gt4),TVO4lTRRcross(gt1,gt2,gt3,gt4))

End Do 


 ! **** Gamma2l **** 
 
IndexArray2(1,:) = (/2,1/) 
IndexArray2(2,:) = (/3,1/) 
IndexArray2(3,:) = (/3,2/) 
Do i1=1,3 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateGamma2l(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,             & 
& MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplcChaChaVPL,      & 
& cplcChaChaVPR,cplcChaFecSvL,cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,cplcFeChiSeL,      & 
& cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,              & 
& cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,            & 
& cplcFeFvVWmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,cplChiFecSeL,     & 
& cplChiFecSeR,cplcHpmVPVWm,cplcVWmVPVWm,cplHpmcHpmVP,cplHpmcVWmVP,cplSecSeVP,           & 
& OA2lSL(gt1,gt2),OA2lSR(gt1,gt2),OA1L(gt1,gt2),OA1R(gt1,gt2))

End Do 


 ! **** H2l **** 
 
IndexArray3(1,:) = (/1,2,1/) 
IndexArray3(2,:) = (/1,3,1/) 
IndexArray3(3,:) = (/2,3,1/) 
IndexArray3(4,:) = (/2,1,1/) 
IndexArray3(5,:) = (/3,1,1/) 
IndexArray3(6,:) = (/3,2,1/) 
Do i1=1,6 
gt1 = IndexArray3(i1,1) 
gt2 = IndexArray3(i1,2) 
 Do i2=1,2 
  gt3=i2 
Call CalculateH2l(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,             & 
& MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhAhhh,              & 
& cplAhhhVZ,cplcChaChahhL,cplcChaChahhR,cplcChaFecSvL,cplcChaFecSvR,cplcFeChaSvL,        & 
& cplcFeChaSvR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,            & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,              & 
& cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,      & 
& cplcFvFecVWmR,cplChiChihhL,cplChiChihhR,cplChiFecSeL,cplChiFecSeR,cplhhcHpmVWm,        & 
& cplhhcVWmVWm,cplhhhhhh,cplhhHpmcHpm,cplhhHpmcVWm,cplhhSecSe,cplhhSvcSv,cplhhVZVZ,      & 
& OH2lSL(gt1,gt2,gt3),OH2lSR(gt1,gt2,gt3))

End Do 
 End Do 


 ! **** Z2l **** 
 
IndexArray2(1,:) = (/1,2/) 
IndexArray2(2,:) = (/1,3/) 
IndexArray2(3,:) = (/2,3/) 
Do i1=1,3 
gt1 = IndexArray2(i1,1) 
gt2 = IndexArray2(i1,2) 
  gt3= 1 
Call CalculateZ2l(gt1,gt2,gt3,.False.,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,             & 
& MFe2,Mhh,Mhh2,MHpm,MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplAhhhVZ,              & 
& cplcChaChaVZL,cplcChaChaVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFeChaSvL,cplcFeChaSvR,     & 
& cplcFeChiSeL,cplcFeChiSeR,cplcFeFeAhL,cplcFeFeAhR,cplcFeFehhL,cplcFeFehhR,             & 
& cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,cplcFeFeVZR,cplcFeFvHpmL,cplcFeFvHpmR,             & 
& cplcFeFvVWmL,cplcFeFvVWmR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,cplcFvFecVWmR,     & 
& cplcFvFvVZL,cplcFvFvVZR,cplChiChiVZL,cplChiChiVZR,cplChiFecSeL,cplChiFecSeR,           & 
& cplcHpmVWmVZ,cplcVWmVWmVZ,cplhhVZVZ,cplHpmcHpmVZ,cplHpmcVWmVZ,cplSecSeVZ,              & 
& cplSvcSvVZ,OZ2lSL(gt1,gt2),OZ2lSR(gt1,gt2),OZ2lVL(gt1,gt2),OZ2lVR(gt1,gt2))

End Do 

If (MakeQTEST) Then  
where (Abs(BOllddSLLcheck).ne.0._dp) BOllddSLLcheck = (BOllddSLLcheck-BOllddSLL)/BOllddSLLcheck
If(MaxVal(Abs(BOllddSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddSLLcheck))
BOllddSLLcheck=BOllddSLL
where (Abs(BOllddSRRcheck).ne.0._dp) BOllddSRRcheck = (BOllddSRRcheck-BOllddSRR)/BOllddSRRcheck
If(MaxVal(Abs(BOllddSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddSRRcheck))
BOllddSRRcheck=BOllddSRR
where (Abs(BOllddSRLcheck).ne.0._dp) BOllddSRLcheck = (BOllddSRLcheck-BOllddSRL)/BOllddSRLcheck
If(MaxVal(Abs(BOllddSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddSRLcheck))
BOllddSRLcheck=BOllddSRL
where (Abs(BOllddSLRcheck).ne.0._dp) BOllddSLRcheck = (BOllddSLRcheck-BOllddSLR)/BOllddSLRcheck
If(MaxVal(Abs(BOllddSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddSLRcheck))
BOllddSLRcheck=BOllddSLR
where (Abs(BOllddVRRcheck).ne.0._dp) BOllddVRRcheck = (BOllddVRRcheck-BOllddVRR)/BOllddVRRcheck
If(MaxVal(Abs(BOllddVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddVRRcheck))
BOllddVRRcheck=BOllddVRR
where (Abs(BOllddVLLcheck).ne.0._dp) BOllddVLLcheck = (BOllddVLLcheck-BOllddVLL)/BOllddVLLcheck
If(MaxVal(Abs(BOllddVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddVLLcheck))
BOllddVLLcheck=BOllddVLL
where (Abs(BOllddVRLcheck).ne.0._dp) BOllddVRLcheck = (BOllddVRLcheck-BOllddVRL)/BOllddVRLcheck
If(MaxVal(Abs(BOllddVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddVRLcheck))
BOllddVRLcheck=BOllddVRL
where (Abs(BOllddVLRcheck).ne.0._dp) BOllddVLRcheck = (BOllddVLRcheck-BOllddVLR)/BOllddVLRcheck
If(MaxVal(Abs(BOllddVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddVLRcheck))
BOllddVLRcheck=BOllddVLR
where (Abs(BOllddTLLcheck).ne.0._dp) BOllddTLLcheck = (BOllddTLLcheck-BOllddTLL)/BOllddTLLcheck
If(MaxVal(Abs(BOllddTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddTLLcheck))
BOllddTLLcheck=BOllddTLL
where (Abs(BOllddTLRcheck).ne.0._dp) BOllddTLRcheck = (BOllddTLRcheck-BOllddTLR)/BOllddTLRcheck
If(MaxVal(Abs(BOllddTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddTLRcheck))
BOllddTLRcheck=BOllddTLR
where (Abs(BOllddTRLcheck).ne.0._dp) BOllddTRLcheck = (BOllddTRLcheck-BOllddTRL)/BOllddTRLcheck
If(MaxVal(Abs(BOllddTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddTRLcheck))
BOllddTRLcheck=BOllddTRL
where (Abs(BOllddTRRcheck).ne.0._dp) BOllddTRRcheck = (BOllddTRRcheck-BOllddTRR)/BOllddTRRcheck
If(MaxVal(Abs(BOllddTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOllddTRRcheck))
BOllddTRRcheck=BOllddTRR
where (Abs(PSOllddSLLcheck).ne.0._dp) PSOllddSLLcheck = (PSOllddSLLcheck-PSOllddSLL)/PSOllddSLLcheck
If(MaxVal(Abs(PSOllddSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddSLLcheck))
PSOllddSLLcheck=PSOllddSLL
where (Abs(PSOllddSRRcheck).ne.0._dp) PSOllddSRRcheck = (PSOllddSRRcheck-PSOllddSRR)/PSOllddSRRcheck
If(MaxVal(Abs(PSOllddSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddSRRcheck))
PSOllddSRRcheck=PSOllddSRR
where (Abs(PSOllddSRLcheck).ne.0._dp) PSOllddSRLcheck = (PSOllddSRLcheck-PSOllddSRL)/PSOllddSRLcheck
If(MaxVal(Abs(PSOllddSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddSRLcheck))
PSOllddSRLcheck=PSOllddSRL
where (Abs(PSOllddSLRcheck).ne.0._dp) PSOllddSLRcheck = (PSOllddSLRcheck-PSOllddSLR)/PSOllddSLRcheck
If(MaxVal(Abs(PSOllddSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddSLRcheck))
PSOllddSLRcheck=PSOllddSLR
where (Abs(PSOllddVRRcheck).ne.0._dp) PSOllddVRRcheck = (PSOllddVRRcheck-PSOllddVRR)/PSOllddVRRcheck
If(MaxVal(Abs(PSOllddVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddVRRcheck))
PSOllddVRRcheck=PSOllddVRR
where (Abs(PSOllddVLLcheck).ne.0._dp) PSOllddVLLcheck = (PSOllddVLLcheck-PSOllddVLL)/PSOllddVLLcheck
If(MaxVal(Abs(PSOllddVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddVLLcheck))
PSOllddVLLcheck=PSOllddVLL
where (Abs(PSOllddVRLcheck).ne.0._dp) PSOllddVRLcheck = (PSOllddVRLcheck-PSOllddVRL)/PSOllddVRLcheck
If(MaxVal(Abs(PSOllddVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddVRLcheck))
PSOllddVRLcheck=PSOllddVRL
where (Abs(PSOllddVLRcheck).ne.0._dp) PSOllddVLRcheck = (PSOllddVLRcheck-PSOllddVLR)/PSOllddVLRcheck
If(MaxVal(Abs(PSOllddVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddVLRcheck))
PSOllddVLRcheck=PSOllddVLR
where (Abs(PSOllddTLLcheck).ne.0._dp) PSOllddTLLcheck = (PSOllddTLLcheck-PSOllddTLL)/PSOllddTLLcheck
If(MaxVal(Abs(PSOllddTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddTLLcheck))
PSOllddTLLcheck=PSOllddTLL
where (Abs(PSOllddTLRcheck).ne.0._dp) PSOllddTLRcheck = (PSOllddTLRcheck-PSOllddTLR)/PSOllddTLRcheck
If(MaxVal(Abs(PSOllddTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddTLRcheck))
PSOllddTLRcheck=PSOllddTLR
where (Abs(PSOllddTRLcheck).ne.0._dp) PSOllddTRLcheck = (PSOllddTRLcheck-PSOllddTRL)/PSOllddTRLcheck
If(MaxVal(Abs(PSOllddTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddTRLcheck))
PSOllddTRLcheck=PSOllddTRL
where (Abs(PSOllddTRRcheck).ne.0._dp) PSOllddTRRcheck = (PSOllddTRRcheck-PSOllddTRR)/PSOllddTRRcheck
If(MaxVal(Abs(PSOllddTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOllddTRRcheck))
PSOllddTRRcheck=PSOllddTRR
where (Abs(PVOllddSLLcheck).ne.0._dp) PVOllddSLLcheck = (PVOllddSLLcheck-PVOllddSLL)/PVOllddSLLcheck
If(MaxVal(Abs(PVOllddSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddSLLcheck))
PVOllddSLLcheck=PVOllddSLL
where (Abs(PVOllddSRRcheck).ne.0._dp) PVOllddSRRcheck = (PVOllddSRRcheck-PVOllddSRR)/PVOllddSRRcheck
If(MaxVal(Abs(PVOllddSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddSRRcheck))
PVOllddSRRcheck=PVOllddSRR
where (Abs(PVOllddSRLcheck).ne.0._dp) PVOllddSRLcheck = (PVOllddSRLcheck-PVOllddSRL)/PVOllddSRLcheck
If(MaxVal(Abs(PVOllddSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddSRLcheck))
PVOllddSRLcheck=PVOllddSRL
where (Abs(PVOllddSLRcheck).ne.0._dp) PVOllddSLRcheck = (PVOllddSLRcheck-PVOllddSLR)/PVOllddSLRcheck
If(MaxVal(Abs(PVOllddSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddSLRcheck))
PVOllddSLRcheck=PVOllddSLR
where (Abs(PVOllddVRRcheck).ne.0._dp) PVOllddVRRcheck = (PVOllddVRRcheck-PVOllddVRR)/PVOllddVRRcheck
If(MaxVal(Abs(PVOllddVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddVRRcheck))
PVOllddVRRcheck=PVOllddVRR
where (Abs(PVOllddVLLcheck).ne.0._dp) PVOllddVLLcheck = (PVOllddVLLcheck-PVOllddVLL)/PVOllddVLLcheck
If(MaxVal(Abs(PVOllddVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddVLLcheck))
PVOllddVLLcheck=PVOllddVLL
where (Abs(PVOllddVRLcheck).ne.0._dp) PVOllddVRLcheck = (PVOllddVRLcheck-PVOllddVRL)/PVOllddVRLcheck
If(MaxVal(Abs(PVOllddVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddVRLcheck))
PVOllddVRLcheck=PVOllddVRL
where (Abs(PVOllddVLRcheck).ne.0._dp) PVOllddVLRcheck = (PVOllddVLRcheck-PVOllddVLR)/PVOllddVLRcheck
If(MaxVal(Abs(PVOllddVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddVLRcheck))
PVOllddVLRcheck=PVOllddVLR
where (Abs(PVOllddTLLcheck).ne.0._dp) PVOllddTLLcheck = (PVOllddTLLcheck-PVOllddTLL)/PVOllddTLLcheck
If(MaxVal(Abs(PVOllddTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddTLLcheck))
PVOllddTLLcheck=PVOllddTLL
where (Abs(PVOllddTLRcheck).ne.0._dp) PVOllddTLRcheck = (PVOllddTLRcheck-PVOllddTLR)/PVOllddTLRcheck
If(MaxVal(Abs(PVOllddTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddTLRcheck))
PVOllddTLRcheck=PVOllddTLR
where (Abs(PVOllddTRLcheck).ne.0._dp) PVOllddTRLcheck = (PVOllddTRLcheck-PVOllddTRL)/PVOllddTRLcheck
If(MaxVal(Abs(PVOllddTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddTRLcheck))
PVOllddTRLcheck=PVOllddTRL
where (Abs(PVOllddTRRcheck).ne.0._dp) PVOllddTRRcheck = (PVOllddTRRcheck-PVOllddTRR)/PVOllddTRRcheck
If(MaxVal(Abs(PVOllddTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOllddTRRcheck))
PVOllddTRRcheck=PVOllddTRR
where (Abs(TSOllddSLLcheck).ne.0._dp) TSOllddSLLcheck = (TSOllddSLLcheck-TSOllddSLL)/TSOllddSLLcheck
If(MaxVal(Abs(TSOllddSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddSLLcheck))
TSOllddSLLcheck=TSOllddSLL
where (Abs(TSOllddSRRcheck).ne.0._dp) TSOllddSRRcheck = (TSOllddSRRcheck-TSOllddSRR)/TSOllddSRRcheck
If(MaxVal(Abs(TSOllddSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddSRRcheck))
TSOllddSRRcheck=TSOllddSRR
where (Abs(TSOllddSRLcheck).ne.0._dp) TSOllddSRLcheck = (TSOllddSRLcheck-TSOllddSRL)/TSOllddSRLcheck
If(MaxVal(Abs(TSOllddSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddSRLcheck))
TSOllddSRLcheck=TSOllddSRL
where (Abs(TSOllddSLRcheck).ne.0._dp) TSOllddSLRcheck = (TSOllddSLRcheck-TSOllddSLR)/TSOllddSLRcheck
If(MaxVal(Abs(TSOllddSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddSLRcheck))
TSOllddSLRcheck=TSOllddSLR
where (Abs(TSOllddVRRcheck).ne.0._dp) TSOllddVRRcheck = (TSOllddVRRcheck-TSOllddVRR)/TSOllddVRRcheck
If(MaxVal(Abs(TSOllddVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddVRRcheck))
TSOllddVRRcheck=TSOllddVRR
where (Abs(TSOllddVLLcheck).ne.0._dp) TSOllddVLLcheck = (TSOllddVLLcheck-TSOllddVLL)/TSOllddVLLcheck
If(MaxVal(Abs(TSOllddVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddVLLcheck))
TSOllddVLLcheck=TSOllddVLL
where (Abs(TSOllddVRLcheck).ne.0._dp) TSOllddVRLcheck = (TSOllddVRLcheck-TSOllddVRL)/TSOllddVRLcheck
If(MaxVal(Abs(TSOllddVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddVRLcheck))
TSOllddVRLcheck=TSOllddVRL
where (Abs(TSOllddVLRcheck).ne.0._dp) TSOllddVLRcheck = (TSOllddVLRcheck-TSOllddVLR)/TSOllddVLRcheck
If(MaxVal(Abs(TSOllddVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddVLRcheck))
TSOllddVLRcheck=TSOllddVLR
where (Abs(TSOllddTLLcheck).ne.0._dp) TSOllddTLLcheck = (TSOllddTLLcheck-TSOllddTLL)/TSOllddTLLcheck
If(MaxVal(Abs(TSOllddTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddTLLcheck))
TSOllddTLLcheck=TSOllddTLL
where (Abs(TSOllddTLRcheck).ne.0._dp) TSOllddTLRcheck = (TSOllddTLRcheck-TSOllddTLR)/TSOllddTLRcheck
If(MaxVal(Abs(TSOllddTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddTLRcheck))
TSOllddTLRcheck=TSOllddTLR
where (Abs(TSOllddTRLcheck).ne.0._dp) TSOllddTRLcheck = (TSOllddTRLcheck-TSOllddTRL)/TSOllddTRLcheck
If(MaxVal(Abs(TSOllddTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddTRLcheck))
TSOllddTRLcheck=TSOllddTRL
where (Abs(TSOllddTRRcheck).ne.0._dp) TSOllddTRRcheck = (TSOllddTRRcheck-TSOllddTRR)/TSOllddTRRcheck
If(MaxVal(Abs(TSOllddTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOllddTRRcheck))
TSOllddTRRcheck=TSOllddTRR
where (Abs(TVOllddSLLcheck).ne.0._dp) TVOllddSLLcheck = (TVOllddSLLcheck-TVOllddSLL)/TVOllddSLLcheck
If(MaxVal(Abs(TVOllddSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddSLLcheck))
TVOllddSLLcheck=TVOllddSLL
where (Abs(TVOllddSRRcheck).ne.0._dp) TVOllddSRRcheck = (TVOllddSRRcheck-TVOllddSRR)/TVOllddSRRcheck
If(MaxVal(Abs(TVOllddSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddSRRcheck))
TVOllddSRRcheck=TVOllddSRR
where (Abs(TVOllddSRLcheck).ne.0._dp) TVOllddSRLcheck = (TVOllddSRLcheck-TVOllddSRL)/TVOllddSRLcheck
If(MaxVal(Abs(TVOllddSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddSRLcheck))
TVOllddSRLcheck=TVOllddSRL
where (Abs(TVOllddSLRcheck).ne.0._dp) TVOllddSLRcheck = (TVOllddSLRcheck-TVOllddSLR)/TVOllddSLRcheck
If(MaxVal(Abs(TVOllddSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddSLRcheck))
TVOllddSLRcheck=TVOllddSLR
where (Abs(TVOllddVRRcheck).ne.0._dp) TVOllddVRRcheck = (TVOllddVRRcheck-TVOllddVRR)/TVOllddVRRcheck
If(MaxVal(Abs(TVOllddVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddVRRcheck))
TVOllddVRRcheck=TVOllddVRR
where (Abs(TVOllddVLLcheck).ne.0._dp) TVOllddVLLcheck = (TVOllddVLLcheck-TVOllddVLL)/TVOllddVLLcheck
If(MaxVal(Abs(TVOllddVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddVLLcheck))
TVOllddVLLcheck=TVOllddVLL
where (Abs(TVOllddVRLcheck).ne.0._dp) TVOllddVRLcheck = (TVOllddVRLcheck-TVOllddVRL)/TVOllddVRLcheck
If(MaxVal(Abs(TVOllddVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddVRLcheck))
TVOllddVRLcheck=TVOllddVRL
where (Abs(TVOllddVLRcheck).ne.0._dp) TVOllddVLRcheck = (TVOllddVLRcheck-TVOllddVLR)/TVOllddVLRcheck
If(MaxVal(Abs(TVOllddVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddVLRcheck))
TVOllddVLRcheck=TVOllddVLR
where (Abs(TVOllddTLLcheck).ne.0._dp) TVOllddTLLcheck = (TVOllddTLLcheck-TVOllddTLL)/TVOllddTLLcheck
If(MaxVal(Abs(TVOllddTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddTLLcheck))
TVOllddTLLcheck=TVOllddTLL
where (Abs(TVOllddTLRcheck).ne.0._dp) TVOllddTLRcheck = (TVOllddTLRcheck-TVOllddTLR)/TVOllddTLRcheck
If(MaxVal(Abs(TVOllddTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddTLRcheck))
TVOllddTLRcheck=TVOllddTLR
where (Abs(TVOllddTRLcheck).ne.0._dp) TVOllddTRLcheck = (TVOllddTRLcheck-TVOllddTRL)/TVOllddTRLcheck
If(MaxVal(Abs(TVOllddTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddTRLcheck))
TVOllddTRLcheck=TVOllddTRL
where (Abs(TVOllddTRRcheck).ne.0._dp) TVOllddTRRcheck = (TVOllddTRRcheck-TVOllddTRR)/TVOllddTRRcheck
If(MaxVal(Abs(TVOllddTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOllddTRRcheck))
TVOllddTRRcheck=TVOllddTRR
where (Abs(BOlluuSLLcheck).ne.0._dp) BOlluuSLLcheck = (BOlluuSLLcheck-BOlluuSLL)/BOlluuSLLcheck
If(MaxVal(Abs(BOlluuSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuSLLcheck))
BOlluuSLLcheck=BOlluuSLL
where (Abs(BOlluuSRRcheck).ne.0._dp) BOlluuSRRcheck = (BOlluuSRRcheck-BOlluuSRR)/BOlluuSRRcheck
If(MaxVal(Abs(BOlluuSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuSRRcheck))
BOlluuSRRcheck=BOlluuSRR
where (Abs(BOlluuSRLcheck).ne.0._dp) BOlluuSRLcheck = (BOlluuSRLcheck-BOlluuSRL)/BOlluuSRLcheck
If(MaxVal(Abs(BOlluuSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuSRLcheck))
BOlluuSRLcheck=BOlluuSRL
where (Abs(BOlluuSLRcheck).ne.0._dp) BOlluuSLRcheck = (BOlluuSLRcheck-BOlluuSLR)/BOlluuSLRcheck
If(MaxVal(Abs(BOlluuSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuSLRcheck))
BOlluuSLRcheck=BOlluuSLR
where (Abs(BOlluuVRRcheck).ne.0._dp) BOlluuVRRcheck = (BOlluuVRRcheck-BOlluuVRR)/BOlluuVRRcheck
If(MaxVal(Abs(BOlluuVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuVRRcheck))
BOlluuVRRcheck=BOlluuVRR
where (Abs(BOlluuVLLcheck).ne.0._dp) BOlluuVLLcheck = (BOlluuVLLcheck-BOlluuVLL)/BOlluuVLLcheck
If(MaxVal(Abs(BOlluuVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuVLLcheck))
BOlluuVLLcheck=BOlluuVLL
where (Abs(BOlluuVRLcheck).ne.0._dp) BOlluuVRLcheck = (BOlluuVRLcheck-BOlluuVRL)/BOlluuVRLcheck
If(MaxVal(Abs(BOlluuVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuVRLcheck))
BOlluuVRLcheck=BOlluuVRL
where (Abs(BOlluuVLRcheck).ne.0._dp) BOlluuVLRcheck = (BOlluuVLRcheck-BOlluuVLR)/BOlluuVLRcheck
If(MaxVal(Abs(BOlluuVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuVLRcheck))
BOlluuVLRcheck=BOlluuVLR
where (Abs(BOlluuTLLcheck).ne.0._dp) BOlluuTLLcheck = (BOlluuTLLcheck-BOlluuTLL)/BOlluuTLLcheck
If(MaxVal(Abs(BOlluuTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuTLLcheck))
BOlluuTLLcheck=BOlluuTLL
where (Abs(BOlluuTLRcheck).ne.0._dp) BOlluuTLRcheck = (BOlluuTLRcheck-BOlluuTLR)/BOlluuTLRcheck
If(MaxVal(Abs(BOlluuTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuTLRcheck))
BOlluuTLRcheck=BOlluuTLR
where (Abs(BOlluuTRLcheck).ne.0._dp) BOlluuTRLcheck = (BOlluuTRLcheck-BOlluuTRL)/BOlluuTRLcheck
If(MaxVal(Abs(BOlluuTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuTRLcheck))
BOlluuTRLcheck=BOlluuTRL
where (Abs(BOlluuTRRcheck).ne.0._dp) BOlluuTRRcheck = (BOlluuTRRcheck-BOlluuTRR)/BOlluuTRRcheck
If(MaxVal(Abs(BOlluuTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BOlluuTRRcheck))
BOlluuTRRcheck=BOlluuTRR
where (Abs(PSOlluuSLLcheck).ne.0._dp) PSOlluuSLLcheck = (PSOlluuSLLcheck-PSOlluuSLL)/PSOlluuSLLcheck
If(MaxVal(Abs(PSOlluuSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuSLLcheck))
PSOlluuSLLcheck=PSOlluuSLL
where (Abs(PSOlluuSRRcheck).ne.0._dp) PSOlluuSRRcheck = (PSOlluuSRRcheck-PSOlluuSRR)/PSOlluuSRRcheck
If(MaxVal(Abs(PSOlluuSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuSRRcheck))
PSOlluuSRRcheck=PSOlluuSRR
where (Abs(PSOlluuSRLcheck).ne.0._dp) PSOlluuSRLcheck = (PSOlluuSRLcheck-PSOlluuSRL)/PSOlluuSRLcheck
If(MaxVal(Abs(PSOlluuSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuSRLcheck))
PSOlluuSRLcheck=PSOlluuSRL
where (Abs(PSOlluuSLRcheck).ne.0._dp) PSOlluuSLRcheck = (PSOlluuSLRcheck-PSOlluuSLR)/PSOlluuSLRcheck
If(MaxVal(Abs(PSOlluuSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuSLRcheck))
PSOlluuSLRcheck=PSOlluuSLR
where (Abs(PSOlluuVRRcheck).ne.0._dp) PSOlluuVRRcheck = (PSOlluuVRRcheck-PSOlluuVRR)/PSOlluuVRRcheck
If(MaxVal(Abs(PSOlluuVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuVRRcheck))
PSOlluuVRRcheck=PSOlluuVRR
where (Abs(PSOlluuVLLcheck).ne.0._dp) PSOlluuVLLcheck = (PSOlluuVLLcheck-PSOlluuVLL)/PSOlluuVLLcheck
If(MaxVal(Abs(PSOlluuVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuVLLcheck))
PSOlluuVLLcheck=PSOlluuVLL
where (Abs(PSOlluuVRLcheck).ne.0._dp) PSOlluuVRLcheck = (PSOlluuVRLcheck-PSOlluuVRL)/PSOlluuVRLcheck
If(MaxVal(Abs(PSOlluuVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuVRLcheck))
PSOlluuVRLcheck=PSOlluuVRL
where (Abs(PSOlluuVLRcheck).ne.0._dp) PSOlluuVLRcheck = (PSOlluuVLRcheck-PSOlluuVLR)/PSOlluuVLRcheck
If(MaxVal(Abs(PSOlluuVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuVLRcheck))
PSOlluuVLRcheck=PSOlluuVLR
where (Abs(PSOlluuTLLcheck).ne.0._dp) PSOlluuTLLcheck = (PSOlluuTLLcheck-PSOlluuTLL)/PSOlluuTLLcheck
If(MaxVal(Abs(PSOlluuTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuTLLcheck))
PSOlluuTLLcheck=PSOlluuTLL
where (Abs(PSOlluuTLRcheck).ne.0._dp) PSOlluuTLRcheck = (PSOlluuTLRcheck-PSOlluuTLR)/PSOlluuTLRcheck
If(MaxVal(Abs(PSOlluuTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuTLRcheck))
PSOlluuTLRcheck=PSOlluuTLR
where (Abs(PSOlluuTRLcheck).ne.0._dp) PSOlluuTRLcheck = (PSOlluuTRLcheck-PSOlluuTRL)/PSOlluuTRLcheck
If(MaxVal(Abs(PSOlluuTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuTRLcheck))
PSOlluuTRLcheck=PSOlluuTRL
where (Abs(PSOlluuTRRcheck).ne.0._dp) PSOlluuTRRcheck = (PSOlluuTRRcheck-PSOlluuTRR)/PSOlluuTRRcheck
If(MaxVal(Abs(PSOlluuTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSOlluuTRRcheck))
PSOlluuTRRcheck=PSOlluuTRR
where (Abs(PVOlluuSLLcheck).ne.0._dp) PVOlluuSLLcheck = (PVOlluuSLLcheck-PVOlluuSLL)/PVOlluuSLLcheck
If(MaxVal(Abs(PVOlluuSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuSLLcheck))
PVOlluuSLLcheck=PVOlluuSLL
where (Abs(PVOlluuSRRcheck).ne.0._dp) PVOlluuSRRcheck = (PVOlluuSRRcheck-PVOlluuSRR)/PVOlluuSRRcheck
If(MaxVal(Abs(PVOlluuSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuSRRcheck))
PVOlluuSRRcheck=PVOlluuSRR
where (Abs(PVOlluuSRLcheck).ne.0._dp) PVOlluuSRLcheck = (PVOlluuSRLcheck-PVOlluuSRL)/PVOlluuSRLcheck
If(MaxVal(Abs(PVOlluuSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuSRLcheck))
PVOlluuSRLcheck=PVOlluuSRL
where (Abs(PVOlluuSLRcheck).ne.0._dp) PVOlluuSLRcheck = (PVOlluuSLRcheck-PVOlluuSLR)/PVOlluuSLRcheck
If(MaxVal(Abs(PVOlluuSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuSLRcheck))
PVOlluuSLRcheck=PVOlluuSLR
where (Abs(PVOlluuVRRcheck).ne.0._dp) PVOlluuVRRcheck = (PVOlluuVRRcheck-PVOlluuVRR)/PVOlluuVRRcheck
If(MaxVal(Abs(PVOlluuVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuVRRcheck))
PVOlluuVRRcheck=PVOlluuVRR
where (Abs(PVOlluuVLLcheck).ne.0._dp) PVOlluuVLLcheck = (PVOlluuVLLcheck-PVOlluuVLL)/PVOlluuVLLcheck
If(MaxVal(Abs(PVOlluuVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuVLLcheck))
PVOlluuVLLcheck=PVOlluuVLL
where (Abs(PVOlluuVRLcheck).ne.0._dp) PVOlluuVRLcheck = (PVOlluuVRLcheck-PVOlluuVRL)/PVOlluuVRLcheck
If(MaxVal(Abs(PVOlluuVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuVRLcheck))
PVOlluuVRLcheck=PVOlluuVRL
where (Abs(PVOlluuVLRcheck).ne.0._dp) PVOlluuVLRcheck = (PVOlluuVLRcheck-PVOlluuVLR)/PVOlluuVLRcheck
If(MaxVal(Abs(PVOlluuVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuVLRcheck))
PVOlluuVLRcheck=PVOlluuVLR
where (Abs(PVOlluuTLLcheck).ne.0._dp) PVOlluuTLLcheck = (PVOlluuTLLcheck-PVOlluuTLL)/PVOlluuTLLcheck
If(MaxVal(Abs(PVOlluuTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuTLLcheck))
PVOlluuTLLcheck=PVOlluuTLL
where (Abs(PVOlluuTLRcheck).ne.0._dp) PVOlluuTLRcheck = (PVOlluuTLRcheck-PVOlluuTLR)/PVOlluuTLRcheck
If(MaxVal(Abs(PVOlluuTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuTLRcheck))
PVOlluuTLRcheck=PVOlluuTLR
where (Abs(PVOlluuTRLcheck).ne.0._dp) PVOlluuTRLcheck = (PVOlluuTRLcheck-PVOlluuTRL)/PVOlluuTRLcheck
If(MaxVal(Abs(PVOlluuTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuTRLcheck))
PVOlluuTRLcheck=PVOlluuTRL
where (Abs(PVOlluuTRRcheck).ne.0._dp) PVOlluuTRRcheck = (PVOlluuTRRcheck-PVOlluuTRR)/PVOlluuTRRcheck
If(MaxVal(Abs(PVOlluuTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVOlluuTRRcheck))
PVOlluuTRRcheck=PVOlluuTRR
where (Abs(TSOlluuSLLcheck).ne.0._dp) TSOlluuSLLcheck = (TSOlluuSLLcheck-TSOlluuSLL)/TSOlluuSLLcheck
If(MaxVal(Abs(TSOlluuSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuSLLcheck))
TSOlluuSLLcheck=TSOlluuSLL
where (Abs(TSOlluuSRRcheck).ne.0._dp) TSOlluuSRRcheck = (TSOlluuSRRcheck-TSOlluuSRR)/TSOlluuSRRcheck
If(MaxVal(Abs(TSOlluuSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuSRRcheck))
TSOlluuSRRcheck=TSOlluuSRR
where (Abs(TSOlluuSRLcheck).ne.0._dp) TSOlluuSRLcheck = (TSOlluuSRLcheck-TSOlluuSRL)/TSOlluuSRLcheck
If(MaxVal(Abs(TSOlluuSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuSRLcheck))
TSOlluuSRLcheck=TSOlluuSRL
where (Abs(TSOlluuSLRcheck).ne.0._dp) TSOlluuSLRcheck = (TSOlluuSLRcheck-TSOlluuSLR)/TSOlluuSLRcheck
If(MaxVal(Abs(TSOlluuSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuSLRcheck))
TSOlluuSLRcheck=TSOlluuSLR
where (Abs(TSOlluuVRRcheck).ne.0._dp) TSOlluuVRRcheck = (TSOlluuVRRcheck-TSOlluuVRR)/TSOlluuVRRcheck
If(MaxVal(Abs(TSOlluuVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuVRRcheck))
TSOlluuVRRcheck=TSOlluuVRR
where (Abs(TSOlluuVLLcheck).ne.0._dp) TSOlluuVLLcheck = (TSOlluuVLLcheck-TSOlluuVLL)/TSOlluuVLLcheck
If(MaxVal(Abs(TSOlluuVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuVLLcheck))
TSOlluuVLLcheck=TSOlluuVLL
where (Abs(TSOlluuVRLcheck).ne.0._dp) TSOlluuVRLcheck = (TSOlluuVRLcheck-TSOlluuVRL)/TSOlluuVRLcheck
If(MaxVal(Abs(TSOlluuVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuVRLcheck))
TSOlluuVRLcheck=TSOlluuVRL
where (Abs(TSOlluuVLRcheck).ne.0._dp) TSOlluuVLRcheck = (TSOlluuVLRcheck-TSOlluuVLR)/TSOlluuVLRcheck
If(MaxVal(Abs(TSOlluuVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuVLRcheck))
TSOlluuVLRcheck=TSOlluuVLR
where (Abs(TSOlluuTLLcheck).ne.0._dp) TSOlluuTLLcheck = (TSOlluuTLLcheck-TSOlluuTLL)/TSOlluuTLLcheck
If(MaxVal(Abs(TSOlluuTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuTLLcheck))
TSOlluuTLLcheck=TSOlluuTLL
where (Abs(TSOlluuTLRcheck).ne.0._dp) TSOlluuTLRcheck = (TSOlluuTLRcheck-TSOlluuTLR)/TSOlluuTLRcheck
If(MaxVal(Abs(TSOlluuTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuTLRcheck))
TSOlluuTLRcheck=TSOlluuTLR
where (Abs(TSOlluuTRLcheck).ne.0._dp) TSOlluuTRLcheck = (TSOlluuTRLcheck-TSOlluuTRL)/TSOlluuTRLcheck
If(MaxVal(Abs(TSOlluuTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuTRLcheck))
TSOlluuTRLcheck=TSOlluuTRL
where (Abs(TSOlluuTRRcheck).ne.0._dp) TSOlluuTRRcheck = (TSOlluuTRRcheck-TSOlluuTRR)/TSOlluuTRRcheck
If(MaxVal(Abs(TSOlluuTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSOlluuTRRcheck))
TSOlluuTRRcheck=TSOlluuTRR
where (Abs(TVOlluuSLLcheck).ne.0._dp) TVOlluuSLLcheck = (TVOlluuSLLcheck-TVOlluuSLL)/TVOlluuSLLcheck
If(MaxVal(Abs(TVOlluuSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuSLLcheck))
TVOlluuSLLcheck=TVOlluuSLL
where (Abs(TVOlluuSRRcheck).ne.0._dp) TVOlluuSRRcheck = (TVOlluuSRRcheck-TVOlluuSRR)/TVOlluuSRRcheck
If(MaxVal(Abs(TVOlluuSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuSRRcheck))
TVOlluuSRRcheck=TVOlluuSRR
where (Abs(TVOlluuSRLcheck).ne.0._dp) TVOlluuSRLcheck = (TVOlluuSRLcheck-TVOlluuSRL)/TVOlluuSRLcheck
If(MaxVal(Abs(TVOlluuSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuSRLcheck))
TVOlluuSRLcheck=TVOlluuSRL
where (Abs(TVOlluuSLRcheck).ne.0._dp) TVOlluuSLRcheck = (TVOlluuSLRcheck-TVOlluuSLR)/TVOlluuSLRcheck
If(MaxVal(Abs(TVOlluuSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuSLRcheck))
TVOlluuSLRcheck=TVOlluuSLR
where (Abs(TVOlluuVRRcheck).ne.0._dp) TVOlluuVRRcheck = (TVOlluuVRRcheck-TVOlluuVRR)/TVOlluuVRRcheck
If(MaxVal(Abs(TVOlluuVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuVRRcheck))
TVOlluuVRRcheck=TVOlluuVRR
where (Abs(TVOlluuVLLcheck).ne.0._dp) TVOlluuVLLcheck = (TVOlluuVLLcheck-TVOlluuVLL)/TVOlluuVLLcheck
If(MaxVal(Abs(TVOlluuVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuVLLcheck))
TVOlluuVLLcheck=TVOlluuVLL
where (Abs(TVOlluuVRLcheck).ne.0._dp) TVOlluuVRLcheck = (TVOlluuVRLcheck-TVOlluuVRL)/TVOlluuVRLcheck
If(MaxVal(Abs(TVOlluuVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuVRLcheck))
TVOlluuVRLcheck=TVOlluuVRL
where (Abs(TVOlluuVLRcheck).ne.0._dp) TVOlluuVLRcheck = (TVOlluuVLRcheck-TVOlluuVLR)/TVOlluuVLRcheck
If(MaxVal(Abs(TVOlluuVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuVLRcheck))
TVOlluuVLRcheck=TVOlluuVLR
where (Abs(TVOlluuTLLcheck).ne.0._dp) TVOlluuTLLcheck = (TVOlluuTLLcheck-TVOlluuTLL)/TVOlluuTLLcheck
If(MaxVal(Abs(TVOlluuTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuTLLcheck))
TVOlluuTLLcheck=TVOlluuTLL
where (Abs(TVOlluuTLRcheck).ne.0._dp) TVOlluuTLRcheck = (TVOlluuTLRcheck-TVOlluuTLR)/TVOlluuTLRcheck
If(MaxVal(Abs(TVOlluuTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuTLRcheck))
TVOlluuTLRcheck=TVOlluuTLR
where (Abs(TVOlluuTRLcheck).ne.0._dp) TVOlluuTRLcheck = (TVOlluuTRLcheck-TVOlluuTRL)/TVOlluuTRLcheck
If(MaxVal(Abs(TVOlluuTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuTRLcheck))
TVOlluuTRLcheck=TVOlluuTRL
where (Abs(TVOlluuTRRcheck).ne.0._dp) TVOlluuTRRcheck = (TVOlluuTRRcheck-TVOlluuTRR)/TVOlluuTRRcheck
If(MaxVal(Abs(TVOlluuTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVOlluuTRRcheck))
TVOlluuTRRcheck=TVOlluuTRR
where (Abs(BO4lSLLcheck).ne.0._dp) BO4lSLLcheck = (BO4lSLLcheck-BO4lSLL)/BO4lSLLcheck
If(MaxVal(Abs(BO4lSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSLLcheck))
BO4lSLLcheck=BO4lSLL
where (Abs(BO4lSRRcheck).ne.0._dp) BO4lSRRcheck = (BO4lSRRcheck-BO4lSRR)/BO4lSRRcheck
If(MaxVal(Abs(BO4lSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSRRcheck))
BO4lSRRcheck=BO4lSRR
where (Abs(BO4lSRLcheck).ne.0._dp) BO4lSRLcheck = (BO4lSRLcheck-BO4lSRL)/BO4lSRLcheck
If(MaxVal(Abs(BO4lSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSRLcheck))
BO4lSRLcheck=BO4lSRL
where (Abs(BO4lSLRcheck).ne.0._dp) BO4lSLRcheck = (BO4lSLRcheck-BO4lSLR)/BO4lSLRcheck
If(MaxVal(Abs(BO4lSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSLRcheck))
BO4lSLRcheck=BO4lSLR
where (Abs(BO4lVRRcheck).ne.0._dp) BO4lVRRcheck = (BO4lVRRcheck-BO4lVRR)/BO4lVRRcheck
If(MaxVal(Abs(BO4lVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVRRcheck))
BO4lVRRcheck=BO4lVRR
where (Abs(BO4lVLLcheck).ne.0._dp) BO4lVLLcheck = (BO4lVLLcheck-BO4lVLL)/BO4lVLLcheck
If(MaxVal(Abs(BO4lVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVLLcheck))
BO4lVLLcheck=BO4lVLL
where (Abs(BO4lVRLcheck).ne.0._dp) BO4lVRLcheck = (BO4lVRLcheck-BO4lVRL)/BO4lVRLcheck
If(MaxVal(Abs(BO4lVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVRLcheck))
BO4lVRLcheck=BO4lVRL
where (Abs(BO4lVLRcheck).ne.0._dp) BO4lVLRcheck = (BO4lVLRcheck-BO4lVLR)/BO4lVLRcheck
If(MaxVal(Abs(BO4lVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVLRcheck))
BO4lVLRcheck=BO4lVLR
where (Abs(BO4lTLLcheck).ne.0._dp) BO4lTLLcheck = (BO4lTLLcheck-BO4lTLL)/BO4lTLLcheck
If(MaxVal(Abs(BO4lTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTLLcheck))
BO4lTLLcheck=BO4lTLL
where (Abs(BO4lTLRcheck).ne.0._dp) BO4lTLRcheck = (BO4lTLRcheck-BO4lTLR)/BO4lTLRcheck
If(MaxVal(Abs(BO4lTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTLRcheck))
BO4lTLRcheck=BO4lTLR
where (Abs(BO4lTRLcheck).ne.0._dp) BO4lTRLcheck = (BO4lTRLcheck-BO4lTRL)/BO4lTRLcheck
If(MaxVal(Abs(BO4lTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTRLcheck))
BO4lTRLcheck=BO4lTRL
where (Abs(BO4lTRRcheck).ne.0._dp) BO4lTRRcheck = (BO4lTRRcheck-BO4lTRR)/BO4lTRRcheck
If(MaxVal(Abs(BO4lTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTRRcheck))
BO4lTRRcheck=BO4lTRR
where (Abs(PSO4lSLLcheck).ne.0._dp) PSO4lSLLcheck = (PSO4lSLLcheck-PSO4lSLL)/PSO4lSLLcheck
If(MaxVal(Abs(PSO4lSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSLLcheck))
PSO4lSLLcheck=PSO4lSLL
where (Abs(PSO4lSRRcheck).ne.0._dp) PSO4lSRRcheck = (PSO4lSRRcheck-PSO4lSRR)/PSO4lSRRcheck
If(MaxVal(Abs(PSO4lSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSRRcheck))
PSO4lSRRcheck=PSO4lSRR
where (Abs(PSO4lSRLcheck).ne.0._dp) PSO4lSRLcheck = (PSO4lSRLcheck-PSO4lSRL)/PSO4lSRLcheck
If(MaxVal(Abs(PSO4lSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSRLcheck))
PSO4lSRLcheck=PSO4lSRL
where (Abs(PSO4lSLRcheck).ne.0._dp) PSO4lSLRcheck = (PSO4lSLRcheck-PSO4lSLR)/PSO4lSLRcheck
If(MaxVal(Abs(PSO4lSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSLRcheck))
PSO4lSLRcheck=PSO4lSLR
where (Abs(PSO4lVRRcheck).ne.0._dp) PSO4lVRRcheck = (PSO4lVRRcheck-PSO4lVRR)/PSO4lVRRcheck
If(MaxVal(Abs(PSO4lVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVRRcheck))
PSO4lVRRcheck=PSO4lVRR
where (Abs(PSO4lVLLcheck).ne.0._dp) PSO4lVLLcheck = (PSO4lVLLcheck-PSO4lVLL)/PSO4lVLLcheck
If(MaxVal(Abs(PSO4lVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVLLcheck))
PSO4lVLLcheck=PSO4lVLL
where (Abs(PSO4lVRLcheck).ne.0._dp) PSO4lVRLcheck = (PSO4lVRLcheck-PSO4lVRL)/PSO4lVRLcheck
If(MaxVal(Abs(PSO4lVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVRLcheck))
PSO4lVRLcheck=PSO4lVRL
where (Abs(PSO4lVLRcheck).ne.0._dp) PSO4lVLRcheck = (PSO4lVLRcheck-PSO4lVLR)/PSO4lVLRcheck
If(MaxVal(Abs(PSO4lVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVLRcheck))
PSO4lVLRcheck=PSO4lVLR
where (Abs(PSO4lTLLcheck).ne.0._dp) PSO4lTLLcheck = (PSO4lTLLcheck-PSO4lTLL)/PSO4lTLLcheck
If(MaxVal(Abs(PSO4lTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTLLcheck))
PSO4lTLLcheck=PSO4lTLL
where (Abs(PSO4lTLRcheck).ne.0._dp) PSO4lTLRcheck = (PSO4lTLRcheck-PSO4lTLR)/PSO4lTLRcheck
If(MaxVal(Abs(PSO4lTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTLRcheck))
PSO4lTLRcheck=PSO4lTLR
where (Abs(PSO4lTRLcheck).ne.0._dp) PSO4lTRLcheck = (PSO4lTRLcheck-PSO4lTRL)/PSO4lTRLcheck
If(MaxVal(Abs(PSO4lTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTRLcheck))
PSO4lTRLcheck=PSO4lTRL
where (Abs(PSO4lTRRcheck).ne.0._dp) PSO4lTRRcheck = (PSO4lTRRcheck-PSO4lTRR)/PSO4lTRRcheck
If(MaxVal(Abs(PSO4lTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTRRcheck))
PSO4lTRRcheck=PSO4lTRR
where (Abs(PVO4lSLLcheck).ne.0._dp) PVO4lSLLcheck = (PVO4lSLLcheck-PVO4lSLL)/PVO4lSLLcheck
If(MaxVal(Abs(PVO4lSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSLLcheck))
PVO4lSLLcheck=PVO4lSLL
where (Abs(PVO4lSRRcheck).ne.0._dp) PVO4lSRRcheck = (PVO4lSRRcheck-PVO4lSRR)/PVO4lSRRcheck
If(MaxVal(Abs(PVO4lSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSRRcheck))
PVO4lSRRcheck=PVO4lSRR
where (Abs(PVO4lSRLcheck).ne.0._dp) PVO4lSRLcheck = (PVO4lSRLcheck-PVO4lSRL)/PVO4lSRLcheck
If(MaxVal(Abs(PVO4lSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSRLcheck))
PVO4lSRLcheck=PVO4lSRL
where (Abs(PVO4lSLRcheck).ne.0._dp) PVO4lSLRcheck = (PVO4lSLRcheck-PVO4lSLR)/PVO4lSLRcheck
If(MaxVal(Abs(PVO4lSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSLRcheck))
PVO4lSLRcheck=PVO4lSLR
where (Abs(PVO4lVRRcheck).ne.0._dp) PVO4lVRRcheck = (PVO4lVRRcheck-PVO4lVRR)/PVO4lVRRcheck
If(MaxVal(Abs(PVO4lVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVRRcheck))
PVO4lVRRcheck=PVO4lVRR
where (Abs(PVO4lVLLcheck).ne.0._dp) PVO4lVLLcheck = (PVO4lVLLcheck-PVO4lVLL)/PVO4lVLLcheck
If(MaxVal(Abs(PVO4lVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVLLcheck))
PVO4lVLLcheck=PVO4lVLL
where (Abs(PVO4lVRLcheck).ne.0._dp) PVO4lVRLcheck = (PVO4lVRLcheck-PVO4lVRL)/PVO4lVRLcheck
If(MaxVal(Abs(PVO4lVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVRLcheck))
PVO4lVRLcheck=PVO4lVRL
where (Abs(PVO4lVLRcheck).ne.0._dp) PVO4lVLRcheck = (PVO4lVLRcheck-PVO4lVLR)/PVO4lVLRcheck
If(MaxVal(Abs(PVO4lVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVLRcheck))
PVO4lVLRcheck=PVO4lVLR
where (Abs(PVO4lTLLcheck).ne.0._dp) PVO4lTLLcheck = (PVO4lTLLcheck-PVO4lTLL)/PVO4lTLLcheck
If(MaxVal(Abs(PVO4lTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTLLcheck))
PVO4lTLLcheck=PVO4lTLL
where (Abs(PVO4lTLRcheck).ne.0._dp) PVO4lTLRcheck = (PVO4lTLRcheck-PVO4lTLR)/PVO4lTLRcheck
If(MaxVal(Abs(PVO4lTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTLRcheck))
PVO4lTLRcheck=PVO4lTLR
where (Abs(PVO4lTRLcheck).ne.0._dp) PVO4lTRLcheck = (PVO4lTRLcheck-PVO4lTRL)/PVO4lTRLcheck
If(MaxVal(Abs(PVO4lTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTRLcheck))
PVO4lTRLcheck=PVO4lTRL
where (Abs(PVO4lTRRcheck).ne.0._dp) PVO4lTRRcheck = (PVO4lTRRcheck-PVO4lTRR)/PVO4lTRRcheck
If(MaxVal(Abs(PVO4lTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTRRcheck))
PVO4lTRRcheck=PVO4lTRR
where (Abs(TSO4lSLLcheck).ne.0._dp) TSO4lSLLcheck = (TSO4lSLLcheck-TSO4lSLL)/TSO4lSLLcheck
If(MaxVal(Abs(TSO4lSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSLLcheck))
TSO4lSLLcheck=TSO4lSLL
where (Abs(TSO4lSRRcheck).ne.0._dp) TSO4lSRRcheck = (TSO4lSRRcheck-TSO4lSRR)/TSO4lSRRcheck
If(MaxVal(Abs(TSO4lSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSRRcheck))
TSO4lSRRcheck=TSO4lSRR
where (Abs(TSO4lSRLcheck).ne.0._dp) TSO4lSRLcheck = (TSO4lSRLcheck-TSO4lSRL)/TSO4lSRLcheck
If(MaxVal(Abs(TSO4lSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSRLcheck))
TSO4lSRLcheck=TSO4lSRL
where (Abs(TSO4lSLRcheck).ne.0._dp) TSO4lSLRcheck = (TSO4lSLRcheck-TSO4lSLR)/TSO4lSLRcheck
If(MaxVal(Abs(TSO4lSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSLRcheck))
TSO4lSLRcheck=TSO4lSLR
where (Abs(TSO4lVRRcheck).ne.0._dp) TSO4lVRRcheck = (TSO4lVRRcheck-TSO4lVRR)/TSO4lVRRcheck
If(MaxVal(Abs(TSO4lVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVRRcheck))
TSO4lVRRcheck=TSO4lVRR
where (Abs(TSO4lVLLcheck).ne.0._dp) TSO4lVLLcheck = (TSO4lVLLcheck-TSO4lVLL)/TSO4lVLLcheck
If(MaxVal(Abs(TSO4lVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVLLcheck))
TSO4lVLLcheck=TSO4lVLL
where (Abs(TSO4lVRLcheck).ne.0._dp) TSO4lVRLcheck = (TSO4lVRLcheck-TSO4lVRL)/TSO4lVRLcheck
If(MaxVal(Abs(TSO4lVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVRLcheck))
TSO4lVRLcheck=TSO4lVRL
where (Abs(TSO4lVLRcheck).ne.0._dp) TSO4lVLRcheck = (TSO4lVLRcheck-TSO4lVLR)/TSO4lVLRcheck
If(MaxVal(Abs(TSO4lVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVLRcheck))
TSO4lVLRcheck=TSO4lVLR
where (Abs(TSO4lTLLcheck).ne.0._dp) TSO4lTLLcheck = (TSO4lTLLcheck-TSO4lTLL)/TSO4lTLLcheck
If(MaxVal(Abs(TSO4lTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTLLcheck))
TSO4lTLLcheck=TSO4lTLL
where (Abs(TSO4lTLRcheck).ne.0._dp) TSO4lTLRcheck = (TSO4lTLRcheck-TSO4lTLR)/TSO4lTLRcheck
If(MaxVal(Abs(TSO4lTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTLRcheck))
TSO4lTLRcheck=TSO4lTLR
where (Abs(TSO4lTRLcheck).ne.0._dp) TSO4lTRLcheck = (TSO4lTRLcheck-TSO4lTRL)/TSO4lTRLcheck
If(MaxVal(Abs(TSO4lTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTRLcheck))
TSO4lTRLcheck=TSO4lTRL
where (Abs(TSO4lTRRcheck).ne.0._dp) TSO4lTRRcheck = (TSO4lTRRcheck-TSO4lTRR)/TSO4lTRRcheck
If(MaxVal(Abs(TSO4lTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTRRcheck))
TSO4lTRRcheck=TSO4lTRR
where (Abs(TVO4lSLLcheck).ne.0._dp) TVO4lSLLcheck = (TVO4lSLLcheck-TVO4lSLL)/TVO4lSLLcheck
If(MaxVal(Abs(TVO4lSLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSLLcheck))
TVO4lSLLcheck=TVO4lSLL
where (Abs(TVO4lSRRcheck).ne.0._dp) TVO4lSRRcheck = (TVO4lSRRcheck-TVO4lSRR)/TVO4lSRRcheck
If(MaxVal(Abs(TVO4lSRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSRRcheck))
TVO4lSRRcheck=TVO4lSRR
where (Abs(TVO4lSRLcheck).ne.0._dp) TVO4lSRLcheck = (TVO4lSRLcheck-TVO4lSRL)/TVO4lSRLcheck
If(MaxVal(Abs(TVO4lSRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSRLcheck))
TVO4lSRLcheck=TVO4lSRL
where (Abs(TVO4lSLRcheck).ne.0._dp) TVO4lSLRcheck = (TVO4lSLRcheck-TVO4lSLR)/TVO4lSLRcheck
If(MaxVal(Abs(TVO4lSLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSLRcheck))
TVO4lSLRcheck=TVO4lSLR
where (Abs(TVO4lVRRcheck).ne.0._dp) TVO4lVRRcheck = (TVO4lVRRcheck-TVO4lVRR)/TVO4lVRRcheck
If(MaxVal(Abs(TVO4lVRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVRRcheck))
TVO4lVRRcheck=TVO4lVRR
where (Abs(TVO4lVLLcheck).ne.0._dp) TVO4lVLLcheck = (TVO4lVLLcheck-TVO4lVLL)/TVO4lVLLcheck
If(MaxVal(Abs(TVO4lVLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVLLcheck))
TVO4lVLLcheck=TVO4lVLL
where (Abs(TVO4lVRLcheck).ne.0._dp) TVO4lVRLcheck = (TVO4lVRLcheck-TVO4lVRL)/TVO4lVRLcheck
If(MaxVal(Abs(TVO4lVRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVRLcheck))
TVO4lVRLcheck=TVO4lVRL
where (Abs(TVO4lVLRcheck).ne.0._dp) TVO4lVLRcheck = (TVO4lVLRcheck-TVO4lVLR)/TVO4lVLRcheck
If(MaxVal(Abs(TVO4lVLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVLRcheck))
TVO4lVLRcheck=TVO4lVLR
where (Abs(TVO4lTLLcheck).ne.0._dp) TVO4lTLLcheck = (TVO4lTLLcheck-TVO4lTLL)/TVO4lTLLcheck
If(MaxVal(Abs(TVO4lTLLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTLLcheck))
TVO4lTLLcheck=TVO4lTLL
where (Abs(TVO4lTLRcheck).ne.0._dp) TVO4lTLRcheck = (TVO4lTLRcheck-TVO4lTLR)/TVO4lTLRcheck
If(MaxVal(Abs(TVO4lTLRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTLRcheck))
TVO4lTLRcheck=TVO4lTLR
where (Abs(TVO4lTRLcheck).ne.0._dp) TVO4lTRLcheck = (TVO4lTRLcheck-TVO4lTRL)/TVO4lTRLcheck
If(MaxVal(Abs(TVO4lTRLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTRLcheck))
TVO4lTRLcheck=TVO4lTRL
where (Abs(TVO4lTRRcheck).ne.0._dp) TVO4lTRRcheck = (TVO4lTRRcheck-TVO4lTRR)/TVO4lTRRcheck
If(MaxVal(Abs(TVO4lTRRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTRRcheck))
TVO4lTRRcheck=TVO4lTRR
where (Abs(BO4lSLLcrosscheck).ne.0._dp) BO4lSLLcrosscheck = (BO4lSLLcrosscheck-BO4lSLLcross)/BO4lSLLcrosscheck
If(MaxVal(Abs(BO4lSLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSLLcrosscheck))
BO4lSLLcrosscheck=BO4lSLLcross
where (Abs(BO4lSRRcrosscheck).ne.0._dp) BO4lSRRcrosscheck = (BO4lSRRcrosscheck-BO4lSRRcross)/BO4lSRRcrosscheck
If(MaxVal(Abs(BO4lSRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSRRcrosscheck))
BO4lSRRcrosscheck=BO4lSRRcross
where (Abs(BO4lSRLcrosscheck).ne.0._dp) BO4lSRLcrosscheck = (BO4lSRLcrosscheck-BO4lSRLcross)/BO4lSRLcrosscheck
If(MaxVal(Abs(BO4lSRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSRLcrosscheck))
BO4lSRLcrosscheck=BO4lSRLcross
where (Abs(BO4lSLRcrosscheck).ne.0._dp) BO4lSLRcrosscheck = (BO4lSLRcrosscheck-BO4lSLRcross)/BO4lSLRcrosscheck
If(MaxVal(Abs(BO4lSLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lSLRcrosscheck))
BO4lSLRcrosscheck=BO4lSLRcross
where (Abs(BO4lVRRcrosscheck).ne.0._dp) BO4lVRRcrosscheck = (BO4lVRRcrosscheck-BO4lVRRcross)/BO4lVRRcrosscheck
If(MaxVal(Abs(BO4lVRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVRRcrosscheck))
BO4lVRRcrosscheck=BO4lVRRcross
where (Abs(BO4lVLLcrosscheck).ne.0._dp) BO4lVLLcrosscheck = (BO4lVLLcrosscheck-BO4lVLLcross)/BO4lVLLcrosscheck
If(MaxVal(Abs(BO4lVLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVLLcrosscheck))
BO4lVLLcrosscheck=BO4lVLLcross
where (Abs(BO4lVRLcrosscheck).ne.0._dp) BO4lVRLcrosscheck = (BO4lVRLcrosscheck-BO4lVRLcross)/BO4lVRLcrosscheck
If(MaxVal(Abs(BO4lVRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVRLcrosscheck))
BO4lVRLcrosscheck=BO4lVRLcross
where (Abs(BO4lVLRcrosscheck).ne.0._dp) BO4lVLRcrosscheck = (BO4lVLRcrosscheck-BO4lVLRcross)/BO4lVLRcrosscheck
If(MaxVal(Abs(BO4lVLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lVLRcrosscheck))
BO4lVLRcrosscheck=BO4lVLRcross
where (Abs(BO4lTLLcrosscheck).ne.0._dp) BO4lTLLcrosscheck = (BO4lTLLcrosscheck-BO4lTLLcross)/BO4lTLLcrosscheck
If(MaxVal(Abs(BO4lTLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTLLcrosscheck))
BO4lTLLcrosscheck=BO4lTLLcross
where (Abs(BO4lTLRcrosscheck).ne.0._dp) BO4lTLRcrosscheck = (BO4lTLRcrosscheck-BO4lTLRcross)/BO4lTLRcrosscheck
If(MaxVal(Abs(BO4lTLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTLRcrosscheck))
BO4lTLRcrosscheck=BO4lTLRcross
where (Abs(BO4lTRLcrosscheck).ne.0._dp) BO4lTRLcrosscheck = (BO4lTRLcrosscheck-BO4lTRLcross)/BO4lTRLcrosscheck
If(MaxVal(Abs(BO4lTRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTRLcrosscheck))
BO4lTRLcrosscheck=BO4lTRLcross
where (Abs(BO4lTRRcrosscheck).ne.0._dp) BO4lTRRcrosscheck = (BO4lTRRcrosscheck-BO4lTRRcross)/BO4lTRRcrosscheck
If(MaxVal(Abs(BO4lTRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(BO4lTRRcrosscheck))
BO4lTRRcrosscheck=BO4lTRRcross
where (Abs(PSO4lSLLcrosscheck).ne.0._dp) PSO4lSLLcrosscheck = (PSO4lSLLcrosscheck-PSO4lSLLcross)/PSO4lSLLcrosscheck
If(MaxVal(Abs(PSO4lSLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSLLcrosscheck))
PSO4lSLLcrosscheck=PSO4lSLLcross
where (Abs(PSO4lSRRcrosscheck).ne.0._dp) PSO4lSRRcrosscheck = (PSO4lSRRcrosscheck-PSO4lSRRcross)/PSO4lSRRcrosscheck
If(MaxVal(Abs(PSO4lSRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSRRcrosscheck))
PSO4lSRRcrosscheck=PSO4lSRRcross
where (Abs(PSO4lSRLcrosscheck).ne.0._dp) PSO4lSRLcrosscheck = (PSO4lSRLcrosscheck-PSO4lSRLcross)/PSO4lSRLcrosscheck
If(MaxVal(Abs(PSO4lSRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSRLcrosscheck))
PSO4lSRLcrosscheck=PSO4lSRLcross
where (Abs(PSO4lSLRcrosscheck).ne.0._dp) PSO4lSLRcrosscheck = (PSO4lSLRcrosscheck-PSO4lSLRcross)/PSO4lSLRcrosscheck
If(MaxVal(Abs(PSO4lSLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lSLRcrosscheck))
PSO4lSLRcrosscheck=PSO4lSLRcross
where (Abs(PSO4lVRRcrosscheck).ne.0._dp) PSO4lVRRcrosscheck = (PSO4lVRRcrosscheck-PSO4lVRRcross)/PSO4lVRRcrosscheck
If(MaxVal(Abs(PSO4lVRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVRRcrosscheck))
PSO4lVRRcrosscheck=PSO4lVRRcross
where (Abs(PSO4lVLLcrosscheck).ne.0._dp) PSO4lVLLcrosscheck = (PSO4lVLLcrosscheck-PSO4lVLLcross)/PSO4lVLLcrosscheck
If(MaxVal(Abs(PSO4lVLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVLLcrosscheck))
PSO4lVLLcrosscheck=PSO4lVLLcross
where (Abs(PSO4lVRLcrosscheck).ne.0._dp) PSO4lVRLcrosscheck = (PSO4lVRLcrosscheck-PSO4lVRLcross)/PSO4lVRLcrosscheck
If(MaxVal(Abs(PSO4lVRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVRLcrosscheck))
PSO4lVRLcrosscheck=PSO4lVRLcross
where (Abs(PSO4lVLRcrosscheck).ne.0._dp) PSO4lVLRcrosscheck = (PSO4lVLRcrosscheck-PSO4lVLRcross)/PSO4lVLRcrosscheck
If(MaxVal(Abs(PSO4lVLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lVLRcrosscheck))
PSO4lVLRcrosscheck=PSO4lVLRcross
where (Abs(PSO4lTLLcrosscheck).ne.0._dp) PSO4lTLLcrosscheck = (PSO4lTLLcrosscheck-PSO4lTLLcross)/PSO4lTLLcrosscheck
If(MaxVal(Abs(PSO4lTLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTLLcrosscheck))
PSO4lTLLcrosscheck=PSO4lTLLcross
where (Abs(PSO4lTLRcrosscheck).ne.0._dp) PSO4lTLRcrosscheck = (PSO4lTLRcrosscheck-PSO4lTLRcross)/PSO4lTLRcrosscheck
If(MaxVal(Abs(PSO4lTLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTLRcrosscheck))
PSO4lTLRcrosscheck=PSO4lTLRcross
where (Abs(PSO4lTRLcrosscheck).ne.0._dp) PSO4lTRLcrosscheck = (PSO4lTRLcrosscheck-PSO4lTRLcross)/PSO4lTRLcrosscheck
If(MaxVal(Abs(PSO4lTRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTRLcrosscheck))
PSO4lTRLcrosscheck=PSO4lTRLcross
where (Abs(PSO4lTRRcrosscheck).ne.0._dp) PSO4lTRRcrosscheck = (PSO4lTRRcrosscheck-PSO4lTRRcross)/PSO4lTRRcrosscheck
If(MaxVal(Abs(PSO4lTRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PSO4lTRRcrosscheck))
PSO4lTRRcrosscheck=PSO4lTRRcross
where (Abs(PVO4lSLLcrosscheck).ne.0._dp) PVO4lSLLcrosscheck = (PVO4lSLLcrosscheck-PVO4lSLLcross)/PVO4lSLLcrosscheck
If(MaxVal(Abs(PVO4lSLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSLLcrosscheck))
PVO4lSLLcrosscheck=PVO4lSLLcross
where (Abs(PVO4lSRRcrosscheck).ne.0._dp) PVO4lSRRcrosscheck = (PVO4lSRRcrosscheck-PVO4lSRRcross)/PVO4lSRRcrosscheck
If(MaxVal(Abs(PVO4lSRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSRRcrosscheck))
PVO4lSRRcrosscheck=PVO4lSRRcross
where (Abs(PVO4lSRLcrosscheck).ne.0._dp) PVO4lSRLcrosscheck = (PVO4lSRLcrosscheck-PVO4lSRLcross)/PVO4lSRLcrosscheck
If(MaxVal(Abs(PVO4lSRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSRLcrosscheck))
PVO4lSRLcrosscheck=PVO4lSRLcross
where (Abs(PVO4lSLRcrosscheck).ne.0._dp) PVO4lSLRcrosscheck = (PVO4lSLRcrosscheck-PVO4lSLRcross)/PVO4lSLRcrosscheck
If(MaxVal(Abs(PVO4lSLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lSLRcrosscheck))
PVO4lSLRcrosscheck=PVO4lSLRcross
where (Abs(PVO4lVRRcrosscheck).ne.0._dp) PVO4lVRRcrosscheck = (PVO4lVRRcrosscheck-PVO4lVRRcross)/PVO4lVRRcrosscheck
If(MaxVal(Abs(PVO4lVRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVRRcrosscheck))
PVO4lVRRcrosscheck=PVO4lVRRcross
where (Abs(PVO4lVLLcrosscheck).ne.0._dp) PVO4lVLLcrosscheck = (PVO4lVLLcrosscheck-PVO4lVLLcross)/PVO4lVLLcrosscheck
If(MaxVal(Abs(PVO4lVLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVLLcrosscheck))
PVO4lVLLcrosscheck=PVO4lVLLcross
where (Abs(PVO4lVRLcrosscheck).ne.0._dp) PVO4lVRLcrosscheck = (PVO4lVRLcrosscheck-PVO4lVRLcross)/PVO4lVRLcrosscheck
If(MaxVal(Abs(PVO4lVRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVRLcrosscheck))
PVO4lVRLcrosscheck=PVO4lVRLcross
where (Abs(PVO4lVLRcrosscheck).ne.0._dp) PVO4lVLRcrosscheck = (PVO4lVLRcrosscheck-PVO4lVLRcross)/PVO4lVLRcrosscheck
If(MaxVal(Abs(PVO4lVLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lVLRcrosscheck))
PVO4lVLRcrosscheck=PVO4lVLRcross
where (Abs(PVO4lTLLcrosscheck).ne.0._dp) PVO4lTLLcrosscheck = (PVO4lTLLcrosscheck-PVO4lTLLcross)/PVO4lTLLcrosscheck
If(MaxVal(Abs(PVO4lTLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTLLcrosscheck))
PVO4lTLLcrosscheck=PVO4lTLLcross
where (Abs(PVO4lTLRcrosscheck).ne.0._dp) PVO4lTLRcrosscheck = (PVO4lTLRcrosscheck-PVO4lTLRcross)/PVO4lTLRcrosscheck
If(MaxVal(Abs(PVO4lTLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTLRcrosscheck))
PVO4lTLRcrosscheck=PVO4lTLRcross
where (Abs(PVO4lTRLcrosscheck).ne.0._dp) PVO4lTRLcrosscheck = (PVO4lTRLcrosscheck-PVO4lTRLcross)/PVO4lTRLcrosscheck
If(MaxVal(Abs(PVO4lTRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTRLcrosscheck))
PVO4lTRLcrosscheck=PVO4lTRLcross
where (Abs(PVO4lTRRcrosscheck).ne.0._dp) PVO4lTRRcrosscheck = (PVO4lTRRcrosscheck-PVO4lTRRcross)/PVO4lTRRcrosscheck
If(MaxVal(Abs(PVO4lTRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(PVO4lTRRcrosscheck))
PVO4lTRRcrosscheck=PVO4lTRRcross
where (Abs(TSO4lSLLcrosscheck).ne.0._dp) TSO4lSLLcrosscheck = (TSO4lSLLcrosscheck-TSO4lSLLcross)/TSO4lSLLcrosscheck
If(MaxVal(Abs(TSO4lSLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSLLcrosscheck))
TSO4lSLLcrosscheck=TSO4lSLLcross
where (Abs(TSO4lSRRcrosscheck).ne.0._dp) TSO4lSRRcrosscheck = (TSO4lSRRcrosscheck-TSO4lSRRcross)/TSO4lSRRcrosscheck
If(MaxVal(Abs(TSO4lSRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSRRcrosscheck))
TSO4lSRRcrosscheck=TSO4lSRRcross
where (Abs(TSO4lSRLcrosscheck).ne.0._dp) TSO4lSRLcrosscheck = (TSO4lSRLcrosscheck-TSO4lSRLcross)/TSO4lSRLcrosscheck
If(MaxVal(Abs(TSO4lSRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSRLcrosscheck))
TSO4lSRLcrosscheck=TSO4lSRLcross
where (Abs(TSO4lSLRcrosscheck).ne.0._dp) TSO4lSLRcrosscheck = (TSO4lSLRcrosscheck-TSO4lSLRcross)/TSO4lSLRcrosscheck
If(MaxVal(Abs(TSO4lSLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lSLRcrosscheck))
TSO4lSLRcrosscheck=TSO4lSLRcross
where (Abs(TSO4lVRRcrosscheck).ne.0._dp) TSO4lVRRcrosscheck = (TSO4lVRRcrosscheck-TSO4lVRRcross)/TSO4lVRRcrosscheck
If(MaxVal(Abs(TSO4lVRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVRRcrosscheck))
TSO4lVRRcrosscheck=TSO4lVRRcross
where (Abs(TSO4lVLLcrosscheck).ne.0._dp) TSO4lVLLcrosscheck = (TSO4lVLLcrosscheck-TSO4lVLLcross)/TSO4lVLLcrosscheck
If(MaxVal(Abs(TSO4lVLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVLLcrosscheck))
TSO4lVLLcrosscheck=TSO4lVLLcross
where (Abs(TSO4lVRLcrosscheck).ne.0._dp) TSO4lVRLcrosscheck = (TSO4lVRLcrosscheck-TSO4lVRLcross)/TSO4lVRLcrosscheck
If(MaxVal(Abs(TSO4lVRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVRLcrosscheck))
TSO4lVRLcrosscheck=TSO4lVRLcross
where (Abs(TSO4lVLRcrosscheck).ne.0._dp) TSO4lVLRcrosscheck = (TSO4lVLRcrosscheck-TSO4lVLRcross)/TSO4lVLRcrosscheck
If(MaxVal(Abs(TSO4lVLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lVLRcrosscheck))
TSO4lVLRcrosscheck=TSO4lVLRcross
where (Abs(TSO4lTLLcrosscheck).ne.0._dp) TSO4lTLLcrosscheck = (TSO4lTLLcrosscheck-TSO4lTLLcross)/TSO4lTLLcrosscheck
If(MaxVal(Abs(TSO4lTLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTLLcrosscheck))
TSO4lTLLcrosscheck=TSO4lTLLcross
where (Abs(TSO4lTLRcrosscheck).ne.0._dp) TSO4lTLRcrosscheck = (TSO4lTLRcrosscheck-TSO4lTLRcross)/TSO4lTLRcrosscheck
If(MaxVal(Abs(TSO4lTLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTLRcrosscheck))
TSO4lTLRcrosscheck=TSO4lTLRcross
where (Abs(TSO4lTRLcrosscheck).ne.0._dp) TSO4lTRLcrosscheck = (TSO4lTRLcrosscheck-TSO4lTRLcross)/TSO4lTRLcrosscheck
If(MaxVal(Abs(TSO4lTRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTRLcrosscheck))
TSO4lTRLcrosscheck=TSO4lTRLcross
where (Abs(TSO4lTRRcrosscheck).ne.0._dp) TSO4lTRRcrosscheck = (TSO4lTRRcrosscheck-TSO4lTRRcross)/TSO4lTRRcrosscheck
If(MaxVal(Abs(TSO4lTRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TSO4lTRRcrosscheck))
TSO4lTRRcrosscheck=TSO4lTRRcross
where (Abs(TVO4lSLLcrosscheck).ne.0._dp) TVO4lSLLcrosscheck = (TVO4lSLLcrosscheck-TVO4lSLLcross)/TVO4lSLLcrosscheck
If(MaxVal(Abs(TVO4lSLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSLLcrosscheck))
TVO4lSLLcrosscheck=TVO4lSLLcross
where (Abs(TVO4lSRRcrosscheck).ne.0._dp) TVO4lSRRcrosscheck = (TVO4lSRRcrosscheck-TVO4lSRRcross)/TVO4lSRRcrosscheck
If(MaxVal(Abs(TVO4lSRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSRRcrosscheck))
TVO4lSRRcrosscheck=TVO4lSRRcross
where (Abs(TVO4lSRLcrosscheck).ne.0._dp) TVO4lSRLcrosscheck = (TVO4lSRLcrosscheck-TVO4lSRLcross)/TVO4lSRLcrosscheck
If(MaxVal(Abs(TVO4lSRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSRLcrosscheck))
TVO4lSRLcrosscheck=TVO4lSRLcross
where (Abs(TVO4lSLRcrosscheck).ne.0._dp) TVO4lSLRcrosscheck = (TVO4lSLRcrosscheck-TVO4lSLRcross)/TVO4lSLRcrosscheck
If(MaxVal(Abs(TVO4lSLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lSLRcrosscheck))
TVO4lSLRcrosscheck=TVO4lSLRcross
where (Abs(TVO4lVRRcrosscheck).ne.0._dp) TVO4lVRRcrosscheck = (TVO4lVRRcrosscheck-TVO4lVRRcross)/TVO4lVRRcrosscheck
If(MaxVal(Abs(TVO4lVRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVRRcrosscheck))
TVO4lVRRcrosscheck=TVO4lVRRcross
where (Abs(TVO4lVLLcrosscheck).ne.0._dp) TVO4lVLLcrosscheck = (TVO4lVLLcrosscheck-TVO4lVLLcross)/TVO4lVLLcrosscheck
If(MaxVal(Abs(TVO4lVLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVLLcrosscheck))
TVO4lVLLcrosscheck=TVO4lVLLcross
where (Abs(TVO4lVRLcrosscheck).ne.0._dp) TVO4lVRLcrosscheck = (TVO4lVRLcrosscheck-TVO4lVRLcross)/TVO4lVRLcrosscheck
If(MaxVal(Abs(TVO4lVRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVRLcrosscheck))
TVO4lVRLcrosscheck=TVO4lVRLcross
where (Abs(TVO4lVLRcrosscheck).ne.0._dp) TVO4lVLRcrosscheck = (TVO4lVLRcrosscheck-TVO4lVLRcross)/TVO4lVLRcrosscheck
If(MaxVal(Abs(TVO4lVLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lVLRcrosscheck))
TVO4lVLRcrosscheck=TVO4lVLRcross
where (Abs(TVO4lTLLcrosscheck).ne.0._dp) TVO4lTLLcrosscheck = (TVO4lTLLcrosscheck-TVO4lTLLcross)/TVO4lTLLcrosscheck
If(MaxVal(Abs(TVO4lTLLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTLLcrosscheck))
TVO4lTLLcrosscheck=TVO4lTLLcross
where (Abs(TVO4lTLRcrosscheck).ne.0._dp) TVO4lTLRcrosscheck = (TVO4lTLRcrosscheck-TVO4lTLRcross)/TVO4lTLRcrosscheck
If(MaxVal(Abs(TVO4lTLRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTLRcrosscheck))
TVO4lTLRcrosscheck=TVO4lTLRcross
where (Abs(TVO4lTRLcrosscheck).ne.0._dp) TVO4lTRLcrosscheck = (TVO4lTRLcrosscheck-TVO4lTRLcross)/TVO4lTRLcrosscheck
If(MaxVal(Abs(TVO4lTRLcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTRLcrosscheck))
TVO4lTRLcrosscheck=TVO4lTRLcross
where (Abs(TVO4lTRRcrosscheck).ne.0._dp) TVO4lTRRcrosscheck = (TVO4lTRRcrosscheck-TVO4lTRRcross)/TVO4lTRRcrosscheck
If(MaxVal(Abs(TVO4lTRRcrosscheck)).gt.maxdiff) maxdiff=MaxVal(Abs(TVO4lTRRcrosscheck))
TVO4lTRRcrosscheck=TVO4lTRRcross
where (Abs(OA2lSLcheck).ne.0._dp) OA2lSLcheck = (OA2lSLcheck-OA2lSL)/OA2lSLcheck
If(MaxVal(Abs(OA2lSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2lSLcheck))
OA2lSLcheck=OA2lSL
where (Abs(OA2lSRcheck).ne.0._dp) OA2lSRcheck = (OA2lSRcheck-OA2lSR)/OA2lSRcheck
If(MaxVal(Abs(OA2lSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA2lSRcheck))
OA2lSRcheck=OA2lSR
where (Abs(OA1Lcheck).ne.0._dp) OA1Lcheck = (OA1Lcheck-OA1L)/OA1Lcheck
If(MaxVal(Abs(OA1Lcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA1Lcheck))
OA1Lcheck=OA1L
where (Abs(OA1Rcheck).ne.0._dp) OA1Rcheck = (OA1Rcheck-OA1R)/OA1Rcheck
If(MaxVal(Abs(OA1Rcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OA1Rcheck))
OA1Rcheck=OA1R
where (Abs(OH2lSLcheck).ne.0._dp) OH2lSLcheck = (OH2lSLcheck-OH2lSL)/OH2lSLcheck
If(MaxVal(Abs(OH2lSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OH2lSLcheck))
OH2lSLcheck=OH2lSL
where (Abs(OH2lSRcheck).ne.0._dp) OH2lSRcheck = (OH2lSRcheck-OH2lSR)/OH2lSRcheck
If(MaxVal(Abs(OH2lSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OH2lSRcheck))
OH2lSRcheck=OH2lSR
where (Abs(OZ2lSLcheck).ne.0._dp) OZ2lSLcheck = (OZ2lSLcheck-OZ2lSL)/OZ2lSLcheck
If(MaxVal(Abs(OZ2lSLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OZ2lSLcheck))
OZ2lSLcheck=OZ2lSL
where (Abs(OZ2lSRcheck).ne.0._dp) OZ2lSRcheck = (OZ2lSRcheck-OZ2lSR)/OZ2lSRcheck
If(MaxVal(Abs(OZ2lSRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OZ2lSRcheck))
OZ2lSRcheck=OZ2lSR
where (Abs(OZ2lVLcheck).ne.0._dp) OZ2lVLcheck = (OZ2lVLcheck-OZ2lVL)/OZ2lVLcheck
If(MaxVal(Abs(OZ2lVLcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OZ2lVLcheck))
OZ2lVLcheck=OZ2lVL
where (Abs(OZ2lVRcheck).ne.0._dp) OZ2lVRcheck = (OZ2lVRcheck-OZ2lVR)/OZ2lVRcheck
If(MaxVal(Abs(OZ2lVRcheck)).gt.maxdiff) maxdiff=MaxVal(Abs(OZ2lVRcheck))
OZ2lVRcheck=OZ2lVR
If (iQTEST.gt.1) Write(*,*) "Q=",10.0_dp**iQTest," max change=",maxdiff  
If (iQTEST.eq.10) Qin=SetRenormalizationScale(Qinsave) 
End If  
End Do  

 ! ***** Combine operators for 2L2d
OllddSLL = BOllddSLL + PSOllddSLL + PVOllddSLL + TSOllddSLL + TVOllddSLL
OllddSRR = BOllddSRR + PSOllddSRR + PVOllddSRR + TSOllddSRR + TVOllddSRR
OllddSRL = BOllddSRL + PSOllddSRL + PVOllddSRL + TSOllddSRL + TVOllddSRL
OllddSLR = BOllddSLR + PSOllddSLR + PVOllddSLR + TSOllddSLR + TVOllddSLR
OllddVRR = BOllddVRR + PSOllddVRR + PVOllddVRR + TSOllddVRR + TVOllddVRR
OllddVLL = BOllddVLL + PSOllddVLL + PVOllddVLL + TSOllddVLL + TVOllddVLL
OllddVRL = BOllddVRL + PSOllddVRL + PVOllddVRL + TSOllddVRL + TVOllddVRL
OllddVLR = BOllddVLR + PSOllddVLR + PVOllddVLR + TSOllddVLR + TVOllddVLR
OllddTLL = BOllddTLL + PSOllddTLL + PVOllddTLL + TSOllddTLL + TVOllddTLL
OllddTLR = BOllddTLR + PSOllddTLR + PVOllddTLR + TSOllddTLR + TVOllddTLR
OllddTRL = BOllddTRL + PSOllddTRL + PVOllddTRL + TSOllddTRL + TVOllddTRL
OllddTRR = BOllddTRR + PSOllddTRR + PVOllddTRR + TSOllddTRR + TVOllddTRR

 ! ***** Combine operators for 2L2u
OlluuSLL = BOlluuSLL + PSOlluuSLL + PVOlluuSLL + TSOlluuSLL + TVOlluuSLL
OlluuSRR = BOlluuSRR + PSOlluuSRR + PVOlluuSRR + TSOlluuSRR + TVOlluuSRR
OlluuSRL = BOlluuSRL + PSOlluuSRL + PVOlluuSRL + TSOlluuSRL + TVOlluuSRL
OlluuSLR = BOlluuSLR + PSOlluuSLR + PVOlluuSLR + TSOlluuSLR + TVOlluuSLR
OlluuVRR = BOlluuVRR + PSOlluuVRR + PVOlluuVRR + TSOlluuVRR + TVOlluuVRR
OlluuVLL = BOlluuVLL + PSOlluuVLL + PVOlluuVLL + TSOlluuVLL + TVOlluuVLL
OlluuVRL = BOlluuVRL + PSOlluuVRL + PVOlluuVRL + TSOlluuVRL + TVOlluuVRL
OlluuVLR = BOlluuVLR + PSOlluuVLR + PVOlluuVLR + TSOlluuVLR + TVOlluuVLR
OlluuTLL = BOlluuTLL + PSOlluuTLL + PVOlluuTLL + TSOlluuTLL + TVOlluuTLL
OlluuTLR = BOlluuTLR + PSOlluuTLR + PVOlluuTLR + TSOlluuTLR + TVOlluuTLR
OlluuTRL = BOlluuTRL + PSOlluuTRL + PVOlluuTRL + TSOlluuTRL + TVOlluuTRL
OlluuTRR = BOlluuTRR + PSOlluuTRR + PVOlluuTRR + TSOlluuTRR + TVOlluuTRR

 ! ***** Combine operators for 4L
O4lSLL = BO4lSLL + PSO4lSLL + PVO4lSLL + TSO4lSLL + TVO4lSLL
O4lSRR = BO4lSRR + PSO4lSRR + PVO4lSRR + TSO4lSRR + TVO4lSRR
O4lSRL = BO4lSRL + PSO4lSRL + PVO4lSRL + TSO4lSRL + TVO4lSRL
O4lSLR = BO4lSLR + PSO4lSLR + PVO4lSLR + TSO4lSLR + TVO4lSLR
O4lVRR = BO4lVRR + PSO4lVRR + PVO4lVRR + TSO4lVRR + TVO4lVRR
O4lVLL = BO4lVLL + PSO4lVLL + PVO4lVLL + TSO4lVLL + TVO4lVLL
O4lVRL = BO4lVRL + PSO4lVRL + PVO4lVRL + TSO4lVRL + TVO4lVRL
O4lVLR = BO4lVLR + PSO4lVLR + PVO4lVLR + TSO4lVLR + TVO4lVLR
O4lTLL = BO4lTLL + PSO4lTLL + PVO4lTLL + TSO4lTLL + TVO4lTLL
O4lTLR = BO4lTLR + PSO4lTLR + PVO4lTLR + TSO4lTLR + TVO4lTLR
O4lTRL = BO4lTRL + PSO4lTRL + PVO4lTRL + TSO4lTRL + TVO4lTRL
O4lTRR = BO4lTRR + PSO4lTRR + PVO4lTRR + TSO4lTRR + TVO4lTRR

 ! ***** Combine operators for 4Lcross
O4lSLLcross = BO4lSLLcross + PSO4lSLLcross + PVO4lSLLcross + TSO4lSLLcross + TVO4lSLLcross
O4lSRRcross = BO4lSRRcross + PSO4lSRRcross + PVO4lSRRcross + TSO4lSRRcross + TVO4lSRRcross
O4lSRLcross = BO4lSRLcross + PSO4lSRLcross + PVO4lSRLcross + TSO4lSRLcross + TVO4lSRLcross
O4lSLRcross = BO4lSLRcross + PSO4lSLRcross + PVO4lSLRcross + TSO4lSLRcross + TVO4lSLRcross
O4lVRRcross = BO4lVRRcross + PSO4lVRRcross + PVO4lVRRcross + TSO4lVRRcross + TVO4lVRRcross
O4lVLLcross = BO4lVLLcross + PSO4lVLLcross + PVO4lVLLcross + TSO4lVLLcross + TVO4lVLLcross
O4lVRLcross = BO4lVRLcross + PSO4lVRLcross + PVO4lVRLcross + TSO4lVRLcross + TVO4lVRLcross
O4lVLRcross = BO4lVLRcross + PSO4lVLRcross + PVO4lVLRcross + TSO4lVLRcross + TVO4lVLRcross
O4lTLLcross = BO4lTLLcross + PSO4lTLLcross + PVO4lTLLcross + TSO4lTLLcross + TVO4lTLLcross
O4lTLRcross = BO4lTLRcross + PSO4lTLRcross + PVO4lTLRcross + TSO4lTLRcross + TVO4lTLRcross
O4lTRLcross = BO4lTRLcross + PSO4lTRLcross + PVO4lTRLcross + TSO4lTRLcross + TVO4lTRLcross
O4lTRRcross = BO4lTRRcross + PSO4lTRRcross + PVO4lTRRcross + TSO4lTRRcross + TVO4lTRRcross

 ! ***** Combine operators for Gamma2l
K1L = OA1L
K1R = OA1R
K2L = OA2lSL
K2R = OA2lSR
K1L = K1L/sqrt(Alpha_MZ*4*Pi)
K1R = K1R/sqrt(Alpha_MZ*4*Pi)
K2L(2,:) = -0.5_dp*K2L(2,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(2)
K2L(3,:) = -0.5_dp*K2L(3,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(3)
K2R(2,:) = -0.5_dp*K2R(2,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(2)
K2R(3,:) = -0.5_dp*K2R(3,:)/sqrt(Alpha_MZ*4*Pi)/mf_l_mz(3)

 ! **** hLLp **** 
 
Call Calculate_hLLp(OH2lSL,OH2lSR,BrhtoMuE,BrhtoTauE,BrhtoTauMu)


 ! **** LLpGamma **** 
 
Call Calculate_LLpGamma(K2L,K2R,muEgamma,tauEgamma,tauMuGamma)


 ! **** Lto3Lp **** 
 
Call Calculate_Lto3Lp(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,O4lVRR,             & 
& O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,BRmuTo3e,BRtauTo3e,BRtauTo3mu)


 ! **** LtoL1L2L2 **** 
 
Call Calculate_LtoL1L2L2(K1L,K1R,K2L,K2R,O4lSLL,O4lSRR,O4lSRL,O4lSLR,O4lVRR,          & 
& O4lVLL,O4lVRL,O4lVLR,O4lTLL,O4lTRR,O4lSLLcross,O4lSRRcross,O4lSRLcross,O4lSLRcross,    & 
& O4lVRRcross,O4lVLLcross,O4lVRLcross,O4lVLRcross,O4lTLLcross,O4lTRRcross,               & 
& BRtauToemumu,BRtauTomuee,BRtauToemumu2,BRtauTomuee2)


 ! **** MuEconversion **** 
 
Call Calculate_MuEconversion(K1L,K1R,K2L,K2R,OllddSLL,OllddSRR,OllddSRL,              & 
& OllddSLR,OllddVRR,OllddVLL,OllddVRL,OllddVLR,OllddTLL,OllddTLR,OllddTRL,               & 
& OllddTRR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,OlluuVLL,OlluuVRL,               & 
& OlluuVLR,OlluuTLL,OlluuTLR,OlluuTRL,OlluuTRR,CRmuEAl,CRmuETi,CRmuESr,CRmuESb,          & 
& CRmuEAu,CRmuEPb)


 ! **** TauLMeson **** 
 
Call Calculate_TauLMeson(OllddSLL,OllddSRR,OllddSRL,OllddSLR,OllddVRR,OllddVLL,       & 
& OllddVRL,OllddVLR,OlluuSLL,OlluuSRR,OlluuSRL,OlluuSLR,OlluuVRR,OlluuVLL,               & 
& OlluuVRL,OlluuVLR,BrTautoEPi,BrTautoEEta,BrTautoEEtap,BrTautoMuPi,BrTautoMuEta,        & 
& BrTautoMuEtap)


 ! **** ZLLp **** 
 
Call Calculate_ZLLp(OZ2lSL,OZ2lSR,OZ2lVL,OZ2lVR,BrZtoMuE,BrZtoTauE,BrZtoTauMu)

Mhh= Mhh_s 
Mhh2 = Mhh2_s 
MAh= MAh_s 
MAh2 = MAh2_s 

! *****  G minus 2 ***** 

Call Gminus2(1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,           & 
& MSe,MSe2,MSv,MSv2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,     & 
& cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,         & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplHpmcHpmVP,cplSecSeVP,ae)

Call Gminus2(2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,           & 
& MSe,MSe2,MSv,MSv2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,     & 
& cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,         & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplHpmcHpmVP,cplSecSeVP,amu)

Call Gminus2(3,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,MHpm2,           & 
& MSe,MSe2,MSv,MSv2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,cplcFeChaSvR,cplcChaChaVPL,     & 
& cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,cplcFeChiSeR,cplcFeFehhL,         & 
& cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,         & 
& cplcFvFecHpmR,cplcFeFvHpmL,cplcFeFvHpmR,cplHpmcHpmVP,cplSecSeVP,atau)


! *****  Lepton EDM ***** 

Call LeptonEDM(1,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,               & 
& MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,      & 
& cplcFeChaSvR,cplcChaChaVPL,cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,       & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHpmcHpmVP,        & 
& cplSecSeVP,cplcVWmVPVWm,EDMe)

Call LeptonEDM(2,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,               & 
& MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,      & 
& cplcFeChaSvR,cplcChaChaVPL,cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,       & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHpmcHpmVP,        & 
& cplSecSeVP,cplcVWmVPVWm,EDMmu)

Call LeptonEDM(3,MAh,MAh2,MCha,MCha2,MChi,MChi2,MFe,MFe2,Mhh,Mhh2,MHpm,               & 
& MHpm2,MSe,MSe2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,cplcFeFeAhL,cplcFeFeAhR,cplcFeChaSvL,      & 
& cplcFeChaSvR,cplcChaChaVPL,cplcChaChaVPR,cplChiFecSeL,cplChiFecSeR,cplcFeChiSeL,       & 
& cplcFeChiSeR,cplcFeFehhL,cplcFeFehhR,cplcFeFeVPL,cplcFeFeVPR,cplcFeFeVZL,              & 
& cplcFeFeVZR,cplcChaFecSvL,cplcChaFecSvR,cplcFvFecHpmL,cplcFvFecHpmR,cplcFvFecVWmL,     & 
& cplcFvFecVWmR,cplcFeFvHpmL,cplcFeFvHpmR,cplcFeFvVWmL,cplcFeFvVWmR,cplHpmcHpmVP,        & 
& cplSecSeVP,cplcVWmVPVWm,EDMtau)


! *****  delta Rho ***** 

sinW2=0.22290_dp 
TW = asin(sqrt(sinW2)) 
g2=Sqrt(4._dp*Sqrt2*G_F*mW2) 
g1=g2*Sqrt(sinW2/(1._dp-sinW2)) 
mW2=(1._dp-sinW2)*mz2 + 0
vev2=Sqrt(mZ2*(1._dp-sinW2)*SinW2/(pi*alpha)) +0 
vd=vev2/Sqrt(1._dp+TanBeta**2) 
vu=TanBeta*vd 
Call SolveTadpoleEquations(g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,vd,vu,(/ ZeroC, ZeroC /))

Call TreeMasses(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,            & 
& MGlu,MGlu2,Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,               & 
& MVWm2,MVZ,MVZ2,pG,TW,UM,UP,v,ZA,ZD,ZDL,ZDR,ZE,ZEL,ZER,ZH,ZN,ZP,ZU,ZUL,ZUR,             & 
& ZV,ZW,ZZ,alphaH,betaH,vd,vu,g1,g2,g3,Yd,Ye,Yu,Mu,Td,Te,Tu,Bmu,mq2,ml2,mHd2,            & 
& mHu2,md2,mu2,me2,M1,M2,M3,GenerationMixing,kont)

MVWm = mW 
MVWm2 = mW2 
MVZ = mZ 
MVZ2 = mZ2 
MFe(1:3) = mf_l 
MFe2(1:3) = mf_l**2 
MFu(1:3) = mf_u 
MFu2(1:3) = mf_u**2 
MFd(1:3) = mf_d 
MFd2(1:3) = mf_d**2 
Call CouplingsForVectorBosons(g1,g2,ZH,ZA,TW,UM,UP,ZN,vd,vu,ZP,ZD,ZE,ZU,              & 
& ZDL,ZUL,ZEL,ZV,cplAhhhVZ,cplcChaChaVZL,cplcChaChaVZR,cplChiChiVZL,cplChiChiVZR,        & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFuVZL,cplcFuFuVZR,               & 
& cplcFvFvVZL,cplcFvFvVZR,cplcgWmgWmVZ,cplcgWpCgWpCVZ,cplhhVZVZ,cplHpmcHpmVZ,            & 
& cplHpmcVWmVZ,cplSdcSdVZ,cplSecSeVZ,cplSucSuVZ,cplSvcSvVZ,cplcVWmVWmVZ,cplAhAhVZVZ,     & 
& cplhhhhVZVZ,cplHpmcHpmVZVZ,cplSdcSdVZVZ,cplSecSeVZVZ,cplSucSuVZVZ,cplSvcSvVZVZ,        & 
& cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,cplAhHpmcVWm,cplChiChacVWmL,           & 
& cplChiChacVWmR,cplcFuFdcVWmL,cplcFuFdcVWmR,cplcFvFecVWmL,cplcFvFecVWmR,cplcgWpCgAcVWm, & 
& cplcgAgWmcVWm,cplcgZgWmcVWm,cplcgWpCgZcVWm,cplhhHpmcVWm,cplhhcVWmVWm,cplHpmcVWmVP,     & 
& cplSdcSucVWm,cplSecSvcVWm,cplcVWmVPVWm,cplAhAhcVWmVWm,cplhhhhcVWmVWm,cplHpmcHpmcVWmVWm,& 
& cplSdcSdcVWmVWm,cplSecSecVWmVWm,cplSucSucVWmVWm,cplSvcSvcVWmVWm,cplcVWmVPVPVWm1,       & 
& cplcVWmVPVPVWm2,cplcVWmVPVPVWm3,cplcVWmcVWmVWmVWm1,cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3)

Call DeltaRho(MAh,MAh2,MCha,MCha2,MChi,MChi2,MFd,MFd2,MFe,MFe2,MFu,MFu2,              & 
& Mhh,Mhh2,MHpm,MHpm2,MSd,MSd2,MSe,MSe2,MSu,MSu2,MSv,MSv2,MVWm,MVWm2,MVZ,MVZ2,           & 
& cplAhAhcVWmVWm,cplAhAhVZVZ,cplAhhhVZ,cplAhHpmcVWm,cplcChaChaVZL,cplcChaChaVZR,         & 
& cplcFdFdVZL,cplcFdFdVZR,cplcFeFeVZL,cplcFeFeVZR,cplcFuFdcVWmL,cplcFuFdcVWmR,           & 
& cplcFuFuVZL,cplcFuFuVZR,cplcFvFecVWmL,cplcFvFecVWmR,cplcFvFvVZL,cplcFvFvVZR,           & 
& cplcgAgWmcVWm,cplcgWmgWmVZ,cplcgWpCgAcVWm,cplcgWpCgWpCVZ,cplcgWpCgZcVWm,               & 
& cplcgZgWmcVWm,cplChiChacVWmL,cplChiChacVWmR,cplChiChiVZL,cplChiChiVZR,cplcVWmcVWmVWmVWm1,& 
& cplcVWmcVWmVWmVWm2,cplcVWmcVWmVWmVWm3,cplcVWmVPVPVWm1,cplcVWmVPVPVWm2,cplcVWmVPVPVWm3, & 
& cplcVWmVPVWm,cplcVWmVWmVZ,cplcVWmVWmVZVZ1,cplcVWmVWmVZVZ2,cplcVWmVWmVZVZ3,             & 
& cplhhcVWmVWm,cplhhhhcVWmVWm,cplhhhhVZVZ,cplhhHpmcVWm,cplhhVZVZ,cplHpmcHpmcVWmVWm,      & 
& cplHpmcHpmVZ,cplHpmcHpmVZVZ,cplHpmcVWmVP,cplHpmcVWmVZ,cplSdcSdcVWmVWm,cplSdcSdVZ,      & 
& cplSdcSdVZVZ,cplSdcSucVWm,cplSecSecVWmVWm,cplSecSeVZ,cplSecSeVZVZ,cplSecSvcVWm,        & 
& cplSucSucVWmVWm,cplSucSuVZ,cplSucSuVZVZ,cplSvcSvcVWmVWm,cplSvcSvVZ,cplSvcSvVZVZ,dRho)

If (WriteParametersAtQ) Then 
scalein = SetRenormalizationScale(160._dp**2) 
Else 
scalein = SetRenormalizationScale(scale_save**2) 
End if 
mz2 = mzsave**2 
mz = mzsave 
g1input = Sqrt(3._dp/5._dp)*g1input 
End subroutine CalculateLowEnergyConstraints 
 
 
End Program SPhenoMSSM 
