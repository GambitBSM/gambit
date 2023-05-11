OnlyLowEnergySPheno = True;


MINPAR={{1,Lambda1Input},
        {2,Lambda2Input},
        {3,Lambda3Input},
        {4,Lambda4Input},
        {5,Lambda5Input},
        {9,M122input},
        {10,TanBeta},
        {11,K1input}, 
        {12,K2input}, 
        {13,K3input}, 
        {14,K4input}, 
        {15,K3pinput},
        {16,K4pinput},
        {17,MTinput}
};

RealParameters = {TanBeta};

ParametersToSolveTadpoles = {M112,M222,vT};

DEFINITION[MatchingConditions]= {
 {v1,vSM*Cos[ArcTan[TanBeta]]},
 {v2,vSM*Sin[ArcTan[TanBeta]]},
 {Ye, YeSM*vSM/v2},
 {Yd, YdSM*vSM/v2},
 {Yu, YuSM*vSM/v2},
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
 {K1,K1input},
 {K2,K2input},
 {K3,K3input},
 {K4,K4input},
 {K3p,K3pinput},
 {K4p,K4pinput},
 {M122, M122input},
 {MT2, MTinput*MTinput}
};




ListDecayParticles = {Fu,Fe,Fd,hh,Ah,Hm,Tpp};
ListDecayParticles3B = {{Fu,"Fu.f90"},{Fe,"Fe.f90"},{Fd,"Fd.f90"}};


DefaultInputValues ={
Lambda1Input -> 0.1, 
Lambda2Input -> 0.27, 
Lambda3Input -> 1.1, 
Lambda4Input ->-0.5, 
Lambda5Input ->0.5,  
M122input -> 40000., 
MTinput -> 375,
TanBeta->2,
K1input -> 0.01,
K2input -> 0.01,
K3input -> 0.01,
K4input -> 0.01,
K3pinput -> -0.01,
K4pinput -> -0.01
};

RenConditionsDecays={
{dCosTW, 1/2*Cos[ThetaW] * (PiVWm/(MVWm^2) - PiVZ/(mVZ^2)) },
{dSinTW, -dCosTW/Tan[ThetaW]},
{dg2, 1/2*g2*(derPiVPheavy0 + PiVPlightMZ/MVZ^2 - (-(PiVWm/MVWm^2) + PiVZ/MVZ^2)/Tan[ThetaW]^2 + (2*PiVZVP*Tan[ThetaW])/MVZ^2)  },
{dg1, dg2*Tan[ThetaW]+g2*dSinTW/Cos[ThetaW]- dCosTW*g2*Tan[ThetaW]/Cos[ThetaW]}
};

(* turn off RGEs for loop-decays *)                     
SA`NoRGEsforDecays=True;