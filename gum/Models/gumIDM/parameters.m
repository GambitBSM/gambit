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


{MHD,      { Description -> "Softbreaking Down-Higgs Mass", OutputName -> MHD2, LesHouches -> {HMIX,20} }}, 
{MHU,      { Description -> "Softbreaking Up-Higgs Mass" ,LesHouches -> {HMIX,21} , OutputName -> MHU2 }},


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

{Lambdaa1,   { OutputName ->lam1, LaTeX -> "\\lambda_1",
              LesHouches -> {HDM,31}}},

{Lambdaa2,   { OutputName ->lam2, LaTeX -> "\\lambda_2",
              LesHouches -> {HDM,32}}},

{Lambdaa3,   { OutputName ->lam3, LaTeX -> "\\lambda_3",
              LesHouches -> {HDM,33}}},

{Lambdaa4,   { OutputName ->lam4, LaTeX -> "\\lambda_4",
              LesHouches -> {HDM,34}}},

{Lambdaa5,   { OutputName ->lam5, LaTeX -> "\\lambda_5",
              LesHouches -> {HDM,35}}}

 }; 
 
