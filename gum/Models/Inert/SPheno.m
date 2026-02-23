OnlyLowEnergySPheno = True;


MINPAR={
        {1,Lambda1IN},
        {2,Lambda2IN},
        {3,Lambda3IN},
        {4,Lambda4IN},
        {5,Lambda5IN} };


ParametersToSolveTadpoles = {MHD,MHU};
RealParameters = {};

DEFINITION[MatchingConditions]= {
 {v, vSM}, 
 {Ye, YeSM},
 {Yd, YdSM},
 {Yu, YuSM},
 {g1, g1SM},
 {g2, g2SM},
 {g3, g3SM}
 };

BoundaryLowScaleInput={
 {Lambda1,Lambda1IN},
 {Lambda2,Lambda2IN},
 {Lambda3,Lambda3IN},
 {Lambda4,Lambda4IN},
 {Lambda5,Lambda5IN}

};

ListDecayParticles = {Fu,Fe,Fd,hh,H0,A0,Hp};
ListDecayParticles3B = {{Fu,"Fu.f90"},{Fe,"Fe.f90"},{Fd,"Fd.f90"}};

AddTreeLevelUnitarityLimits=True;

DefaultInputValues ={Lambda1IN -> 0.1, Lambda2IN -> 0.27, Lambda3IN -> 1.0, Lambda4IN ->-0.5, Lambda5IN ->0.5};


RenConditionsDecays={
{dCosTW, 1/2*Cos[ThetaW] * (PiVWp/(MVWp^2) - PiVZ/(mVZ^2)) },
{dSinTW, -dCosTW/Tan[ThetaW]},
{dg2, 1/2*g2*(derPiVPheavy0 + PiVPlightMZ/MVZ^2 - (-(PiVWp/MVWp^2) + PiVZ/MVZ^2)/Tan[ThetaW]^2 + (2*PiVZVP*Tan[ThetaW])/MVZ^2)  },
{dg1, dg2*Tan[ThetaW]+g2*dSinTW/Cos[ThetaW]- dCosTW*g2*Tan[ThetaW]/Cos[ThetaW]}
};
