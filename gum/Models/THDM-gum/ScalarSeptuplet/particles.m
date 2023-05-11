(* SARAH generated template for particles.m file for THDMIHT *)
(* File created at 12:22 on 19.1.2016  *) 

(* IMPORTANT: *)
(* check/adjust in particular the lines which contain "CHECK!" *)
(* the correct information is needed there to have correct results! *)


(* ###############            EWSB       ################# *) 

ParticleDefinitions[EWSB] = { 
 
(* ----------- Already defined particles in existing particles.m -------------- *) 

{Ah,{ 
     Description -> "Pseudo-Scalar Higgs", 
     FeynArtsNr -> 2, 
     LaTeX -> "A^0", 
     Mass -> {0, LesHouches}, 
     OutputName -> "Ah", 
     PDG -> {0, 36}, 
     ElectricCharge -> 0, 
     Width -> {0, External}}}, 

{Fd,{ 
     Description -> "Down-Quarks", 
     FeynArtsNr -> 4, 
     LaTeX -> "d", 
     Mass -> {0.0035, 0.104, 4.2}, 
     OutputName -> "d", 
     PDG -> {1, 3, 5}, 
     ElectricCharge -> -1/3, 
     Width -> {0, 0, 0}}}, 

{Fe,{ 
     Description -> "Leptons", 
     FeynArtsNr -> 2, 
     LaTeX -> "e", 
     Mass -> {0.000511, 0.105, 1.776}, 
     OutputName -> "e", 
     PDG -> {11, 13, 15}, 
     ElectricCharge -> -1, 
     Width -> {0, 0, 0}}}, 

{Fu,{ 
     Description -> "Up-Quarks", 
     FeynArtsNr -> 3, 
     LaTeX -> "u", 
     Mass -> {0.0015, 1.27, 171.2}, 
     OutputName -> "u", 
     PDG -> {2, 4, 6}, 
     ElectricCharge -> 2/3, 
     Width -> {0, 0, 1.51}}}, 

{Fv,{ 
     Description -> "Neutrinos", 
     FeynArtsNr -> 1, 
     LaTeX -> "\\nu", 
     Mass -> {0, 0, 0}, 
     OutputName -> "nu", 
     PDG -> {12, 14, 16}, 
     ElectricCharge -> 0, 
     Width -> {0, 0, 0}}}, 

{gG,{ 
     Description -> "Gluon Ghost", 
     FeynArtsNr -> 5, 
     LaTeX -> "\\eta^G", 
     Mass -> 0, 
     OutputName -> "gG", 
     PDG -> {0}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{gP,{ 
     Description -> "Photon Ghost", 
     FeynArtsNr -> 1, 
     LaTeX -> "\\eta^{\\gamma}", 
     Mass -> 0, 
     OutputName -> "gA", 
     PDG -> {0}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{gWm,{ 
     Description -> "Negative W-Boson Ghost", 
     FeynArtsNr -> 3, 
     LaTeX -> "\\eta^-", 
     Mass -> Mass[VWm], 
     OutputName -> "gWm", 
     PDG -> {0}, 
     ElectricCharge -> -1, 
     Width -> Automatic}}, 

{gWmC,{ 
     Description -> "Positive W-Boson Ghost", 
     FeynArtsNr -> 4, 
     LaTeX -> "\\eta^+", 
     Mass -> Mass[VWm], 
     OutputName -> "gWpC", 
     PDG -> {0}, 
     ElectricCharge -> 1, 
     Width -> Automatic}}, 

{gZ,{ 
     Description -> "Z-Boson Ghost", 
     FeynArtsNr -> 2, 
     LaTeX -> "\\eta^Z", 
     Mass -> Mass[VZ], 
     OutputName -> "gZ", 
     PDG -> {0}, 
     ElectricCharge -> 0, 
     Width -> Automatic}}, 

{hh,{ 
     Description -> "Higgs", 
     FeynArtsNr -> 1, 
     LaTeX -> "h", 
     Mass -> LesHouches, 
     OutputName -> "h", 
     PDG -> {25, 35}, 
     ElectricCharge -> 0, 
     Width -> Automatic}}, 

{Hm,{ 
     Description -> "Charged Higgs", 
     FeynArtsNr -> 3, 
     LaTeX -> {"H^-","H^+"}, 
     Mass -> {0, LesHouches}, 
     OutputName -> {"Hm","Hp"}, 
     PDG -> {0, -37}, 
     ElectricCharge -> -1, 
     Width -> {0, External}}}, 

{TP3,{ 
FeynArtsNr -> 34, 
     LaTeX -> "{T}^{+++}", 
     Mass -> LesHouches, 
     OutputName -> "tp3", 
     PDG -> {44}, 
     ElectricCharge -> 3}}, 

{TP2,{ 
FeynArtsNr -> 32, 
     LaTeX -> "{T}^{++}", 
     Mass -> LesHouches, 
     OutputName -> "tp2", 
     PDG -> {46}, 
     ElectricCharge -> 2}}, 

{TP1,{
FeynArtsNr -> 30,  
     LaTeX -> "{T}^{+}", 
     Mass -> LesHouches, 
     OutputName -> "tp1", 
     PDG -> {48}, 
     ElectricCharge -> 1}}, 

{T0 ,{ 
FeynArtsNr -> 28, 
     LaTeX -> "T^0", 
     Mass -> LesHouches, 
     OutputName -> "t0", 
     PDG -> {50}, 
     ElectricCharge -> 0}}, 

{VG,{ 
     Description -> "Gluon", 
     FeynArtsNr -> 5, 
     LaTeX -> "g", 
     Mass -> 0, 
     OutputName -> "g", 
     PDG -> {21}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{VP,{ 
     Description -> "Photon", 
     FeynArtsNr -> 1, 
     LaTeX -> "\\gamma", 
     Mass -> 0, 
     OutputName -> "A", 
     PDG -> {22}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{VWm,{ 
     Description -> "W-Boson", 
     Goldstone -> Hm[{1}], 
     FeynArtsNr -> 3, 
     LaTeX -> {"W^-","W^+"}, 
     Mass -> Dependence, 
     MassDependence -> Sqrt[Mass[VZ]^2/2 + Sqrt[-((Pi*Mass[VZ]^2)/(Sqrt[2]*aEWinv*Gf)) + Mass[VZ]^4/4]], 
     OutputName -> {"Wm","WP"}, 
     PDG -> {-24}, 
     ElectricCharge -> -1, 
     Width -> 2.141}}, 

{VZ,{ 
     Description -> "Z-Boson", 
     Goldstone -> Ah[{1}], 
     FeynArtsNr -> 2, 
     LaTeX -> "Z", 
     Mass -> 91.1876, 
     OutputName -> "Z", 
     PDG -> {23}, 
     ElectricCharge -> 0, 
     Width -> 2.4952}} 
}; 




(* ###############            GaugeES       ################# *) 

ParticleDefinitions[GaugeES] = { 
 
(* ----------- Already defined particles in existing particles.m -------------- *) 

{Fd1,{ 
     FeynArtsNr -> 6, 
     LaTeX -> "d1", 
     Mass -> LesHouches, 
     OutputName -> "fd1", 
     PDG -> {29, 30, 31}, 
     Width -> Automatic}}, 

{Fd2,{ 
     FeynArtsNr -> 8, 
     LaTeX -> "d2", 
     Mass -> LesHouches, 
     OutputName -> "fd2", 
     PDG -> {35, 36, 37}, 
     Width -> Automatic}}, 

{Fe1,{ 
     FeynArtsNr -> 10, 
     LaTeX -> "e1", 
     Mass -> LesHouches, 
     OutputName -> "fe1", 
     PDG -> {41, 42, 43}, 
     Width -> Automatic}}, 

{Fe2,{ 
     FeynArtsNr -> 12, 
     LaTeX -> "e2", 
     Mass -> LesHouches, 
     OutputName -> "fe2", 
     PDG -> {47, 48, 49}, 
     Width -> Automatic}}, 

{Fu1,{ 
     FeynArtsNr -> 14, 
     LaTeX -> "u1", 
     Mass -> LesHouches, 
     OutputName -> "fu1", 
     PDG -> {53, 54, 55}, 
     Width -> Automatic}}, 

{Fu2,{ 
     FeynArtsNr -> 16, 
     LaTeX -> "u2", 
     Mass -> LesHouches, 
     OutputName -> "fu2", 
     PDG -> {59, 60, 61}, 
     Width -> Automatic}}, 

{Fv,{ 
     Description -> "Neutrinos", 
     FeynArtsNr -> 1, 
     LaTeX -> "\\nu", 
     Mass -> {0, 0, 0}, 
     OutputName -> "nu", 
     PDG -> {12, 14, 16}, 
     ElectricCharge -> 0, 
     Width -> {0, 0, 0}}}, 

{gB,{ 
     Description -> "B-Boson Ghost", 
     FeynArtsNr -> 1, 
     LaTeX -> "\\eta^B", 
     Mass -> 0, 
     OutputName -> "gB", 
     PDG -> {0}, 
     Width -> 0}}, 

{gG,{ 
     Description -> "Gluon Ghost", 
     FeynArtsNr -> 5, 
     LaTeX -> "\\eta^G", 
     Mass -> 0, 
     OutputName -> "gG", 
     PDG -> {0}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{gWB,{ 
     Description -> "W-Boson Ghost", 
     FeynArtsNr -> 2, 
     LaTeX -> "\\eta^W", 
     Mass -> 0, 
     OutputName -> "gW", 
     PDG -> {0}   (* adjusted number of PDGs to number of generations  *), 
     Width -> 0}}, 

{H10,{ 
     FeynArtsNr -> 20, 
     LaTeX -> "{h1}^0", 
     Mass -> LesHouches, 
     OutputName -> "h10", 
     PDG -> {63}, 
     Width -> Automatic}}, 

{H1p,{ 
     FeynArtsNr -> 22, 
     LaTeX -> "h1p", 
     Mass -> LesHouches, 
     OutputName -> "h1p", 
     PDG -> {65}, 
     Width -> Automatic}}, 

{H20,{ 
     FeynArtsNr -> 24, 
     LaTeX -> "{h2}^0", 
     Mass -> LesHouches, 
     OutputName -> "h20", 
     PDG -> {67}, 
     Width -> Automatic}}, 

{H2p,{ 
     FeynArtsNr -> 26, 
     LaTeX -> "h2p", 
     Mass -> LesHouches, 
     OutputName -> "h2p", 
     PDG -> {69}, 
     Width -> Automatic}}, 

{T0,{ 
     FeynArtsNr -> 28, 
     LaTeX -> "{t}^0", 
     Mass -> LesHouches, 
     OutputName -> "t0", 
     PDG -> {71}, 
     Width -> Automatic}}, 

{TP1,{ 
     FeynArtsNr -> 30, 
     LaTeX -> "T^+", 
     Mass -> LesHouches, 
     OutputName -> "tp1", 
     PDG -> {73}, 
     Width -> Automatic}}, 

{TP2,{ 
FeynArtsNr -> 32, 
     LaTeX -> "{T}^{++}", 
     Mass -> LesHouches, 
     OutputName -> "tp2", 
     PDG -> {44}, 
     ElectricCharge -> 2, 
     Width -> Automatic}}, 


{TP3,{ 
FeynArtsNr -> 34, 
     LaTeX -> "{T}^{+++}", 
     Mass -> LesHouches, 
     OutputName -> "tp3", 
     PDG -> {46}, 
     ElectricCharge -> 3, 
     Width -> Automatic}}, 
{VB,{ 
     Description -> "B-Boson", 
     FeynArtsNr -> 1, 
     LaTeX -> "B", 
     Mass -> 0, 
     OutputName -> "B", 
     PDG -> {0}, 
     Width -> 0}}, 

{VG,{ 
     Description -> "Gluon", 
     FeynArtsNr -> 5, 
     LaTeX -> "g", 
     Mass -> 0, 
     OutputName -> "g", 
     PDG -> {21}, 
     ElectricCharge -> 0, 
     Width -> 0}}, 

{VWB,{ 
     Description -> "W-Bosons", 
     FeynArtsNr -> 2, 
     LaTeX -> "W", 
     Mass -> 0, 
     OutputName -> "W", 
     PDG -> {0, 24, 25}, 
     Width -> 0}} 
}; 




(* ###############            Weyl Spinors and intermediate states       ################# *) 

WeylFermionAndIndermediate = { 
 
(* ----------- Already defined particles in existing particles.m -------------- *) 

{dL,{ 
     LaTeX -> "d_L"}}, 

{uL,{ 
     LaTeX -> "u_L"}}, 

{eL,{ 
     LaTeX -> "e_L"}}, 

{vL,{ 
     LaTeX -> "\\nu_L"}}, 

{dR,{ 
     LaTeX -> "d_R"}}, 

{uR,{ 
     LaTeX -> "u_R"}}, 

{eR,{ 
     LaTeX -> "e_R"}}, 

{DL,{ 
     LaTeX -> "D_L"}}, 

{DR,{ 
     LaTeX -> "D_R"}}, 

{UL,{ 
     LaTeX -> "U_L"}}, 

{UR,{ 
     LaTeX -> "U_R"}}, 

{EL,{ 
     LaTeX -> "E_L"}}, 

{ER,{ 
     LaTeX -> "E_R"}}, 

{sigma1,{ 
     LaTeX -> "\\sigma_1"}}, 

{phi1,{ 
     LaTeX -> "\\phi_1"}}, 

{sigma2,{ 
     LaTeX -> "\\sigma_2"}}, 

{phi2,{ 
     LaTeX -> "\\phi_2"}}, 

{d,{ 
     LaTeX -> "d"}}, 

{e,{ 
     LaTeX -> "e"}}, 

{H1,{ 
     LaTeX -> "h1"}}, 

{H2,{ 
     LaTeX -> "h2"}}, 

{l,{ 
     LaTeX -> "l"}}, 

{q,{ 
     LaTeX -> "q"}}, 

{T,{ 
     LaTeX -> "t"}}, 

{u,{ 
     LaTeX -> "u"}}, 

{VB,{ 
     LaTeX -> "B"}}, 

{VG,{ 
     LaTeX -> "G"}}, 

{VWB,{ 
     LaTeX -> "WB"}} 
}; 




