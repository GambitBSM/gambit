(* Description: defines a string to describe the parameter. *)
(* OutputName: defines a string which is used for the parameter in the different outputs. No special
characters should be used to be compatible with C++ and Fortran *)
(* Real: defines if a parameter should be considered as real (True) or complex (False). Default is
False (except for couplings). *)
(* Form: can be used for matrices to define if it is diagonal (Diagonal) or a scalar (Scalar). By
default no assumption is made. *)
(* LaTeX: defines the name of the parameter used in the LATEX output. Standard LATEX language
should be used *)
(*  GUTnormalization: defines a GUT normalization for an Abelian gauge coupling. *)
(* Dependence: defines a dependence on other parameters which should always be used. *)
(* DependenceOptional: defines a dependence which is optionally used in analytical calculations. *)
(* DependenceNum: defines a dependence which is used in numerical calculations. *)
(* DependenceSPheno: defines a dependence which is just used by SPheno. *)
(* MatrixProduct: can be used to express a matrix as product of two other matrices. This can be
used for instance to relate the CKM matrix to the quark rotation matrices. *)
(* LesHouches: defines the position of the parameter in a Les Houches spectrum file. For matrices
just the name of the block is defined, for scalars the block and an entry has to be given: {block,
number}. *)
(* Value: assigns a numerical value to the parameter. *)

(*  The reason why we also add an output name is
that this matrix shows up internally in SPheno *)

(* Many of the above definitions are just optional and are often not needed *)

ParameterDefinitions = { 

{g1,        { Description -> "Hypercharge-Coupling"}},
{g2,        { Description -> "Left-Coupling"}},
{g3,        { Description -> "Strong-Coupling"}},  
				
{AlphaS,    {Description -> "Alpha Strong"}},

{Gf,        { Description -> "Fermi's constant"}},
{aEWinv,    { Description -> "inverse weak coupling constant at mZ"}},
{e,         { Description -> "electric charge"}}, 

{Yu,        { Description -> "Up-Yukawa-Coupling"   }}, 
{Yd,        { Description -> "Down-Yukawa-Coupling"}},
{Ye,        { Description -> "Lepton-Yukawa-Coupling"}}, 

{MHD,      { Description -> "Softbreaking Down-Higgs Mass"}}, 
{MHU,      { Description -> "Softbreaking Up-Higgs Mass"}}, 

{v,         { Description -> "EW-VEV",
               DependenceNum -> Sqrt[4*Mass[VWp]^2/(g2^2)],
               DependenceSPheno -> None }},      

{\[Beta],   { Description -> "Pseudo Scalar mixing angle"  }},   

{TanBeta,   { Description -> "Tan Beta" }},              

{ZP,        { Description->"Charged-Mixing-Matrix",
              Dependence -> None}},                      
                                          
{ZEL,       { Description ->"Left-Lepton-Mixing-Matrix"}},
{ZER,       { Description ->"Right-Lepton-Mixing-Matrix" }},                          
{ZDL,       { Description ->"Left-Down-Mixing-Matrix"}},                       
{ZDR,       { Description ->"Right-Down-Mixing-Matrix"}},              
{ZUL,       { Description ->"Left-Up-Mixing-Matrix"}},                        
{ZUR,       { Description ->"Right-Up-Mixing-Matrix"}},           
              
{ThetaW,    { Description -> "Weinberg-Angle",
              DependenceNum -> ArcSin[Sqrt[1 - Mass[VWp]^2/Mass[VZ]^2]] }},                           

{ZZ, {Description ->   "Photon-Z Mixing Matrix"}},

{ZW, {Description -> "W Mixing Matrix",
       Dependence ->   1/Sqrt[2] {{1, 1},
                  {\[ImaginaryI],-\[ImaginaryI]}} }},

{Lambda1,   { OutputName ->"Lam1",
              LesHouches -> {HDM,1}}},

{Lambda2,   { OutputName ->"Lam2",
              LesHouches -> {HDM,2}}},

{Lambda3,   { OutputName ->"Lam3",
              LesHouches -> {HDM,3}}},

{Lambda4,   { OutputName ->"Lam4",
              LesHouches -> {HDM,4}}},

{Lambda5,   { OutputName ->"Lam5",
              LesHouches -> {HDM,5}}}

 }; 
 

