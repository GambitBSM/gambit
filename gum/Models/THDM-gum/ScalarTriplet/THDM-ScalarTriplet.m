Off[General::spell]

Model`Name = "THDMIHT_gum";
Model`NameLaTeX ="Two Higgs Doublet Model with inert complex Higgs Triplet";
Model`Authors = "K. Nickel";
Model`Date = "2016-01-15";

(*-------------------------------------------*)
(*   Particle Content*)
(*-------------------------------------------*)

(* Gauge Superfields *)

Global[[1]] = {Z[2], Z2};
pP=1;
pM=-1;


Gauge[[1]]={B,   U[1], hypercharge, g1,False, pP};
Gauge[[2]]={WB, SU[2], left,        g2,True,  pP};
Gauge[[3]]={G,  SU[3], color,       g3,False, pP};


(* Chiral Superfields *)

FermionFields[[1]] = {q, 3, {uL,dL},     1/6, 2, 3, pP};  
FermionFields[[2]] = {l, 3, {vL,eL},    -1/2, 2, 1, pP};
FermionFields[[3]] = {d, 3, conj[dR],   1/3, 1, -3, pP};
FermionFields[[4]] = {u, 3, conj[uR],  -2/3, 1, -3, pP};
FermionFields[[5]] = {e, 3, conj[eR],     1, 1,  1, pP};

ScalarFields[[1]] =  {H1, 1, {H1p, H10},     1/2, 2,  1, pP};
ScalarFields[[2]] =  {H2, 1, {H2p, H20},     1/2, 2,  1, pP};

(* triplet components: Tpp, Tp, T0 *)

ScalarFields[[3]] =  {T,  1, {{Tp/Sqrt[2],Tpp},{T0,-Tp/Sqrt[2]}},   1, 3, 1, pM};


     

(*----------------------------------------------*)
(*   DEFINITION                                 *)
(*----------------------------------------------*)

NameOfStates={GaugeES, EWSB};

(* ----- Before EWSB ----- *)

DEFINITION[GaugeES][Additional]= {
	{LagHC, { AddHC->True}},
	{LagNoHC,{ AddHC->False}}
};






LagNoHC = -(M112 conj[H1].H1 + M222 conj[H2].H2 + Lambda1/2 conj[H1].H1.conj[H1].H1 + \
		Lambda2/2 conj[H2].H2.conj[H2].H2 + Lambda3 conj[H2].H2.conj[H1].H1 + Lambda4 conj[H2].H1.conj[H1].H2 + \
            MT2 conj[T].T + K1 Delta[lef1, lef2] Delta[lef1b, lef4b] Delta[lef2b, lef3b] Delta[lef3,lef4] conj[T].T.conj[T].T \
            + epsTensor[lef1b,lef2] epsTensor[lef2b,lef1]  epsTensor[lef3b,lef4] epsTensor[lef4b,lef3] K2 conj[T].T.conj[T].T  \
            + K3 Delta[lef1,lef2] epsTensor[lef2b,lef3] epsTensor[lef3b,lef4]  conj[H1].T.conj[T].H1  \
            + K3p Delta[lef1,lef2] epsTensor[lef2b,lef3] epsTensor[lef3b,lef4] conj[H2].T.conj[T].H2 \
            + K4 conj[H1].H1.conj[T].T  + K4p conj[H2].H2.conj[T].T);


LagHC = -(-M122 conj[H1].H2 + Lambda5/2 conj[H2].H1.conj[H2].H1 + Yd conj[H2].d.q + Ye conj[H2].e.l + Yu H2.u.q);

(* allowed terms by gauge invariance *)
(*
d.q.conj[H1]
e.l.conj[H1]
q.u.H1
+ hc

H1.H1.conj[H1].conj[H2]
H1.H2.conj[H2].conj[H2]

conj[H1].H2.conj[T].T
would create CPV
*)


(* Gauge Sector *)

DEFINITION[EWSB][GaugeSector] =
{ 
  {{VB,VWB[3]},{VP,VZ},ZZ},
  {{VWB[1],VWB[2]},{VWm,conj[VWm]},ZW}
};     
        
        
          	

(* ----- VEVs ---- *)

DEFINITION[EWSB][VEVs]= 
{    {H10, {v1, 1/Sqrt[2]}, {sigma1, \[ImaginaryI]/Sqrt[2]},{phi1, 1/Sqrt[2]}},
     {H20, {v2, 1/Sqrt[2]}, {sigma2, \[ImaginaryI]/Sqrt[2]},{phi2, 1/Sqrt[2]}},
     {T0,  {vT, 1/Sqrt[2]}, {sigmaT, \[ImaginaryI]/Sqrt[2]},{phiT, 1/Sqrt[2]}}
     };
 

DEFINITION[EWSB][MatterSector]=   
    { {{phi1, phi2, phiT}, {hh, ZH}},
      {{sigma1, sigma2, sigmaT}, {Ah, ZA}},
      {{conj[H1p],conj[H2p],conj[Tp]},{Hm,ZP}},
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



