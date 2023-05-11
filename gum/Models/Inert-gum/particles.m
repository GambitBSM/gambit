(* Description: a string for defining the particle. *)
(* PDG: defines the PDG numbers of all generations. *)
(* PDG.IX: defines a nine-digit number of a particle supporting the proposal Ref. [290, 291]. By default, the entries of PDG are used in the output *)
(* ElectricCharge: defines the electric charge of a particle in units of e. This information is exported to the CalcHep/CompHep and UFO model files. *)
(* Width: can be used to define a fixed numerical value for the width. *)
(* Mass: defines, how MC tools obtain a numerical value for the mass of the particle: *)


(* – a numerical value can be given *)
(* – the keyword Automatic assigns that SARAH derives the tree level expression for the mass *)
(* from the Lagrangian. The mass is then calculated by using the values of the other parameters. *)
(* – the keyword LesHouches assigns that this mass is calculated numerically by a spectrum *)
(* generator like SPheno and provided via a Les Houches spectrum file. This is usually the *)
(* preferred method because also loop corrections are included. *)

(* OutputName: defines the name used in the different outputs for other codes. *)
(* LaTeX: defines the name of the particle used in the LATEX output. *)
(* FeynArtsNr: the number assigned to the particle used in the FeynArts output *)
(* LHPC: defines the column and colour used for the particle in the steering file for the LHPC
Spectrum Plotter 24. All colours available in gnuplot can be used. *)
(* Goldstone: for each massive vector boson the name of corresponding Goldstone boson is given. *)

(* Usually, the user is only interested in the output for the mass
eigenstates. Therefore, it is not really necessary to define the entire properties of all intermediate
states and the gauge eigenstates. *)

ParticleDefinitions[GaugeES] = {

  {VB,   { Description -> "B-Boson"}},

  {VG,   { Description -> "Gluon"}},

  {VWB,  { Description -> "W-Bosons"}},

  {gB,   { Description -> "B-Boson Ghost"}},

  {gG,   { Description -> "Gluon Ghost" }},

  {gWB,  { Description -> "W-Boson Ghost"}}

};


ParticleDefinitions[EWSB] = {

  {hh   ,  {  Description -> "Neutral Down-Higgs",
              OutputName -> "h0",
              ElectricCharge->0,
              PDG -> {25},
              FeynArtsNr -> 1,
              PDG.IX -> {101000001} }},

  {G0   ,  {  Description -> "Pseudo-Scalar Goldstone",
              PDG -> {0},
              PDG.IX ->{0},
              Mass -> {0},
              FeynArtsNr -> 4,
              ElectricCharge->0,
              Width -> {0} }},

  {H0   ,  {  Description -> "Neutral Up-Higgs",
              OutputName ->"H0",
              PDG -> {35},
              PDG.IX -> {101000001},
              FeynArtsNr -> 2,
              ElectricCharge->0,
              LaTeX -> "H" }},

  {A0   ,  {  Description -> "Pseudo-Scalar Higgs", (*"Pseudo Scalar Up",*)
              OutputName ->"A0",
              PDG -> {36},
              ElectricCharge->0,
              FeynArtsNr -> 3,
              LaTeX -> "A^0" }},

  {Hp,  { Description -> "Charged Higgs",
          ElectricCharge -> 1,
          FeynArtsNr -> 5}},

  {VP,   { Description -> "Photon"}},

  {VZ,   { Description -> "Z-Boson",
           Goldstone -> G0 }},

  {VG,   { Description -> "Gluon" }},

  {VWp,  { Description -> "W+ - Boson",
           Goldstone -> Hp[{1}] }},

(* note that we use Hp[{1}], Hp[{2}] to pick out the first and second charged scalar (the first being the Goldstone) *)

  {gP,   { Description -> "Photon Ghost"}},
  {gWp,  { Description -> "Positive W+ - Boson Ghost"}},
  {gWpC, { Description -> "Negative W+ - Boson Ghost" }},
  {gZ,   { Description -> "Z-Boson Ghost" }},
  {gG,   { Description -> "Gluon Ghost" }},

  {Fd,   { Description -> "Down-Quarks"}},
  {Fu,   { Description -> "Up-Quarks"}},
  {Fe,   { Description -> "Leptons" }},
  {Fv,   { Description -> "Neutrinos" }}

};


WeylFermionAndIndermediate = {

  {phid,   {  PDG -> 0,
            Width -> 0,
            Mass -> Automatic,
            LaTeX -> "\\phi_{d}",
            OutputName -> "" }},


  {phiu,   {  PDG -> 0,
            Width -> 0,
            Mass -> Automatic,
            LaTeX -> "\\phi_{u}",
            OutputName -> "" }},

  {sigmad,   {  PDG -> 0,
            Width -> 0,
            Mass -> Automatic,
            LaTeX -> "\\sigma_{d}",
            OutputName -> "" }},

  {sigmau,   {  PDG -> 0,
            Width -> 0,
            Mass -> Automatic,
            LaTeX -> "\\sigma_{u}",
            OutputName -> "" }}

};


(* For the ghost we used the PDG 0 to make clear that this is not a physical state *)
