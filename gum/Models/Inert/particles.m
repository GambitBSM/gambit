
ParticleDefinitions[GaugeES] = {

      {VB,   { Description -> "B-Boson"}},                                                   
      {VG,   { Description -> "Gluon"}},          
      {VWB,  { Description -> "W-Bosons"}},          
      {gB,   { Description -> "B-Boson Ghost"}},                                                   
      {gG,   { Description -> "Gluon Ghost" }},          
      {gWB,  { Description -> "W-Boson Ghost"}}
      };
      
      
      
      
   ParticleDefinitions[EWSB] = {

     {hh   ,  {  Description -> "Higgs",
                 ElectricCharge->0,     
                 PDG -> {25},
                 Mass -> LesHouches,
                 Width -> Automatic,
                 FeynArtsNr -> 1,
                 PDG.IX -> {101000001} }}, 
                 
     {G0   ,  {  Description -> "Pseudo-Scalar Higgs",
                 ElectricCharge->0,
                 PDG -> {0},
                 PDG.IX ->{0},
                 Mass -> {0},
                 FeynArtsNr -> 4,               
                 Width -> {0} }},  

     {H0   ,  {  Name -> "~H0",
                 Description -> "Inert CP-even scalar",
                 OutputName->"H0",
                 ElectricCharge->0,
                 PDG -> {35},
                 Mass -> LesHouches,
                 Width -> Automatic,
                 FeynArtsNr -> 2,
                 PDG.IX ->{101000002},               
                 Latex -> "H^0" }},  
                 
     {A0   ,  {  Description -> "Inert CP-odd scalar",
                 OutputName->"A0",
                 ElectricCharge->0,
                 PDG -> {36},
                 Mass -> LesHouches,
                 Width -> Automatic,
                 FeynArtsNr -> 3,
                 PDG.IX ->{101000003},               
                 Latex -> "A^0" }},            
            
      
     {Hp   ,  {  Description -> "Charged Higgs",
                 OutputName->"Hp",
                 ElectricCharge->1,
                 PDG -> {0, 37},
                 Mass -> LesHouches,
                 Width -> Automatic,
                 FeynArtsNr -> 5,
                 PDG.IX ->{0, 101000004} }}, 
                                                                   
      {VP,   { Description -> "Photon"}}, 
      {VZ,   { Description -> "Z-Boson",
                Goldstone -> G0 }}, 
      {VG,   { Description -> "Gluon" }},          
      {VWp,  { Description -> "W+ - Boson",
               Goldstone -> Hp[{1}] }},         
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


