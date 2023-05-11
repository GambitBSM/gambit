! -----------------------------------------------------------------------------  
! This file was automatically created by SARAH version 4.14.0 
! SARAH References: arXiv:0806.0538, 0909.2863, 1002.0840, 1207.0906, 1309.7223  
! (c) Florian Staub, 2013  
! ------------------------------------------------------------------------------  
! File created at 23:51 on 14.9.2022   
! ----------------------------------------------------------------------  
 
 
Module Settings 
 
Use Control 
Use Mathematics 
Use LoopFunctions 
Logical, Save :: PrintPartialContributions = .False. 
Logical, Save :: Enable3BDecays = .True. 
Logical, Save :: Enable3BDecaysS = .True. 
Logical, Save :: Enable3BDecaysF = .True. 
Logical, Save :: FirstRun = .True. 
Logical, Save :: DecoupleAtRenScale = .False. 
Logical, Save :: RunningCouplingsDecays = .True. 
Logical, Save :: WriteSLHA1 = .False. 
Logical, Save :: MakeQTEST = .False. 
Logical, Save :: CalculateOneLoopMasses = .True. 
Logical, Save :: CalculateOneLoopMassesSave = .True. 
Logical, Save :: Kin_Threshold_Scan = .True. 
Logical, Save :: CalculateTwoLoopHiggsMasses = .True. 
Logical, Save :: SquareFullAmplitudeDecays = .False. 
Logical :: CalculateTwoLoopHiggsMassesSave = .True. 
Logical, Save :: CalculateLowEnergy = .True. 
Logical, Save :: WriteParametersAtQ = .False. 
Logical, Save :: OutputForMO = .False. 
Logical, Save :: OutputForMG = .False. 
Logical, Save :: TwoLoopRGE=.True.
Logical, Save :: OneLoopDecays=.True.
Logical, Save :: ewOSinDecays=.True.
Logical, Save :: yukOSinDecays=.False.
Logical, Save :: LoopInducedDecaysOS=.True.
Logical, Save :: CTinLoopDecays=.False.
Logical, Save :: Extra_scale_loopDecays=.False.
Logical, Save :: MatchZWpoleMasses=.False.
Logical, Save :: OnlyLightStates=.False.
Logical, Save :: PoleMassesForLoopDecays=.False.
Logical, Save :: OnlyHeavyStates=.False.
Integer :: divonly, divonly_save 
Real(dp) :: divergence, divergence_save, scale_loopdecays  
Real(dp) :: TwoLoopRegulatorMass = 0._dp 
Logical :: IRdivOnly = .false. 
Character(len=3) :: IRstring="000" 
Character(len=15)::HighScaleModel
Real(dp), save :: rMS = 1._dp 
Real(dp), save :: epsCoup = 1.0E-10_dp 
Real(dp), save :: DerrMS = 0._dp 
Real(dp), save :: rMS_SM = 1._dp 
Real(dp), save :: Mass_Regulator_PhotonGluon = 1.0E-10_dp 
Logical, Save :: SimplisticLoopDecays=.False.
Logical, Save :: ShiftIRdiv=.True.
Logical, Save :: DebugLoopDecays=.False.
Logical, Save :: OnlyTreeLevelContributions= .false. 
Logical, Save :: ExternalZfactors=.True.
Logical, Save :: OSkinematics=.True.
Logical, Save :: One_Loop_Matching =.True.
Logical, Save :: Offdiaognal_WaveFunction_Matching=.False.
Logical, Save :: UseZeroRotationMatrices=.False.
Logical, Save :: UseP2Matrices=.True.
Logical, Save :: RunningSUSYparametersLowEnergy=.True.
Logical, Save :: RunningSMparametersLowEnergy=.True.
Integer, Save :: MinimalNumberIterations = 5
Logical :: SwitchToSCKM= .False. 
Logical :: CalculateMSSM2Loop= .False. 
Logical :: GaugelessLimit= .True. 
Logical :: Calculate_mh_within_SM = .True. 
Logical :: Force_mh_within_SM= .False. 
Logical :: FoundIterativeSolution = .True.
Logical :: WriteOutputForNonConvergence=.True.
Logical :: SPA_Convention 
Logical :: ForceRealMatrices = .False. 
Logical :: WriteGUTvalues 
Logical :: TwoLoopSafeMode 
Integer :: TwoLoopMethod = 3 
Logical :: PoleMassesInLoops = .True. 
Logical ::  include1l2lshift = .false. 
Logical ::  NewGBC = .true. 
Logical :: WriteTreeLevelTadpoleParameters = .false. 
Logical :: IncludeDeltaVB = .True. 
Logical :: IncludeBSMdeltaVB = .True. 
Real(dp) :: WidthToBeInvisible = 0._dp 
Logical :: HigherOrderDiboson = .True. 
Real(dp) :: nLep = 3._dp, mf_u_mz_running 
Real(dp) :: nUp = 2._dp 
Real(dp) :: err2L = 0._dp 
Real(dp) :: UVscaleQ, IRmass=1.0E-6_dp,  epsUV=1.0E-6_dp 
Real(dp) :: nDown = 3._dp 
Real(dp) :: MaxMassLoop = 1.0E16_dp 
Real(dp) :: MinWidth = 1.0E-30_dp 
Real(dp) :: hstep_pn=0.1_dp, hstep_sa=0.001_dp 
Real(dp) :: MaxMassNumericalZero = 1.0E-8_dp 
Logical :: runningTopMZ= .False. 
Logical :: PrintDebugInformation = .False. 
Logical ::IncludeThresholdsAtScale 
Logical :: PurelyNumericalEffPot 
Logical :: Write_WCXF = .false. 
Integer :: MatchingOrder = -2 
Complex(dp) :: CKMcomplex(3,3) 
Real(dp) :: Xi = 1._dp 
Real(dp) :: RXi = 1._dp 
Real(dp) :: RXiNew = 1._dp 

 Contains 

Function InverseMatrix(M) Result(Inv) 
Implicit None
Complex(dp), Intent(in) :: M(:,:) 
Complex(dp) :: Inv(Size(M,1),Size(M,2)) 
Integer :: kont 

inv = M 
Call gaussj(kont,inv,Size(M,1),Size(M,2)) 
End Function InverseMatrix 

End Module Settings 
 
