(* SARAH: a "spectrum generator" generator *)
(* tree-level mass matrices and vertices *)
(* one-loop self-energies *)
(* two-loop renormalization group equations *)
(* two-loop Higgs masses *)
(* flavor observables calculated using the FlavorKit extension *)
(* all calculations converted to F-code and added to a SPheno-like spectrum generator *)
(* interfacing this information to other tools *)

(* CalcHEP/CompHep *)
(* FeynArts/FormCalc *)
(* UFO *)
(* WHIARD/OMega *)
(* Vevacious *)
(* SPheno *)

(* HiggsBounds/HiggsSignals *)
(* MicrOmegas *)
(* MadGraph *)

(* Features of the generated SPheno *)
(* Full two-loop running of all parameters and all masses at one-loop *)
(* two-loop corrections to Higgs masses *)
(* Complete one-loop thresholds at MZ *)
(* calculation of flavour and precision observables at full 1-loop *)
(* calculation of decay widths and branching ratios *)
(* interface to HiggsBounds and HiggsSignals *)
(* estimate of electroweak Fine-Tuning *)


Off[General::spell]

Model`Name = "Inert_gum";
Model`NameLaTeX = "Inert doublet Model";
Model`Authors = "A.Woodcock, B.Herrmann, F.Staub";
Model`Date = "2014-11-06";

(* 2013-09-01: changing to new conventions for FermionFields/MatterFields *)
(* 2014-04-24: removed mixing between neutral Higgs fields *)
(* 2014-11-06: Changed sign in Lagrangian *)


(*-------------------------------------------*)
(*   Particle Content*)
(*-------------------------------------------*)

(* Global Symmetries *)

(* 1: symmetry, 2: name *)

Global[[1]] = {Z[2], Z2};

(* Maybe better named Local Symmetries *)
(* of course, each is enforce by an introduction of a gauge *)
(* field, so we must also include the notation for this here *)
(* we also provide the name of the conserved charge *)

(* left === weak isospin charge *)


(* Gauge Groups *)

(* looks like we just defined the Gauge fields, B, W, G *)
(* we are using the pre-EWSB notation here *)

(* Gauge symmetries & Gauge Fields *)

(* 1: Gauge field name *)
(* 2: Gauge group *)
(* 3: name of group *)
(* 4: corresponding coupling name *)
(* 5: is the group brken later *)
(* 6: Z2 rep *)

Gauge[[1]]={B,   U[1], hypercharge, g1, False, 1};
Gauge[[2]]={WB, SU[2], left,        g2, True,  1};
Gauge[[3]]={G,  SU[3], color,       g3, False, 1};


(* Matter Fields *)

(* 1: name of matter field *)
(* 2: number of generations *)
(* 3: names of SU[2] doublet components *)
(* 4: the weak hypercharge *)
(* 5: the SU[2] rep *)
(* 6: the SU[3] rep *)
(* 7: the Z2 rep *)

(* NOTE: for SUSY models we have SuperFields instead of FermionFiolds and ScalarFields *)

FermionFields[[1]] = {q, 3, {uL, dL},     1/6, 2,  3, 1};  
FermionFields[[2]] = {l, 3, {vL, eL},    -1/2, 2,  1, 1};
FermionFields[[3]] = {d, 3, conj[dR],     1/3, 1, -3, 1};
FermionFields[[4]] = {u, 3, conj[uR],    -2/3, 1, -3, 1};
FermionFields[[5]] = {e, 3, conj[eR],       1, 1,  1, 1};

ScalarFields[[1]] =  {Hd, 1, {Hd0, Hdm},    -1/2, 2,  1,  1};
ScalarFields[[2]] =  {Hu, 1, {Hup, Hu0},     1/2, 2,  1, -1};


(*----------------------------------------------*)
(*   DEFINITION                                 *)
(*----------------------------------------------*)


(* GaugeES -> Lagrangian with Gauge-symmetric eigenstates *)
(* EWSB -> Lagrangian with eigenstates after Gauge-symmetry breaking*)
(*          these can be considered the mass eigenstates *)
NameOfStates={GaugeES, EWSB};

