OnlyLowEnergySPheno = True;

MINPAR={{1,Lambda1Input},
        {2,Lambda2Input},
        {3,Lambda3Input},
        {4,Lambda4Input},
        {5,Lambda5Input},
        {9,M122input},
        {10,TanBeta},
        {11,LambdaT1Input}, 
	{12,LambdaT2Input}, 
	{13,LambdaT3Input}, 
	{14,LambdaT4Input},
	{15,MTInput}
};

RealParameters = {TanBeta};

ParametersToSolveTadpoles = {M112,M222};

DEFINITION[MatchingConditions]= {
 {v1,vSM*Cos[ArcTan[TanBeta]]},
 {v2,vSM*Sin[ArcTan[TanBeta]]},
 {Ye, YeSM*vSM/v1- v2/v1*epsE},
 {Yd, YdSM*vSM/v1- v2/v1*epsD},
 {Yu, YuSM*vSM/v2- v1/v2*epsU},
 {g1, g1SM},
 {g2, g2SM},
 {g3, g3SM}
 };

BoundaryLowScaleInput={
 {Lambda1,Lambda1Input},
 {Lambda2,Lambda2Input},
 {Lambda3,Lambda3Input},
 {Lambda4,Lambda4Input},
 {Lambda5,Lambda5Input},
 {LambdaT1,LambdaT1Input},
 {LambdaT2,LambdaT2Input},
 {LambdaT3,LambdaT3Input},
 {LambdaT4,LambdaT4Input},
 {M122, M122input},
 {MT2,MTInput*MTInput}
};

ListDecayParticles = {Fu,Fe,Fd,hh,Ah,Hm,TP2,TP3};
ListDecayParticles3B = {{Fu,"Fu.f90"},{Fe,"Fe.f90"},{Fd,"Fd.f90"}};

DefaultInputValues ={
Lambda1Input -> 0.1, 
Lambda2Input -> 0.2, 
Lambda3Input -> 0.3, 
Lambda4Input -> -0.3, 
Lambda5Input -> 0.2,  
M122input -> 40000., 
MTInput -> 375,
TanBeta-> 2,
LambdaT1Input -> 1, 
LambdaT2Input -> 1, 
LambdaT3Input -> 1, 
LambdaT4Input -> -1
};

RenConditionsDecays={
{dCosTW, 1/2*Cos[ThetaW] * (PiVWm/(MVWm^2) - PiVZ/(mVZ^2)) },
{dSinTW, -dCosTW/Tan[ThetaW]},
{dg2, 1/2*g2*(derPiVPheavy0 + PiVPlightMZ/MVZ^2 - (-(PiVWm/MVWm^2) + PiVZ/MVZ^2)/Tan[ThetaW]^2 + (2*PiVZVP*Tan[ThetaW])/MVZ^2)  },
{dg1, dg2*Tan[ThetaW]+g2*dSinTW/Cos[ThetaW]- dCosTW*g2*Tan[ThetaW]/Cos[ThetaW]}
};

(* turn off RGEs for loop-decays *)                     
SA`NoRGEsforDecays=True;
