(* To get a SPheno version without RGE evolution *)

OnlyLowEnergySPheno = True;

(* A list of parameters which should be read from a LesHouches file by SPheno. First, the
number in the block is defined, afterwards the variable *)

MINPAR={
        {1,Lambdaa1IN},
        {2,Lambdaa2IN},
        {3,Lambdaa3IN},
        {4,Lambdaa4IN},
        {5,Lambdaa5IN},
        {9,MHUIN}
        };

(* SARAH derives for each VEV the corresponding minimum condition
for the vacuum. These equations give constraints to the same number of parameters as VEV are in
the models. ParametersToSolveTadpoles is used to set the parameter which fixed by the tadpole
equations. *)

(* MHU needs to be removed *)

ParametersToSolveTadpoles = {MHD};
(* ParametersToSolveTadpoles = {MHD,MHU}; *)

(* e input parameters are always real. This information is set via *)

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

(* It is also possible to use a low scale input without any RGE running. In that case
special boundary conditions can be defined by the array BoundaryLowScaleInput.
All boundaries are defined by a two dimensional array. The first entry is the name of the parameter,
the second entry is the used condition at the considered scale. *)

BoundaryLowScaleInput={
 {Lambdaa1,Lambdaa1IN},
 {Lambdaa2,Lambdaa2IN},
 {Lambdaa3,Lambdaa3IN},
 {Lambdaa4,Lambdaa4IN},
 {Lambdaa5,Lambdaa5IN},
 {MHU,MHUIN}
};

(* List of particles for which the two-body decays are to be calculated.
This can be a list of particles using the names inside SARAH, e.g.
ListDecayParticles = {Sd,Su,Se,hh,Ah,Hpm,Chi};
or just Automatic. If Automatic is used, the widths of all particles not defined as standard
model particles as well as for the top quark are calculated. *)

ListDecayParticles = {Fu,Fe,Fd,hh,H0,A0,Hp};

(* Three body decays of fermions. This can be a list with the names of
the particles and the corresponding files names *)

ListDecayParticles3B = {{Fu,"Fu.f90"},{Fe,"Fe.f90"},{Fd,"Fd.f90"}};

(* This enables the output of all routines to calculate the tree-level unitarity constraints. By default, this generates
the full scattering matrix involving all scalar fields in the model which are colourless. In the case that some
particles should not be included, they can be explicitly removed via *)

AddTreeLevelUnitarityLimits=False;

(* the default values for the input file *)

DefaultInputValues ={Lambdaa1IN -> 0.1, Lambdaa2IN -> 0.27, Lambdaa3IN -> 1.0, Lambdaa4IN ->-0.5, Lambdaa5IN ->0.5, MHUIN ->20000};

RenConditionsDecays={
{dCosTW, 1/2*Cos[ThetaW] * (PiVWp/(MVWp^2) - PiVZ/(mVZ^2)) },
{dSinTW, -dCosTW/Tan[ThetaW]},
{dg2, 1/2*g2*(derPiVPheavy0 + PiVPlightMZ/MVZ^2 - (-(PiVWp/MVWp^2) + PiVZ/MVZ^2)/Tan[ThetaW]^2 + (2*PiVZVP*Tan[ThetaW])/MVZ^2)  },
{dg1, dg2*Tan[ThetaW]+g2*dSinTW/Cos[ThetaW]- dCosTW*g2*Tan[ThetaW]/Cos[ThetaW]}
};