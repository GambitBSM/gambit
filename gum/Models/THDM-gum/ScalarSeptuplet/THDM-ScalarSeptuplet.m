Off[General::spell]

Model`Name = "THDMSEP_gum";
Model`NameLaTeX ="Two Higgs Doublet Model with a real scalar septuplet";
Model`Authors = "K. Nickel, A. Vicente";
Model`Date = "2016-02-04";

(* based on the septuplet model introduced in 1512.06587 *)

(*-------------------------------------------*)
(*   Particle Content*)
(*-------------------------------------------*)

(* Gauge Superfields *)

Gauge[[1]]={B,   U[1], hypercharge, g1,False};
Gauge[[2]]={WB, SU[2], left,        g2,True};
Gauge[[3]]={G,  SU[3], color,       g3,False};

(* Chiral Superfields *)

FermionFields[[1]] = {q, 3, {uL,dL},     1/6, 2, 3};  
FermionFields[[2]] = {l, 3, {vL,eL},    -1/2, 2, 1};
FermionFields[[3]] = {d, 3, conj[dR],   1/3, 1, -3};
FermionFields[[4]] = {u, 3, conj[uR],  -2/3, 1, -3};
FermionFields[[5]] = {e, 3, conj[eR],     1, 1,  1};

ScalarFields[[1]] =  {H1, 1, {H1p, H10},     1/2, 2,  1};
ScalarFields[[2]] =  {H2, 1, {H2p, H20},     1/2, 2,  1};

(* septuplet components: TP3, TP2, TP1, T0, TM1, TM2, TM3 *)

sept = Table[0, {2}, {2}, {2}, {2}, {2}, {2}];
Do[
   nnnnn2 = Count[{lef1,lef1b,lef1c,lef1d,lef1e,lef1f}, 2];
   If[nnnnn2 == 0, elemsep = \[ImaginaryI] TP3];
   If[nnnnn2 == 1, elemsep = \[ImaginaryI] TP2/Sqrt[6]];
   If[nnnnn2 == 2, elemsep = \[ImaginaryI] TP1/Sqrt[15]];
   If[nnnnn2 == 3, elemsep = -\[ImaginaryI] T0/Sqrt[20]];
   If[nnnnn2 == 4, elemsep = -\[ImaginaryI] TM1/Sqrt[15]];
   If[nnnnn2 == 5, elemsep = \[ImaginaryI] TM2/Sqrt[6]];
   If[nnnnn2 == 6, elemsep = -\[ImaginaryI] TM3];
   sept[[lef1,lef1b,lef1c,lef1d,lef1e,lef1f]] = elemsep;
, {lef1,1,2},{lef1b,1,2},{lef1c,1,2},{lef1d,1,2},{lef1e,1,2},{lef1f,1,2}];

TM1 = conj[TP1];
TM2 = conj[TP2];
TM3 = conj[TP3];

ScalarFields[[3]] =  {T, 1, sept,    0, 7,  1};

RealScalars = {T0};
conj[T0] = T0;     

(*----------------------------------------------*)
(*   DEFINITION                                 *)
(*----------------------------------------------*)

NameOfStates={GaugeES, EWSB};

(* ----- Before EWSB ----- *)

DEFINITION[GaugeES][Additional]= {
	{LagHC,  { AddHC->True}},
	{LagNoHC,{ AddHC->False}},
	{LagNoHC7,{ AddHC->False}}
};

LagNoHC = -( M112 conj[H1].H1 + M222 conj[H2].H2 + Lambda1/2 conj[H1].H1.conj[H1].H1 + \
	     Lambda2/2 conj[H2].H2.conj[H2].H2 + Lambda3 conj[H2].H2.conj[H1].H1 + Lambda4 conj[H2].H1.conj[H1].H2 );

cont7777A = epsTensor[lef1,lef2] epsTensor[lef1b,lef2b] epsTensor[lef1c,lef2c] epsTensor[lef1d,lef2d] epsTensor[lef1e,lef2e] epsTensor[lef1f,lef2f] epsTensor[lef3,lef4] epsTensor[lef3b,lef4b] epsTensor[lef3c,lef4c] epsTensor[lef3d,lef4d] epsTensor[lef3e,lef4e] epsTensor[lef3f,lef4f];
cont7777B = epsTensor[lef1,lef2] epsTensor[lef1b,lef2b] epsTensor[lef1c,lef2c] epsTensor[lef1d,lef2d] epsTensor[lef1e,lef2e] epsTensor[lef3f,lef2f] epsTensor[lef3,lef4] epsTensor[lef3b,lef4b] epsTensor[lef3c,lef4c] epsTensor[lef3d,lef4d] epsTensor[lef3e,lef4e] epsTensor[lef1f,lef4f];

LagNoHC7 = -( MT2 T.T + 1/24 LambdaT1 T.T.T.T cont7777A + \
              1/24 LambdaT2 T.T.T.T cont7777B + LambdaT3 conj[H1].H1.T.T + LambdaT4 conj[H2].H2.T.T );

LagHC = -( -M122 conj[H1].H2 + Lambda5/2 conj[H2].H1.conj[H2].H1 + Yd conj[H1].d.q + Ye conj[H1].e.l + Yu H2.u.q + \
	   epsD conj[H2].d.q + epsE conj[H2].e.l + epsU H1.u.q);


(* Gauge Sector *)

DEFINITION[EWSB][GaugeSector] =
{ 
  {{VB,VWB[3]},{VP,VZ},ZZ},
  {{VWB[1],VWB[2]},{VWm,conj[VWm]},ZW}
};     
        	

(* ----- VEVs ---- *)

DEFINITION[EWSB][VEVs]= 
{    {H10, {v1, 1/Sqrt[2]}, {sigma1, \[ImaginaryI]/Sqrt[2]},{phi1, 1/Sqrt[2]}},
     {H20, {v2, 1/Sqrt[2]}, {sigma2, \[ImaginaryI]/Sqrt[2]},{phi2, 1/Sqrt[2]}}
     };
 

DEFINITION[EWSB][MatterSector]=   
    { {{phi1, phi2}, {hh, ZH}},
      {{sigma1, sigma2}, {Ah, ZA}},
      {{conj[H1p],conj[H2p]},{Hm,ZP}},
      {{{dL}, {conj[dR]}}, {{DL,Vd}, {DR,Ud}}},
      {{{uL}, {conj[uR]}}, {{UL,Vu}, {UR,Uu}}},
      {{{eL}, {conj[eR]}}, {{EL,Ve}, {ER,Ue}}}       };  


(*------------------------------------------------------*)
(* Dirac-Spinors *)
(*------------------------------------------------------*)

DEFINITION[EWSB][DiracSpinors]={
 Fd ->{  DL, conj[DR]},
 Fe ->{  EL, conj[ER]},
 Fu ->{  UL, conj[UR]},
 Fv ->{  vL, 0}
};

DEFINITION[GaugeES][DiracSpinors]={
 Fd1 ->{  dL, 0},
 Fd2 ->{  0, dR},
 Fu1 ->{  uL, 0},
 Fu2 ->{  0, uR},
 Fe1 ->{  eL, 0},
 Fe2 ->{  0, eR},
 Fv -> {  vL, 0}
};



