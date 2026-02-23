Off[General::spell]

Model`Name = "Inert";
Model`NameLaTeX ="Inert doublet Model";
Model`Authors = "B.Herrmann, F.Staub";
Model`Date = "2014-11-06";

(* 2013-09-01: changing to new conventions for FermionFields/MatterFields *)
(* 2014-04-24: removed mixing between neutral Higgs fields *)
(* 2014-11-06: Changed sign in Lagrangian *)


(*-------------------------------------------*)
(*   Particle Content*)
(*-------------------------------------------*)

(* Global Symmetries *)

Global[[1]] = {Z[2], Z2};

(* Gauge Groups *)

Gauge[[1]]={B,   U[1], hypercharge, g1,False,1};
Gauge[[2]]={WB, SU[2], left,        g2,True, 1};
Gauge[[3]]={G,  SU[3], color,       g3,False,1};


(* Matter Fields *)

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

NameOfStates={GaugeES, EWSB};

(* ----- Before EWSB ----- *)


  		  
DEFINITION[GaugeES][Additional]= {
	{LagHC, {AddHC->True}},
	{LagNoHC,{ AddHC->False}}
};



LagNoHC = -(MHD conj[Hd].Hd + MHU conj[Hu].Hu + Lambda1 conj[Hd].Hd.conj[Hd].Hd + \
		Lambda2 conj[Hu].Hu.conj[Hu].Hu + Lambda3 conj[Hu].Hu.conj[Hd].Hd  + Lambda4 conj[Hu].Hd.Hu.conj[Hd]);


LagHC = -(Lambda5/2 Hu.Hd.Hu.Hd + Yd Hd.q.d + Ye Hd.l.e - Yu conj[Hd].q.u);



DEFINITION[EWSB][GaugeSector] =
{ 
  {{VB,VWB[3]},{VP,VZ},ZZ},
  {{VWB[1],VWB[2]},{VWp,conj[VWp]},ZW}
};    
        
        
          	

(* ----- VEVs ---- *)


DEFINITION[EWSB][VEVs]= 
{    {Hd0, {v, 1/Sqrt[2]}, {G0, \[ImaginaryI]/Sqrt[2]},{hh, 1/Sqrt[2]}},
     {Hu0, {0, 0}, {A0, \[ImaginaryI]/Sqrt[2]},{H0, 1/Sqrt[2]}}     };

 

(* ---- Mixings ---- *)


DEFINITION[EWSB][MatterSector]= 
{    {{Hup,conj[Hdm]},{Hp,ZP}},
     {{{dL}, {conj[dR]}}, {{DL,ZDL}, {DR,ZDR}}},
     {{{uL}, {conj[uR]}}, {{UL,ZUL}, {UR,ZUR}}},
     {{{eL}, {conj[eR]}}, {{EL,ZEL}, {ER,ZER}}}
           
 }; 


DEFINITION[EWSB][DiracSpinors]={
 Fd ->{  DL, conj[DR]},
 Fe ->{  EL, conj[ER]},
 Fu ->{  UL, conj[UR]},
 Fv ->{  vL, 0}};