(* ----- Before EWSB ----- *)

(* Define the gauge-symmetric lagrangian *)

(* we only need to define the scalar potential and Yukawa sector *)
(* the fermion-gauge and gauge-gauge interactions derived via Gauge principle *)

DEFINITION[GaugeES][Additional]= {
	{LagHC,  { AddHC->True}},
	{LagNoHC,{ AddHC->False}}
};



LagNoHC = -(MHD conj[Hd].Hd + MHU conj[Hu].Hu + Lambda1 conj[Hd].Hd.conj[Hd].Hd + \
		       Lambda2 conj[Hu].Hu.conj[Hu].Hu + Lambda3 conj[Hu].Hu.conj[Hd].Hd  + Lambda4 conj[Hu].Hd.Hu.conj[Hd]);


LagHC = -(Lambda5/2 Hu.Hd.Hu.Hd + Yd Hd.q.d + Ye Hd.l.e - Yu conj[Hd].q.u);

(* LagHC = -(Lambda5/2 conj[Hu].Hd.conj[Hu].Hd + Yd conj[Hd].d.q + Ye conj[Hd].e.l - Yu Hd.u.q); *)


(* For the EWSB lagrangian, we redefine the gauge and fermion sectors *)
(* and define the VEVs *)

(* define the new Gauge boson eigenstates after EWSB *)
(* B and WB[3] mix to become P,Z *)
(* WB[1] and WB[2] mix to become W+,W- *)

(* 1: the gauge eigenstates to be mixed *)
(* 2: the resulting EWSB state *)
(* 3: denotes matrix which diagonalizes the mass matrix *)

(*  This parametrization can be defined later
in parameters.m *)

DEFINITION[EWSB][GaugeSector] =
{ 
  {{VB,VWB[3]}, {VP,VZ}, ZZ},
  {{VWB[1],VWB[2]}, {VWp,conj[VWp]}, ZW}
};    
        

(* ----- VEVs ---- *)

(* above here we have already defined all aspects of the model *)
(* but in practise we are interested in mass states after gauge symmetry breaking *)
(* se we define the rotations to these mass states *)

(* define which fields acquire a VEV to break the gauge symmetry *)


(* we only list the neutral Higgs doublet components *)
(* since we don't want a VEV for the charged components *)


DEFINITION[EWSB][VEVs]= 
{    {Hd0, {v, 1/Sqrt[2]}, {G0, \[ImaginaryI]/Sqrt[2]}, {hh, 1/Sqrt[2]}},
     {Hu0, {0, 0},         {A0, \[ImaginaryI]/Sqrt[2]}, {H0, 1/Sqrt[2]}} };


(* ---- Mixings ---- *)

(* what vector bosons, scalars and fermions mix among each other *)
(* the LHS set mixes together to become the RHS set after EWSB *)
(* Hup,conj[Hdm] -> Hp *)
(* Here Zxx denotes the matrix which diagonalizes the mass matrix*)
(* dL,conj[dR] -> DL,ZDL,DR,ZDR *)

(* todo: why aren't the Goldstone bosons G+/- specified? *)

(* 1: the gauge eigenstates to be mixed *)
(* 2: the resulting EWSB state *)
(* 3: denotes matrix which diagonalizes the mass matrix *)

DEFINITION[EWSB][MatterSector]= 
{    {{Hup, conj[Hdm]}, {Hp, ZP}},
     {{{dL}, {conj[dR]}}, {{DL,ZDL}, {DR,ZDR}}},
     {{{uL}, {conj[uR]}}, {{UL,ZUL}, {UR,ZUR}}},
     {{{eL}, {conj[eR]}}, {{EL,ZEL}, {ER,ZER}}}}; 

(* While SARAH works internally often with Weyl spinors, Dirac spinors are commonly
used by Monte-Carlo tools and also by SPheno. Therefore, we have to define the relation between the
two- and four-component fermions *)

DEFINITION[EWSB][DiracSpinors]={
 Fd ->{  DL, conj[DR]},
 Fe ->{  EL, conj[ER]},
 Fu ->{  UL, conj[UR]},
 Fv ->{  vL, 0}};
